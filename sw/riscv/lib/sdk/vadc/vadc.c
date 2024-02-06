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
 * Inverts the byte order of a 4 bytes transaction
 */
#define REVERT_32b_ADDR(x) (((uint32_t)x >> 24) | (((uint32_t)x & 0x00ff0000) >> 8) | (((uint32_t)x & 0x0000ff00) << 8) | (((uint32_t)x & 0x000000ff) << 24))

/**
 * Inverts the bytes of a 2 byte transaction
 */
#define REVERT_16b(x) (((uint16_t)x >> 8) | (((uint16_t)x & 0x00ff) << 8))

/**
 * Maximum frequency of the VADC
 * The FPGA can support a maximum of 133MHz with the current design
 */
#define VADC_CLK_MAX_HZ (133 * 1000 * 1000)

/**
 * Base address of the virtual adc
 */
#define VADC_BASE_ADDR REVERT_32b_ADDR(0x00000000)

/**
 * The data to send when summy cycles are occuring
 */
#define DUMMY_DATA 0x00000000

/**
 * Number of waiting bytes (8 cycles) bewteen sending an address to the virtual
 * ADC and receiving the actual data. This delay is due to the SPI2AXI bridge.
 * It has been tested that a minimum number of wating cycles are 2 bytes.
 * The SPI cannot be configured at a cycle (bit) precision, but at
 * byte (8 cycles)
 */
#define DUMMY_BYTES 2U

/**
 * Bytes to cycles (1 to 8) operation
 */
#define B2C(c) ((uint32_t)c << 3)

/**
 * Wrap around when accesing the virtual ADC. The PL allocates a circular
 * buffer of 1KB. Therefore, a wrap around must be done at the address
 * 0x0400 starting from the base address 0x0000. The wrap around address
 * has 2 bytes (16 bits).
 */
#define WRAP_AROUND_ADDR 0x0400

/****************************************************************************/
/**                                                                        **/
/*                        TYPEDEFS AND STRUCTURES                           */
/**                                                                        **/
/****************************************************************************/

/**
 * Comands to read registers of the Virtual ADC (SPI2 SPI bridge)
 * @todo store them as 1 bytes
 */
typedef enum
{
    /**
     * Reads from the reg0 of the VADC controller (SPI2AXI bridge)
    */
    READ_REG0_CMD       = 0x05,
    /**
     * Reads from the reg1 of the VADC controller (SPI2AXI bridge)
    */
    READ_REG1_CMD       = 0x07,
    /**
     * Reads from the reg2 of the VADC controller (SPI2AXI bridge)
    */
    READ_REG2_CMD       = 0x21,
    /**
     * Reads from the reg3 of the VADC controller (SPI2AXI bridge)
    */
    READ_REG3_CMD       = 0x31
    
} reg_read_vadc_cmd;

/**
 * Comands to write registers of the Virtual ADC (SPI2 SPI bridge)
 */
typedef enum
{
    /**
     * Writes to the reg0 of the VADC controller (SPI2AXI bridge)
    */
    WRITE_REG0_CMD      = 0x01,
    /**
     * Reads from the reg0 of the VADC controller (SPI2AXI bridge)
    */
    WRITE_REG1_CMD      = 0x11,
    /**
     * Reads from the reg1 of the VADC controller (SPI2AXI bridge)
    */
    WRITE_REG2_CMD      = 0x20,
    /**
     * Reads from the reg2 of the VADC controller (SPI2AXI bridge)
    */
    WRITE_REG3_CMD      = 0x30
    
} reg_write_vadc_cmd;

/**
 * Comands to access the memory of the Virtual ADC (BRAM)
 * This commans are decoded by the SPI2AXI bridge
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
    READ_MEM_CMD        = 0x0B
} wr_mem_vadc_cmd;

typedef enum
{
    /**
     * Uses QSPI to access the virtual ADC
    */
    QSPI_ON         = 1U,
    /**
     * Uses QSPI to access the virtual ADC
    */
    QSPI_OFF        = 0U
} qspi_t;

/**
 * Wrap arround address splited in two regsiters of one byte each
 */
typedef struct
{
    /**
    * Least Significant Byte
    */
    uint8_t low;
    /**
    * Most Significant Byte
    */
    uint8_t high;

}wrap_around_bytes_t;

