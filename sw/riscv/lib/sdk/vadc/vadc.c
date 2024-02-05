/*
                              *******************
******************************* C SOURCE FILE *****************************
**                            *******************
**
** project  : X-HEEP-FEMU
** filename : vadc.c
** version  : 1
** date     : 31/01/24
**
***************************************************************************
**
** Copyright (c) EPFL contributors.
** All rights reserved.
**
***************************************************************************
*/

/***************************************************************************/
/***************************************************************************/
/**
* @file   vadc.c
* @date   31/01/24
* @brief  Virtual ADC SDK to set up the SPI and use the Virtual ADC in FEMU
*/

/****************************************************************************/
/**                                                                        **/
/*                             MODULES USED                                 */
/**                                                                        **/
/****************************************************************************/

#include "vadc.h"
#include "handler.h" // For defining the DMA handler
#include "core_v_mini_mcu.h" // For the base address

/* To manage interrupts. */
#include "fast_intr_ctrl.h"
#include "csr.h"
#include "stdasm.h"

/****************************************************************************/
/**                                                                        **/
/*                        DEFINITIONS AND MACROS                            */
/**                                                                        **/
/****************************************************************************/

/**
 * Inverts the byte order of an address for PSI transaction
 */
#define REVERT_32b_ADDR(addr) ((((uint32_t)addr & 0xff000000) >> 24) | (((uint32_t)addr & 0x00ff0000) >> 8) | (((uint32_t)addr & 0x0000ff00) << 8) | (((uint32_t)addr & 0x000000ff) << 24))

/**
 * Maximum frequency of the VADC
 */
#define VADC_CLK_MAX_HZ (133 * 1000 * 1000)

/****************************************************************************/
/**                                                                        **/
/*                        TYPEDEFS AND STRUCTURES                           */
/**                                                                        **/
/****************************************************************************/

/**
 * Comands allowed by the Virtual ADC (SPI2 SPI bridge)
 * Registers
 *  - Reg0: The bit 0 specifies if Quad SPI is used (not tested)
 *  - Reg1: The number of dummy cycles necessary access data per transaction
 *  - Reg2: Lower bits of the wrap-around adress
 *  - Reg3: Upper bits of the wrap-around adress
 */
typedef enum
{
    /**
     * Writes to the ADC data buffer (BRAM)
    */
    WRITE_MEM_CMD       = 0x02,
    /**
     * Reads from the ADC data buffer (BRAM)
    */
    READ_MEM_CMD        = 0x0B,
    /**
     * Writes to the reg0 of the VADC controller (SPI2AXI bridge)
    */
    WRITE_REG0_CMD      = 0x01,
    /**
     * Reads from the reg0 of the VADC controller (SPI2AXI bridge)
    */
    READ_REG0_CMD       = 0x05,
    /**
     * Writes to the reg1 of the VADC controller (SPI2AXI bridge)
    */
    WRITE_REG1_CMD      = 0x11,
    /**
     * Reads from the reg1 of the VADC controller (SPI2AXI bridge)
    */
    READ_REG1_CMD       = 0x07,
    /**
     * Writes to the reg2 of the VADC controller (SPI2AXI bridge)
    */
    WRITE_REG2_CMD      = 0x20,
    /**
     * Reads from the reg2 of the VADC controller (SPI2AXI bridge)
    */
    READ_REG2_CMD       = 0x21,
    /**
     * Writes to the reg3 of the VADC controller (SPI2AXI bridge)
    */
    WRITE_REG3_CMD      = 0x30,
    /**
     * Reads from the reg3 of the VADC controller (SPI2AXI bridge)
    */
    READ_REG3_CMD       = 0x31
    
} vadc_cmd;

/****************************************************************************/
/**                                                                        **/
/*                      PROTOTYPES OF LOCAL FUNCTIONS                       */
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/*                           EXPORTED VARIABLES                             */
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/*                            GLOBAL VARIABLES                              */
/**                                                                        **/
/****************************************************************************/

/**
 * Control Block with the other peripherals used to configure the Virtual ADC
 */
static struct
{
    /**
    * SOC CTRL peripheral
    */
    soc_ctrl_t soc_ctrl;

    /**
    * SPI peripheral
    */
    spi_host_t spi_host_flash;

    /**
     * DMA peripheral
     */
    dma_t dma;

    /**
     * DMA peripheral
     */
    volatile int8_t dma_intr_flag;

}vadc_cb;


/****************************************************************************/
/**                                                                        **/
/*                           EXPORTED FUNCTIONS                             */
/**                                                                        **/
/****************************************************************************/

/**
 * @brief Initializes the virtual ADC through the SPI
 * @retval None
 */
void handler_irq_fast_dma(void)
{
    fast_intr_ctrl_t fast_intr_ctrl;
    fast_intr_ctrl.base_addr = mmio_region_from_addr((uintptr_t)FAST_INTR_CTRL_START_ADDRESS);
    clear_fast_interrupt(&fast_intr_ctrl, kDma_fic_e);
    vadc_cb.dma_intr_flag = 1;
}

