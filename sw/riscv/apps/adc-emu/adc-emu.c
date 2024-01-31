/*
* Copyright 2023 EPFL
* Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
* SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
*
* Author: Simone Machetti - simone.machetti@epfl.ch
*/

#include <stdio.h>
#include <stdlib.h>
#include "csr.h"
#include "hart.h"
#include "handler.h"
#include "core_v_mini_mcu.h"
#include "rv_timer.h"
#include "rv_timer_regs.h"
#include "soc_ctrl.h"
#include "rv_plic.h"
#include "rv_plic_regs.h"
#include "spi_host.h"
#include "spi_host_regs.h"
#include "dma.h"
#include "fast_intr_ctrl.h"
#include "gpio.h"
#include "fast_intr_ctrl_regs.h"

#include "definitions.h"

#define REVERT_32b_ADDR(addr) ((((uint32_t)addr & 0xff000000) >> 24) | (((uint32_t)addr & 0x00ff0000) >> 8) | (((uint32_t)addr & 0x0000ff00) << 8) | (((uint32_t)addr & 0x000000ff) << 24))
#define FLASH_ADDR 0x00000000
#define FLASH_CLK_MAX_HZ (133 * 1000 * 1000)

#if ENABLE_PRINTF
    #define PRINTF(fmt, ...)    printf(fmt, ## __VA_ARGS__)
#else
    #define PRINTF(...)
#endif

volatile int8_t dma_intr_flag;

spi_host_t spi_host_flash;
soc_ctrl_t soc_ctrl;
dma_t dma;
gpio_params_t gpio_params;
gpio_t gpio;
gpio_result_t gpio_res;
uint32_t data[INPUT_DATA_LENGTH];


void handler_irq_fast_dma(void)
{
    fast_intr_ctrl_t fast_intr_ctrl;
    fast_intr_ctrl.base_addr = mmio_region_from_addr((uintptr_t)FAST_INTR_CTRL_START_ADDRESS);
    clear_fast_interrupt(&fast_intr_ctrl, kDma_fic_e);
    dma_intr_flag = 1;
}

void read_from_flash(spi_host_t *SPI, dma_t *DMA, uint32_t *data, uint32_t byte_count, uint32_t addr)
{
    // Setting the DMA
    uint32_t *fifo_ptr_rx = SPI->base_addr.base + SPI_HOST_RXDATA_REG_OFFSET;
    dma_set_read_ptr_inc(DMA, (uint32_t) 0);
    dma_set_write_ptr_inc(DMA, (uint32_t) 4);
    dma_set_read_ptr(DMA, (uint32_t) fifo_ptr_rx);
    dma_set_write_ptr(DMA, (uint32_t) data);
    dma_set_spi_mode(DMA, (uint32_t) 1);
    dma_set_data_type(DMA, (uint32_t) 0);
    dma_set_cnt_start(DMA, (uint32_t) byte_count);

    // Read command
    uint32_t read_from_mem = 0x0b;
    uint32_t cmd_read_from_mem = spi_create_command((spi_command_t){
        .len       = 0,
        .csaat     = true,
        .speed     = kSpiSpeedStandard,
        .direction = kSpiDirTxOnly
    });

    // Address command
    uint32_t addr_cmd = REVERT_32b_ADDR(0x00000000);
    uint32_t cmd_address = spi_create_command((spi_command_t){
        .len       = 3,
        .csaat     = true,
        .speed     = kSpiSpeedStandard,
        .direction = kSpiDirTxOnly
    });

    // Dummy command
    uint32_t dummy_cmd = 0x00;
    uint32_t cmd_dummy = spi_create_command((spi_command_t){
        .len       = 1,
        .csaat     = true,
        .speed     = kSpiSpeedStandard,
        .direction = kSpiDirTxOnly
    });

    // Receive data
    const uint32_t cmd_read_rx = spi_create_command((spi_command_t){
        .len       = byte_count - 1,
        .csaat     = false,
        .speed     = kSpiSpeedStandard,
        .direction = kSpiDirRxOnly
    });

    // Read command
    spi_write_word(SPI, read_from_mem);
    spi_set_command(SPI, cmd_read_from_mem);
    spi_wait_for_ready(SPI);
    // Address command
    spi_write_word(SPI, addr_cmd);
    spi_wait_for_ready(SPI);
    spi_set_command(SPI, cmd_address);
    spi_wait_for_ready(SPI);
    // Dummy command
    spi_write_word(SPI, dummy_cmd);
    spi_wait_for_ready(SPI);
    spi_set_command(SPI, cmd_dummy);
    spi_wait_for_ready(SPI);
    // Receive data
    spi_set_command(SPI, cmd_read_rx);
    spi_wait_for_ready(SPI);

    while(dma_intr_flag == 0) {
        wait_for_interrupt();
    }
}

