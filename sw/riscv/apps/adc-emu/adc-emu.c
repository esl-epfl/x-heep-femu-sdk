/*
* Copyright 2023 EPFL
* Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
* SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
*
* Author: Simone Machetti - simone.machetti@epfl.ch
*/

#include <stdio.h>
#include <stdlib.h>
#include "gpio.h"
#include "core_v_mini_mcu.h"

#include "vadc.h"
#include "definitions.h"

#if ENABLE_PRINTF
    #define PRINTF(fmt, ...)    printf(fmt, ## __VA_ARGS__)
#else
    #define PRINTF(...)
#endif

gpio_params_t gpio_params;
gpio_t gpio;
gpio_result_t gpio_res;
uint32_t data[INPUT_DATA_LENGTH];

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
    for(uint32_t i = 0; i < INPUT_DATA_LENGTH; i++){
        x = data[i];
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
}

static inline void write_result(){
    // Sequence header
    PRINTF("%sIN\n",OUTPUT_START_SEQ);

    // Data to send
    for(uint32_t i = 0; i < INPUT_DATA_LENGTH; i++){
        PRINTF("%02d\n", data[i]);
    }

    // Sequence tail
    PRINTF("%s\n",OUTPUT_END_SEQ);

    return;
}

int main(int argc, char *argv[])
{
    // Start the performance counters to report timing and energy
    perf_start();
    
    // Init the virtual ADC
    vadc_init();

    // Obtain the data (simulating obtaining a buffer from the ADC)
    vadc_get_data_dma(data, 4 * INPUT_DATA_LENGTH);

    // Perform a LPF and HPF to the signal
    lpf_hpf();

    // Stop the performance counters.
    perf_stop();

    // Send back the result.
    write_result();

    return EXIT_SUCCESS;

}