void vadc_init()
{
    vadc_cb.soc_ctrl.base_addr = mmio_region_from_addr((uintptr_t)SOC_CTRL_START_ADDRESS);
    soc_ctrl_select_spi_host(&vadc_cb.soc_ctrl);

    uint32_t core_clk = soc_ctrl_get_frequency(&vadc_cb.soc_ctrl);

    CSR_SET_BITS(CSR_REG_MSTATUS, 0x8);
    uint32_t mask = 1 << 19;
    CSR_SET_BITS(CSR_REG_MIE, mask);
    CSR_SET_BITS(CSR_REG_MIE, mask);

    vadc_cb.spi_host_flash.base_addr = mmio_region_from_addr((uintptr_t)SPI_HOST_START_ADDRESS);
    spi_set_enable(&vadc_cb.spi_host_flash, true);
    spi_output_enable(&vadc_cb.spi_host_flash, true);

    vadc_cb.dma.base_addr = mmio_region_from_addr((uintptr_t)DMA_START_ADDRESS);

    uint16_t clk_div = 0;

    if (VADC_CLK_MAX_HZ < core_clk / 2)
    {
        clk_div = (core_clk / (VADC_CLK_MAX_HZ)-2) / 2;
        if (core_clk / (2 + 2 * clk_div) > VADC_CLK_MAX_HZ)
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
    spi_set_configopts(&vadc_cb.spi_host_flash, 0, chip_cfg_flash);
    spi_set_csid(&vadc_cb.spi_host_flash, 0);

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
    spi_write_word(&vadc_cb.spi_host_flash, WRITE_REG0_CMD);
    spi_set_command(&vadc_cb.spi_host_flash, cmd_bridge);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
    spi_write_word(&vadc_cb.spi_host_flash, 0x00);
    spi_set_command(&vadc_cb.spi_host_flash, cmd_bridge_value);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
    
    // Set the dummy address (reg1)
    spi_write_word(&vadc_cb.spi_host_flash, WRITE_REG1_CMD);
    spi_set_command(&vadc_cb.spi_host_flash, cmd_bridge);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
    spi_write_word(&vadc_cb.spi_host_flash, set_dummy_cycle);
    spi_set_command(&vadc_cb.spi_host_flash, cmd_bridge_value);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);

    // Set wrap around (reg3, reg2)
    spi_write_word(&vadc_cb.spi_host_flash, WRITE_REG2_CMD);
    spi_set_command(&vadc_cb.spi_host_flash, cmd_bridge);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
    spi_write_word(&vadc_cb.spi_host_flash, 0x00); // 0xFF
    spi_set_command(&vadc_cb.spi_host_flash, cmd_bridge_value);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);

    spi_write_word(&vadc_cb.spi_host_flash, WRITE_REG3_CMD);
    spi_set_command(&vadc_cb.spi_host_flash, cmd_bridge);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
    spi_write_word(&vadc_cb.spi_host_flash, 0x04); // 0x03
    spi_set_command(&vadc_cb.spi_host_flash, cmd_bridge_value);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
}

void vadc_get_data_dma(uint32_t *data, uint32_t byte_count)
{
    // Setting the DMA
    uint32_t *fifo_ptr_rx = vadc_cb.spi_host_flash.base_addr.base + SPI_HOST_RXDATA_REG_OFFSET;
    dma_set_read_ptr_inc(&vadc_cb.dma, (uint32_t) 0);
    dma_set_write_ptr_inc(&vadc_cb.dma, (uint32_t) 4);
    dma_set_read_ptr(&vadc_cb.dma, (uint32_t) fifo_ptr_rx);
    dma_set_write_ptr(&vadc_cb.dma, (uint32_t) data);
    dma_set_spi_mode(&vadc_cb.dma, (uint32_t) 1);
    dma_set_data_type(&vadc_cb.dma, (uint32_t) 0);
    vadc_cb.dma_intr_flag = 0;
    dma_set_cnt_start(&vadc_cb.dma, (uint32_t) byte_count);

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
    uint32_t dummy_cmd = 0x00000000;
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
    spi_write_word(&vadc_cb.spi_host_flash, read_from_mem);
    spi_set_command(&vadc_cb.spi_host_flash, cmd_read_from_mem);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
    // Address command
    spi_write_word(&vadc_cb.spi_host_flash, addr_cmd);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
    spi_set_command(&vadc_cb.spi_host_flash, cmd_address);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
    // Dummy command
    spi_write_word(&vadc_cb.spi_host_flash, dummy_cmd);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
    spi_set_command(&vadc_cb.spi_host_flash, cmd_dummy);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
    // Receive data
    spi_set_command(&vadc_cb.spi_host_flash, cmd_read_rx);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);

    while(vadc_cb.dma_intr_flag == 0) {
        wait_for_interrupt();
    }
}

/****************************************************************************/
/**                                                                        **/
/*                            LOCAL FUNCTIONS                               */
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/*                                 EOF                                      */
/**                                                                        **/
/****************************************************************************/