void vadc_init()
{
    soc_ctrl.base_addr = mmio_region_from_addr((uintptr_t)SOC_CTRL_START_ADDRESS);
    soc_ctrl_select_spi_host(&soc_ctrl);

    uint32_t core_clk = soc_ctrl_get_frequency(&soc_ctrl);

    CSR_SET_BITS(CSR_REG_MSTATUS, 0x8);
    uint32_t mask = 1 << 19;
    CSR_SET_BITS(CSR_REG_MIE, mask);
    dma_intr_flag = 0;
    CSR_SET_BITS(CSR_REG_MIE, mask);

    spi_host_flash.base_addr = mmio_region_from_addr((uintptr_t)SPI_HOST_START_ADDRESS);
    spi_set_enable(&spi_host_flash, true);
    spi_output_enable(&spi_host_flash, true);

    dma.base_addr = mmio_region_from_addr((uintptr_t)DMA_START_ADDRESS);

    uint16_t clk_div = 0;

    if (FLASH_CLK_MAX_HZ < core_clk / 2)
    {
        clk_div = (core_clk / (FLASH_CLK_MAX_HZ)-2) / 2;
        if (core_clk / (2 + 2 * clk_div) > FLASH_CLK_MAX_HZ)
            clk_div += 1;
    }

    const uint32_t chip_cfg_flash = spi_create_configopts((spi_configopts_t){
        .clkdiv = clk_div,
        .csnidle = 0xF,
        .csntrail = 0xF,
        .csnlead = 0xF,
        .fullcyc = false,
        .cpha = 0,
        .cpol = 0});
    spi_set_configopts(&spi_host_flash, 0, chip_cfg_flash);
    spi_set_csid(&spi_host_flash, 0);

    // Config SPI to AXI bridge

    const uint32_t write_mem_cmd = 0x02;
    const uint32_t read_mem_cmd = 0x0B;
    const uint32_t write_reg0_cmd = 0x01;
    const uint32_t read_reg0_cmd = 0x05;
    const uint32_t write_reg1_cmd = 0x11;
    const uint32_t read_reg1_cmd = 0x07;
    const uint32_t write_reg2_cmd = 0x20;
    const uint32_t read_reg2_cmd = 0x21;
    const uint32_t write_reg3_cmd = 0x30;
    const uint32_t read_reg3_cmd = 0x31;

    const uint32_t cmd_bridge = spi_create_command((spi_command_t){
        .len        = 0,
        .csaat      = true,
        .speed      = kSpiSpeedStandard,
        .direction  = kSpiDirTxOnly
    });

    const uint32_t set_dummy_cycle = 15U;
    const uint32_t cmd_bridge_value = spi_create_command((spi_command_t){
        .len        = 0,
        .csaat      = false,
        .speed      = kSpiSpeedStandard,
        .direction  = kSpiDirTxOnly
    });

    // Set normal SPI (reg0)
    spi_write_word(&spi_host_flash, write_reg0_cmd);
    spi_set_command(&spi_host_flash, cmd_bridge);
    spi_wait_for_ready(&spi_host_flash);
    spi_write_word(&spi_host_flash, 0x00);
    spi_set_command(&spi_host_flash, cmd_bridge_value);
    spi_wait_for_ready(&spi_host_flash);
    
    // Set the dummy address (reg1)
    spi_write_word(&spi_host_flash, write_reg1_cmd);
    spi_set_command(&spi_host_flash, cmd_bridge);
    spi_wait_for_ready(&spi_host_flash);
    spi_write_word(&spi_host_flash, set_dummy_cycle);
    spi_set_command(&spi_host_flash, cmd_bridge_value);
    spi_wait_for_ready(&spi_host_flash);

    // Set wrap around (reg3, reg2)
    spi_write_word(&spi_host_flash, write_reg2_cmd);
    spi_set_command(&spi_host_flash, cmd_bridge);
    spi_wait_for_ready(&spi_host_flash);
    spi_write_word(&spi_host_flash, 0x00); // 0xFF
    spi_set_command(&spi_host_flash, cmd_bridge_value);
    spi_wait_for_ready(&spi_host_flash);

    spi_write_word(&spi_host_flash, write_reg3_cmd);
    spi_set_command(&spi_host_flash, cmd_bridge);
    spi_wait_for_ready(&spi_host_flash);
    spi_write_word(&spi_host_flash, 0x04); // 0x03
    spi_set_command(&spi_host_flash, cmd_bridge_value);
    spi_wait_for_ready(&spi_host_flash);
}