/**
 * Wrap arround address structure to access the address and the byte fields
 */
typedef union{
    uint16_t addr;
    wrap_around_bytes_t byte;
}wrap_around_addr_t;

/****************************************************************************/
/**                                                                        **/
/*                      PROTOTYPES OF LOCAL FUNCTIONS                       */
/**                                                                        **/
/****************************************************************************/

/**
 * Writes into the configuration registers of the SPI2AXI bridge in order to
 * use the virtual ADC. The structure of register representing the ones
 * persents in the SPI2AXI bridge of the Virtual ADC.
 * Virtual ADC registers:
 *  - Reg0: The bit 0 specifies if Quad SPI is used (not tested)
 *  - Reg1: The number of dummy cycles necessary access data per transaction
 *  - Reg2: Lower bits of the wrap-around adress
 *  - Reg3: Upper bits of the wrap-around adress
 */
static void set_vadc_config();

/**
 * Controls the writing of a virtual ADC register through the SPI
 */
static void reg_write_vadc(reg_read_vadc_cmd cmd, uint8_t value);

/**
 * Generate SPI commands for the virtual ADC
 */
static void create_spi_cmds();

/**
 * Set the SPI to communicate to the virtual ADC
 */
static void set_spi_vadc_config();

/**
 * Set the SOC to use the SPI
 */
static void set_soc_vadc_config();

/**
 * Set the DMA to capture the SPI data from the virtual ADC
 */
static void set_dma_vadc_config();

/**
 * Set the DMA to transfer data comming form the virtual ADC
 */
static void set_vadc_dma_transaction(uint32_t *data);

/**
 * The header of every virtual ADC transaction:
 * - 1 Byte command
 * - 4 Bytes address
 * - Wating cycles (2 bytes)
 * This header is defined by the SPI2AXI bridge
 */
static void vadc_read_header();

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
    uint32_t vadc_addr;

    /**
     * DMA peripheral
     */
    volatile int8_t dma_intr_flag;

}vadc_cb;

/**
 * Virtual ADC configuration
 */
static struct
{
    /**
    * Quad SPI mode when using the virtual ADC
    */
    qspi_t qspi_mode;

    /**
    * Dummy (wating) cycles when reading data from the virtual ADC. 0 count
    * as a cycle, meaning that the wating cycles are the number specified
    * plus one
    */
    uint8_t dummy_cycles;

    /**
    * Wrap around adress of the virtual ADC
    */
    wrap_around_addr_t wrap_around;

}vadc_config;

/**
 * Commands to send to the virtual ADC throug the SPI
 */
static struct
{
    /**
    * Send 1 byte command to the virtual ADC (keep stransaction)
    */
    uint32_t cmd_send_spi_cmd;

    /**
    * Receive 1 byte value for the the virtual ADC register (end stransaction)
    */
    uint32_t read_reg_value_spi_cmd;

    /**
    * Send 1 byte value for the the virtual ADC register (end stransaction)
    */
    uint32_t write_reg_value_spi_cmd;

    /**
    * Send 4 bytes address to read/write the virtual ADC (keep stransaction)
    */
    uint32_t send_address_spi_cmd;

    /**
    * Send X bytes waiting cycles to the virtual ADC (keep stransaction)
    */
    uint32_t send_dummy_spi_cmd;

    /**
    * Receive X bytes of data from the virtual ADC (end stransaction)
    */
    uint32_t read_data_spi_cmd;

}vadc_spi_cmds;

/****************************************************************************/
/**                                                                        **/
/*                           EXPORTED FUNCTIONS                             */
/**                                                                        **/
/****************************************************************************/

void handler_irq_fast_dma(void)
{
    fast_intr_ctrl_t fast_intr_ctrl;
    fast_intr_ctrl.base_addr = mmio_region_from_addr((uintptr_t)FAST_INTR_CTRL_START_ADDRESS);
    clear_fast_interrupt(&fast_intr_ctrl, kDma_fic_e);
    vadc_cb.dma_intr_flag = 1;
}

void vadc_init()
{
    //Set the SOC to use the SPI
    set_soc_vadc_config();
    
    //Set the DMA to capture the SPI data from the virtual ADC
    set_dma_vadc_config();

    // Set the SPI to communicate to the virtual ADC
    set_spi_vadc_config();

    // Configure the virtual ADC throud the SPI
    set_vadc_config();
}

