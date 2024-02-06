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

#include <stdio.h>
#include <stdlib.h>

#include "perf.h"
#include "core_v_mini_mcu.h" // For the base address

/****************************************************************************/
/**                                                                        **/
/*                        DEFINITIONS AND MACROS                            */
/**                                                                        **/
/****************************************************************************/

#define PERF_GPIO 1

#define ENABLE_PRINTF 	1
#define OUTPUT_START_SEQ 	"# "
#define OUTPUT_DIVIDER 	"|"
#define OUTPUT_END_SEQ 	"#---"

#if ENABLE_PRINTF
    #define PRINTF(fmt, ...)    printf(fmt, ## __VA_ARGS__)
#else
    #define PRINTF(...)
#endif

/****************************************************************************/
/**                                                                        **/
/*                        TYPEDEFS AND STRUCTURES                           */
/**                                                                        **/
/****************************************************************************/

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
    * GPIO peripheral
    */
    gpio_params_t gpio_params;

    /**
    * GPIO
    */
    gpio_t gpio;

}perf_cb;

/****************************************************************************/
/**                                                                        **/
/*                           EXPORTED FUNCTIONS                             */
/**                                                                        **/
/****************************************************************************/

void perf_start(){
    gpio_result_t gpio_res;

    perf_cb.gpio_params.base_addr = mmio_region_from_addr((uintptr_t)GPIO_AO_START_ADDRESS);
    gpio_res = gpio_init(perf_cb.gpio_params, &perf_cb.gpio);

    gpio_res = gpio_output_set_enabled(&perf_cb.gpio, PERF_GPIO, true);
    gpio_write(&perf_cb.gpio, 1, true);
}

void perf_stop(){
    gpio_write(&perf_cb.gpio, PERF_GPIO, false);
}

void write_result(uint32_t* data, uint32_t size){

    // Sequence header
    PRINTF("%sOutput\n",OUTPUT_START_SEQ);

    // Data to send
    for(uint32_t i = 0; i < size; i++){
        PRINTF("%02d\n", data[i]);
    }

    // Sequence tail
    PRINTF("%s\n",OUTPUT_END_SEQ);

    return;
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