static inline void perf_start(){
    gpio_params.base_addr = mmio_region_from_addr((uintptr_t)GPIO_AO_START_ADDRESS);
    gpio_res = gpio_init(gpio_params, &gpio);

    gpio_res = gpio_output_set_enabled(&gpio, 1, true);
    gpio_write(&gpio, 1, true);
}

static inline void perf_stop(){
    gpio_write(&gpio, 1, false);
}

/**
 * This functions takes the data and returns two values:
 * LPF | HPF
 *
 * LPF: The moving-mean of the signal with a sample window that is a power of 2.
 * HPF: The original signal, subtracted the moving-mean.
*/
static inline void lpf_hpf(){
    // uint8_t bits = 5;
    // uint32_t m  = data[0];
    // uint32_t mb = m << bits;
    uint32_t x = 0;
    // uint32_t h = 0;
    // uint32_t l = m;
    // PRINTF("%sLPF %s HPF %s IN\n",OUTPUT_START_SEQ, OUTPUT_DIVIDER, OUTPUT_DIVIDER);
    PRINTF("%sIN\n",OUTPUT_START_SEQ); // Header
    for(uint32_t i = 0; i < INPUT_DATA_LENGTH; i++){
        x = data[i];
        PRINTF("%02d\n",x);
    }
    // for(uint32_t i = 1; i < INPUT_DATA_LENGTH; i++){
    //     x = data[i];        // The current value to compute the mean
    //     mb -= m;            // 4*mean without the last value
    //     mb += x;            // 4*mean with the new value
    //     m = mb >> bits;     // The new mean (4*mean/4)
    //     h = l - m;          // The new HPFd value (signal - mean)
    //     l = x;              // The value of data[i-1] for the next iteration
    //     PRINTF("%02d\n",x);
    // }
    PRINTF("%s\n",OUTPUT_END_SEQ); // Tail
}


int main(int argc, char *argv[])
{
    // Start the performance counters to report timing and energy
    perf_start();
    vadc_init();

    // Obtain the data (simulating obtaining a buffer from the ADC)
    read_from_flash(&spi_host_flash, &dma, data, 4 * INPUT_DATA_LENGTH, FLASH_ADDR);

    // Perform a LPF and HPF to the signal
    lpf_hpf();

    // Stop the performance counters.
    perf_stop();
    return EXIT_SUCCESS;

}
