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

#define REVERT_24b_ADDR(addr) ((((uint32_t)addr & 0xff0000) >> 16) | ((uint32_t)addr & 0xff00) | (((uint32_t)addr & 0xff) << 16))
#define FLASH_ADDR 0x00000000
#define FLASH_CLK_MAX_HZ (133 * 1000 * 1000)

volatile int8_t dma_intr_flag;

spi_host_t spi_host_flash;

void handler_irq_fast_dma(void)
{
    fast_intr_ctrl_t fast_intr_ctrl;
    fast_intr_ctrl.base_addr = mmio_region_from_addr((uintptr_t)FAST_INTR_CTRL_START_ADDRESS);
    clear_fast_interrupt(&fast_intr_ctrl, kDma_fic_e);
    dma_intr_flag = 1;
}

void read_from_flash(spi_host_t *SPI, dma_t *DMA, uint32_t *data, uint32_t byte_count, uint32_t addr)
{
    uint32_t read_from_mem = 0x0b;
    spi_write_word(SPI, read_from_mem);
    uint32_t cmd_read_from_mem = spi_create_command((spi_command_t){
        .len       = 0,
        .csaat     = true,
        .speed     = kSpiSpeedStandard,
        .direction = kSpiDirTxOnly
    });
    spi_set_command(SPI, cmd_read_from_mem);
    spi_wait_for_ready(SPI);

    uint32_t addr_cmd = 0x00000000;
    spi_write_word(SPI, addr_cmd);
    spi_wait_for_ready(SPI);
    uint32_t cmd_address = spi_create_command((spi_command_t){
        .len       = 3,
        .csaat     = true,
        .speed     = kSpiSpeedStandard,
        .direction = kSpiDirTxOnly
    });
    spi_set_command(SPI, cmd_address);
    spi_wait_for_ready(SPI);

    uint32_t dummy_cmd = 0x00000000;
    spi_write_word(SPI, dummy_cmd);
    spi_wait_for_ready(SPI);
    uint32_t cmd_dummy = spi_create_command((spi_command_t){
        .len       = 3,
        .csaat     = true,
        .speed     = kSpiSpeedStandard,
        .direction = kSpiDirTxOnly
    });
    spi_set_command(SPI, cmd_dummy);
    spi_wait_for_ready(SPI);

    uint32_t dummy_cmd_2 = 0x00;
    spi_write_word(SPI, dummy_cmd_2);
    spi_wait_for_ready(SPI);
    uint32_t cmd_dummy_2 = spi_create_command((spi_command_t){
        .len       = 0,
        .csaat     = true,
        .speed     = kSpiSpeedStandard,
        .direction = kSpiDirTxOnly
    });
    spi_set_command(SPI, cmd_dummy_2);
    spi_wait_for_ready(SPI);

    uint32_t *fifo_ptr_rx = SPI->base_addr.base + SPI_HOST_RXDATA_REG_OFFSET;

    dma_set_read_ptr_inc(DMA, (uint32_t) 0);
    dma_set_write_ptr_inc(DMA, (uint32_t) 4);
    dma_set_read_ptr(DMA, (uint32_t) fifo_ptr_rx);
    dma_set_write_ptr(DMA, (uint32_t) data);

    dma_set_spi_mode(DMA, (uint32_t) 3);
    dma_set_data_type(DMA, (uint32_t) 0);
    dma_set_cnt_start(DMA, (uint32_t) byte_count);

    const uint32_t cmd_read_rx = spi_create_command((spi_command_t){
        .len       = byte_count - 1,
        .csaat     = false,
        .speed     = kSpiSpeedStandard,
        .direction = kSpiDirRxOnly
    });
    spi_set_command(SPI, cmd_read_rx);
    spi_wait_for_ready(SPI);

    while(dma_intr_flag == 0) {
        wait_for_interrupt();
    }
}

int main(int argc, char *argv[])
{
    soc_ctrl_t soc_ctrl;
    soc_ctrl.base_addr = mmio_region_from_addr((uintptr_t)SOC_CTRL_START_ADDRESS);
    soc_ctrl_select_spi_host(&soc_ctrl);

    uint32_t core_clk = soc_ctrl_get_frequency(&soc_ctrl);

    CSR_SET_BITS(CSR_REG_MSTATUS, 0x8);
    uint32_t mask = 1 << 19;
    CSR_SET_BITS(CSR_REG_MIE, mask);
    dma_intr_flag = 0;
    CSR_SET_BITS(CSR_REG_MIE, mask);

    spi_host_flash.base_addr = mmio_region_from_addr((uintptr_t)SPI_FLASH_START_ADDRESS);
    spi_set_enable(&spi_host_flash, true);
    spi_output_enable(&spi_host_flash, true);

    dma_t dma;
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

    const uint32_t reset_cmd = 0x11;
    spi_write_word(&spi_host_flash, reset_cmd);
    const uint32_t cmd_reset = spi_create_command((spi_command_t){
        .len        = 0,
        .csaat      = true,
        .speed      = kSpiSpeedStandard,
        .direction  = kSpiDirTxOnly
    });
    spi_set_command(&spi_host_flash, cmd_reset);
    spi_wait_for_ready(&spi_host_flash);

    const uint32_t set_dummy_cycle = 0x07;
    spi_write_word(&spi_host_flash, set_dummy_cycle);
    const uint32_t cmd_set_dummy = spi_create_command((spi_command_t){
        .len        = 0,
        .csaat      = false,
        .speed      = kSpiSpeedStandard,
        .direction  = kSpiDirTxOnly
    });
    spi_set_command(&spi_host_flash, cmd_set_dummy);
    spi_wait_for_ready(&spi_host_flash);

    uint32_t results[32];
    for(uint32_t i = 0; i < 32; i++){
        results[i] = 0;
    }

    read_from_flash(&spi_host_flash, &dma, results, 4 * 32, FLASH_ADDR);

    for(uint32_t i = 0; i < 32; i++){
        printf("%d: 0x%08X\n\r", i, (unsigned int)results[i]);
    }

    return EXIT_SUCCESS;
}
