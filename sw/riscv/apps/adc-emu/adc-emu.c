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

#define ACQUISITION_BLOCK_SIZE() (((INPUT_DATA_LENGTH) - (acquired_data)) > (INPUT_BUFFER_SIZE) ? (INPUT_BUFFER_SIZE) : ((INPUT_DATA_LENGTH) - (acquired_data)))

volatile bool acquiring = false;

typedef enum{
    STATE_ACQ_PROC__INIT,
    STATE_ACQ_PROC__LAUNCH_ACQ_A,
    STATE_ACQ_PROC__LAUNCH_ACQ_B,
    STATE_ACQ_PROC__WAIT_ACQ_A,
    STATE_ACQ_PROC__WAIT_ACQ_B,
    STATE_ACQ_PROC__PROC_A,
    STATE_ACQ_PROC__PROC_B,
    STATE_ACQ_PROC__END,
} state_acq_proc_t;

/**
 * This functions takes the data and returns two values:
 * LPF | HPF
 *
 * LPF: The moving-mean of the signal with a sample window that is a power of 2.
 * HPF: The original signal, subtracted the moving-mean.
*/
static inline void data_processing_old(uint32_t *input, uint32_t size){
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

static inline uint32_t data_processing( uint32_t *input, uint32_t size ){
    uint32_t i;
    uint32_t max = 0;
    for( i = 0; i < size; i ++){
        max = input[i] > max ? input[i] : max;
    }
    return max;
}


/**
 * This is the non-weak implementation of the extended interrupt-handling
 * routine of the virtual ADC.
 */
void vadc_done(){
    acquiring = false;
}

static inline void wait_vadc_done(){
    while( acquiring ){};
}

int main(int argc, char *argv[])
{
    static state_acq_proc_t state_acq_proc = STATE_ACQ_PROC__INIT;
    static uint32_t buffer_A    [INPUT_BUFFER_SIZE];
    static uint32_t buffer_B    [INPUT_BUFFER_SIZE];
    static uint32_t buffer_out  [INPUT_DATA_LENGTH/INPUT_BUFFER_SIZE];

    uint32_t processed_data         = 0;
    uint32_t acquired_data          = 0;
    uint32_t acquisition_size_A     = 0;
    uint32_t acquisition_size_B     = 0;


    // Start the performance counters to report timing and energy
    perf_start();

    // Init the virtual ADC
    vadc_init();

    // Adjust the virtual ADC speed adquisition.
    uint32_t freq = 700 * 1000; // Frequency in Hz
    printf("Target frequency: %d Hz\n", freq);
    freq = set_vadc_clk(freq, CLK_BELOW);
    printf("Frequency achieved: %d Hz\n", freq);


    /*
        For simplicity of this demo the following loop will be implemented with blocking
        functions, although the same idea could be implemented on an FSM or RTOS.
    */



    acquisition_size_A = ACQUISITION_BLOCK_SIZE();
    acquiring = true;
    launch_vadc(buffer_A, WORD_SIZE_BYTES * acquisition_size_A);

    while( processed_data < INPUT_DATA_LENGTH ){

        wait_vadc_done();
        acquired_data += acquisition_size_A;

        if( acquired_data < INPUT_DATA_LENGTH ){
            acquisition_size_B = ACQUISITION_BLOCK_SIZE();
            acquiring = true;
            launch_vadc(buffer_B, WORD_SIZE_BYTES * acquisition_size_B);
        }

        if( processed_data < INPUT_DATA_LENGTH ){
            buffer_out[ processed_data/INPUT_BUFFER_SIZE ] = data_processing(buffer_A, acquisition_size_A);
            processed_data += acquisition_size_A;
        }

        if( acquired_data < INPUT_DATA_LENGTH ){
            wait_vadc_done();
            acquired_data += acquisition_size_B;
        }

        if( acquired_data < INPUT_DATA_LENGTH ){
            acquisition_size_A = ACQUISITION_BLOCK_SIZE();
            acquiring = true;
            launch_vadc(buffer_A, WORD_SIZE_BYTES * acquisition_size_A);
        }

        if( processed_data < INPUT_DATA_LENGTH ){
            buffer_out[ processed_data/INPUT_BUFFER_SIZE ] = data_processing(buffer_B, acquisition_size_B);
            processed_data += acquisition_size_B;
        }
    }

    // Stops the transaction
    vadc_deinit();

    // Stop the performance counters.
    perf_stop();

    // Send back the result.
    write_result(buffer_out, INPUT_DATA_LENGTH/INPUT_BUFFER_SIZE);

    return EXIT_SUCCESS;

}