/**
 * @todo separate init transaction and seding bytes
 * @todo remove wfi and move to the user level
*/
void read_vadc_dma(uint32_t *data_buffer, uint32_t byte_count)
{
    // -- VADC transaction configuraion -- //
    
    // Setting the DMA
    set_vadc_dma_transaction(data_buffer);

    // Receive data
    vadc_spi_cmds.read_data_spi_cmd = spi_create_command((spi_command_t){
        .len        = byte_count - 1,
        .csaat      = false,
        .speed      = kSpiSpeedStandard,
        .direction  = kSpiDirRxOnly
    });

    // Sending the header SPI transaction to the virtual ADC
    vadc_read_header();

    // -- VADC transactions -- //

    // Start SPI transaction
    spi_set_command(&vadc_cb.spi_host_flash, vadc_spi_cmds.read_data_spi_cmd);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
    // Strart DMA transaction
    dma_set_cnt_start(&vadc_cb.dma, (uint32_t) byte_count);

    // -- Wait for transaction to be done -- //

    // Wait for virtual ADC transaction to be completed
    while(vadc_cb.dma_intr_flag == 0) {
        wait_for_interrupt();
    }
}

/****************************************************************************/
/**                                                                        **/
/*                            LOCAL FUNCTIONS                               */
/**                                                                        **/
/****************************************************************************/

void set_vadc_config(){
    // Set the base address of the virtual ADC memory (BRAM)
    vadc_cb.vadc_addr = VADC_BASE_ADDR;

    // Initialze virtual ADC configuration with default values
    vadc_config.qspi_mode = QSPI_OFF;
    vadc_config.dummy_cycles = B2C(DUMMY_BYTES) - 1;
    vadc_config.wrap_around.addr = WRAP_AROUND_ADDR;
    
    // Set normal SPI (reg0)
    reg_write_vadc(WRITE_REG0_CMD, vadc_config.qspi_mode);
    
    // Set the dummy address (reg1)
    reg_write_vadc(WRITE_REG1_CMD, vadc_config.dummy_cycles);

    // Set wrap around (reg2 and reg3)
    reg_write_vadc(WRITE_REG2_CMD, vadc_config.wrap_around.byte.low);
    reg_write_vadc(WRITE_REG3_CMD, vadc_config.wrap_around.byte.high);
}

/**
 * @todo send one single transaction
*/
void reg_write_vadc(reg_read_vadc_cmd cmd, uint8_t value){
    spi_write_word(&vadc_cb.spi_host_flash, (uint32_t) cmd);
    spi_set_command(&vadc_cb.spi_host_flash, vadc_spi_cmds.cmd_send_spi_cmd);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
    spi_write_word(&vadc_cb.spi_host_flash, (uint8_t) value);
    spi_set_command(&vadc_cb.spi_host_flash, vadc_spi_cmds.write_reg_value_spi_cmd);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
}

void create_spi_cmds(){

    /**
    * SPI command to Write/Read command to the virtual ADC through the SPI
    */
    vadc_spi_cmds.cmd_send_spi_cmd               = spi_create_command((spi_command_t){
                                                                        .len        = 0,
                                                                        .csaat      = true,
                                                                        .speed      = kSpiSpeedStandard,
                                                                        .direction  = kSpiDirTxOnly
                                                                    });
    /**
    * SPI command to read the value in a register of the Virtual ACD through the SPI
    */
    vadc_spi_cmds.read_reg_value_spi_cmd         = spi_create_command((spi_command_t){
                                                                        .len        = 0,
                                                                        .csaat      = false,
                                                                        .speed      = kSpiSpeedStandard,
                                                                        .direction  = kSpiDirRxOnly
                                                                    });   
    /**
    * SPI command to send value to read in a register of the Virtual ACD through the SPI
    */
    vadc_spi_cmds.write_reg_value_spi_cmd        = spi_create_command((spi_command_t){
                                                                        .len        = 0,
                                                                        .csaat      = false,
                                                                        .speed      = kSpiSpeedStandard,
                                                                        .direction  = kSpiDirTxOnly
                                                                    });    
    /**
    * SPI command to send memory address to read in the Virtual ACD through the SPI
    */
    vadc_spi_cmds.send_address_spi_cmd           = spi_create_command((spi_command_t){
                                                                        .len        = 3,
                                                                        .csaat      = true,
                                                                        .speed      = kSpiSpeedStandard,
                                                                        .direction  = kSpiDirTxOnly
                                                                    });    
    /**
    * SPI command to send dummy cycles to the virtual ADC
    */                 
    vadc_spi_cmds.send_dummy_spi_cmd             = spi_create_command((spi_command_t){
                                                                        .len        = DUMMY_BYTES - 1,
                                                                        .csaat      = true,
                                                                        .speed      = kSpiSpeedStandard,
                                                                        .direction  = kSpiDirTxOnly
                                                                    });    
}

