/*
* Copyright 2023 EPFL
* Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
* SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
*
* Author: Simone Machetti - simone.machetti@epfl.ch
*/

#include <stdio.h>
#include <stdlib.h>

#include "perf.h"
#include "vadc.h"
#include "definitions.h"

/**
 * This functions takes the data and returns two values:
 * LPF | HPF
 *
 * LPF: The moving-mean of the signal with a sample window that is a power of 2.
 * HPF: The original signal, subtracted the moving-mean.
*/
static inline void lpf_hpf(uint32_t *input, uint32_t size){
    uint8_t bits = 5;
    uint32_t m  = input[0];
    uint32_t mb = m << bits;
    uint32_t x = 0;
    uint32_t h = 0;
    uint32_t l = m;

    for(uint32_t i = 1; i < size; i++){
        x = input[i];       // The current value to compute the mean
        mb -= m;            // 4*mean without the last value
        mb += x;            // 4*mean with the new value
        m = mb >> bits;     // The new mean (4*mean/4)
        h = l - m;          // The new HPFd value (signal - mean)
        l = x;              // The value of data[i-1] for the next iteration
        input[i] = m;       // Store in the input the value of its mean
    }
}

int main(int argc, char *argv[])
{
    static uint32_t data_buffer[INPUT_DATA_LENGTH];

    // Start the performance counters to report timing and energy
    perf_start();

    // Init the virtual ADC
    vadc_init();

    // Obtain the data (simulating obtaining a buffer from the ADC)
    vadc_get_data_dma(data_buffer, 4 * INPUT_DATA_LENGTH);

    // Perform a LPF and HPF to the signal
    lpf_hpf(data_buffer, INPUT_DATA_LENGTH);

    // Stop the performance counters.
    perf_stop();

    // Send back the result.
    write_result(data_buffer, INPUT_DATA_LENGTH);

    return EXIT_SUCCESS;

}
