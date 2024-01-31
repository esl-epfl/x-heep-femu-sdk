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
 * @brief Initializes the virtual ADC through the SPI
 * @retval None
 */
void vadc_init();

/**
 * @brief Initiates one continuous transactions with the virtual ADC through
 * the SPI using the DMA to trasfer the data to the memory.
 * @param SPI Pointer to the SPI controller 
 * @param DMA Pointer to the DMA controller 
 * @param data Pointer to where data will be collected from the virtual ADC
 * @param byte_count Number of bytes to be trasfered
 * @param addr Base address of the Virtual ADC (BRAM)
 * @retval None
 */
void vadc_get_data_dma(uint32_t *data, uint32_t byte_count);

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