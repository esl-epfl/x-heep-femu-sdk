/*
                              *******************
******************************* H HEADER FILE *****************************
**                            *******************
**
** project  : X-HEEP-FEMU
** filename : vadc.h
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
* @file   vadc.h
* @date   31/01/24
* @brief  Virtual ADC SDK to set up the SPI and use the Virtual ADC in FEMU
*/

#ifndef _VADC_SDK_H
#define _VADC_SDK_H

/****************************************************************************/
/**                                                                        **/
/**                            MODULES USED                                **/
/**                                                                        **/
/****************************************************************************/

#include <stddef.h>
#include <stdint.h>

#include "spi_host.h"
#include "spi_host_regs.h"
#include "dma.h"
#include "hart.h"
#include "soc_ctrl.h"

/****************************************************************************/
/**                                                                        **/
/**                       DEFINITIONS AND MACROS                           **/
/**                                                                        **/
/****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************/
/**                                                                        **/
/**                       TYPEDEFS AND STRUCTURES                          **/
/**                                                                        **/
/****************************************************************************/

typedef enum
{
    /**
     * Rounds the target frequency to its nearset value from below
    */
    CLK_BELOW,

    /**
     * Rounds the target frequency to its nearset value from above
    */
    CLK_ABOVE,

    /**
     * Rounds the target frequency to its nearset value
     */
    CLK_NEAREST
} clk_round_t;

/****************************************************************************/
/**                                                                        **/
/**                          EXPORTED VARIABLES                            **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                          EXPORTED FUNCTIONS                            **/
/**                                                                        **/
/****************************************************************************/

/**
 * @brief Initializes the virtual ADC through the SPI. The clock frequency is
 * set to the maximum by default
 * @retval None
 */
void vadc_init();

/**
 * @brief Initializes the virtual ADC through the SPI. The clock frequency is
 * set to the maximum by default
 * @retval None
 */
void vadc_deinit();

/**
 * @brief Initiates one continuous transactions with the virtual ADC through
 * the SPI using the DMA to trasfer the data to the memory.
 * @param data_buffer Pointer to where data will be collected from the virtual ADC
 * @param byte_count Number of bytes to be trasfered
 * @retval None
 */
void launch_vadc(uint32_t *data_buffer, uint32_t byte_count);

/**
 * @brief Set the clk for the spi transactions with the spi.
 * @param target_freq Target clock frequency in Hz for the SPI communication
 * with the virtual ADC
 * @param round_type If the target frequency cannot be achieved, it will be
 * set to the nearset frequency BELOW, ABOVE or NEAREST.
 * @retval The actual clock frequency (in Hz) at with the virtual adc was
 * configured
 */
uint32_t set_vadc_clk(uint32_t target_freq, clk_round_t round_type);

/****************************************************************************/
/**                                                                        **/
/**                          INLINE FUNCTIONS                              **/
/**                                                                        **/
/****************************************************************************/
#ifdef __cplusplus
} // extern "C"
#endif

#endif /* _VADC_SDK_H */
/****************************************************************************/
/**                                                                        **/
/**                                EOF                                     **/
/**                                                                        **/
/****************************************************************************/