/**
 * @todo be able to modify frequency
*/
void set_spi_vadc_config(){
    // Set SPI bas address
    vadc_cb.spi_host_flash.base_addr = mmio_region_from_addr((uintptr_t)SPI_HOST_START_ADDRESS);
    spi_set_enable(&vadc_cb.spi_host_flash, true);
    spi_output_enable(&vadc_cb.spi_host_flash, true);

    // Set SPI clock
    uint32_t core_clk = soc_ctrl_get_frequency(&vadc_cb.soc_ctrl);
    uint16_t clk_div = 0;
    if (VADC_CLK_MAX_HZ < core_clk / 2)
    {
        clk_div = (core_clk / (VADC_CLK_MAX_HZ)-2) / 2;
        if (core_clk / (2 + 2 * clk_div) > VADC_CLK_MAX_HZ)
            clk_div += 1;
    }

    // Set SPI config
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

    // Generate SPI commands for the virtual ADC
    create_spi_cmds();
}

void set_soc_vadc_config(){
    // Configure SOC
    vadc_cb.soc_ctrl.base_addr = mmio_region_from_addr((uintptr_t)SOC_CTRL_START_ADDRESS);
    soc_ctrl_select_spi_host(&vadc_cb.soc_ctrl);
}

void set_dma_vadc_config(){
    // Enable DMA fast interrupt
    CSR_SET_BITS(CSR_REG_MSTATUS, 0x8);
    uint32_t mask = 1 << 19;
    CSR_SET_BITS(CSR_REG_MIE, mask);
    CSR_SET_BITS(CSR_REG_MIE, mask);

    // Configure DMA
    vadc_cb.dma.base_addr = mmio_region_from_addr((uintptr_t)DMA_START_ADDRESS);
}

void set_vadc_dma_transaction(uint32_t *data){
    uint32_t *fifo_ptr_rx = vadc_cb.spi_host_flash.base_addr.base + SPI_HOST_RXDATA_REG_OFFSET;
    dma_set_read_ptr_inc(&vadc_cb.dma, (uint32_t) 0);
    dma_set_write_ptr_inc(&vadc_cb.dma, (uint32_t) 4);
    dma_set_read_ptr(&vadc_cb.dma, (uint32_t) fifo_ptr_rx);
    dma_set_write_ptr(&vadc_cb.dma, (uint32_t) data);
    dma_set_spi_mode(&vadc_cb.dma, (uint32_t) 1);
    dma_set_data_type(&vadc_cb.dma, (uint32_t) 0);
    vadc_cb.dma_intr_flag = 0;
}

void vadc_read_header(){
    // Send read ADC command
    spi_write_word(&vadc_cb.spi_host_flash, READ_MEM_CMD);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
    spi_set_command(&vadc_cb.spi_host_flash, vadc_spi_cmds.cmd_send_spi_cmd);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);

    // Send ADC address
    spi_write_word(&vadc_cb.spi_host_flash, vadc_cb.vadc_addr);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
    spi_set_command(&vadc_cb.spi_host_flash, vadc_spi_cmds.send_address_spi_cmd);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);

    // Send dummy (wating) cycles
    spi_write_word(&vadc_cb.spi_host_flash, DUMMY_DATA);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
    spi_set_command(&vadc_cb.spi_host_flash, vadc_spi_cmds.send_dummy_spi_cmd);
    spi_wait_for_ready(&vadc_cb.spi_host_flash);
}

/****************************************************************************/
/**                                                                        **/
/*                                 EOF                                      */
/**                                                                        **/
/****************************************************************************/