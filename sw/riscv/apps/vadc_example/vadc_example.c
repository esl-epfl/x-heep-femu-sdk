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

#define ACQUISITION_BLOCK_SIZE() (((VADC_ACQUISITION_SAMPLES) - (acquired_data)) > (X_HEEP_SAMPLING_BUFFER_SAMPLES) ? (X_HEEP_SAMPLING_BUFFER_SAMPLES) : ((VADC_ACQUISITION_SAMPLES) - (acquired_data)))

#if ENABLE_PRINTF
    #define PRINTF(fmt, ...)    printf(fmt, ## __VA_ARGS__)
#else
    #define PRINTF(...)
#endif

volatile bool acquiring = false;

/**
 * Takes data from an input buffer and returns the result of some processing.
 */
static inline uint32_t data_processing( uint32_t *input, uint32_t size ){
    uint16_t i;
    uint32_t data   = 0;
    uint32_t data_A = 0;
    uint32_t data_B = 0;
    uint32_t max_A  = 0;
    uint32_t max_B  = 0;

    for( i = 0; i < size; i ++){
        data = input[i];

        data_A =  data & ADC_CH_DATA_MASK;
        max_A = data_A > max_A ? data_A : max_A;

        data_B = (data >> WORD_SIZE_BITS) & ADC_CH_DATA_MASK; // The current value to compute the mean
        max_B = data_B > max_B ? data_B : max_B ;
    }
    return (max_A & ADC_CH_DATA_MASK) | ((max_B & ADC_CH_DATA_MASK) << WORD_SIZE_BITS);
}

/**
 * Print results throug the UART so the processing system of the FPGA can read them
 * None
 */
void write_result(uint32_t* data, uint32_t size){

    // Sequence header
    PRINTF("Output\n");

    // Data to send
    for(uint32_t i = 0; i < size; i++){
        PRINTF("%02d\n", data[i]);
    }

    // Sequence tail
    PRINTF("End\n");

    return;
}



/**
 * This is the non-weak implementation of the extended interrupt-handling
 * routine of the virtual ADC.
 */
void vadc_done(){
    acquiring = false;
}

/**
 * Waits for the vADC to finish its acquisition in a blocking mode.
 * @ToDo: Send X-HEEP to sleep
 */
static inline void wait_vadc_done(){
    while( acquiring ){};
}

/**
 * Interleave acquisition and processing of the data received from the vADC over two buffers.
 * For the whole duration of the acquisition the DMA will copy data obtained from the vADC into
 * one buffer while the CPU processes data on the other. Results are stored in a third buffer.
 */
static inline void acquire_and_process( uint32_t *buffer_A, uint32_t *buffer_B, uint32_t *buffer_out){
    uint32_t processed_data         = 0;
    uint32_t acquired_data          = 0;
    uint32_t acquisition_size_A     = 0;
    uint32_t acquisition_size_B     = 0;

    acquisition_size_A = ACQUISITION_BLOCK_SIZE();
    acquiring = true;
    launch_vadc(buffer_A, WORD_SIZE_BYTES * acquisition_size_A);

    while( processed_data < VADC_ACQUISITION_SAMPLES ){

        wait_vadc_done();
        acquired_data += acquisition_size_A;

        if( acquired_data < VADC_ACQUISITION_SAMPLES ){
            acquisition_size_B = ACQUISITION_BLOCK_SIZE();
            acquiring = true;
            launch_vadc(buffer_B, WORD_SIZE_BYTES * acquisition_size_B);
        }

        if( processed_data < VADC_ACQUISITION_SAMPLES ){
            buffer_out[ processed_data/X_HEEP_SAMPLING_BUFFER_SAMPLES ] = data_processing(buffer_A, acquisition_size_A);
            processed_data += acquisition_size_A;
        }

        if( acquired_data < VADC_ACQUISITION_SAMPLES ){
            wait_vadc_done();
            acquired_data += acquisition_size_B;
        }

        if( acquired_data < VADC_ACQUISITION_SAMPLES ){
            acquisition_size_A = ACQUISITION_BLOCK_SIZE();
            acquiring = true;
            launch_vadc(buffer_A, WORD_SIZE_BYTES * acquisition_size_A);
        }

        if( processed_data < VADC_ACQUISITION_SAMPLES ){
            buffer_out[ processed_data/X_HEEP_SAMPLING_BUFFER_SAMPLES ] = data_processing(buffer_B, acquisition_size_B);
            processed_data += acquisition_size_B;
        }
    }
}


int main(int argc, char *argv[])
{
    // The two buffers used to interleave the acquisition and processing of input data.
    static uint32_t buffer_A    [X_HEEP_SAMPLING_BUFFER_SAMPLES];
    static uint32_t buffer_B    [X_HEEP_SAMPLING_BUFFER_SAMPLES];
    // The buffer used to store the results of the processing.
    static uint32_t buffer_out  [VADC_ACQUISITION_SAMPLES/X_HEEP_SAMPLING_BUFFER_SAMPLES];

    // Start the performance counters to report timing and energy
    perf_start();

    // Init the virtual ADC
    vadc_init();

    // Adjust the virtual ADC speed adquisition.
    uint32_t freq = set_vadc_clk(VADC_SAMPLING_FREQ_HZ, CLK_BELOW);
    PRINTF("Sampling frequency: %d Hz\n", freq);

    // Interleave between to buffers to acquire data and process it.
    // The result of the processing is stored in buffer_out to be transmitted back
    // into the FEMU.
    acquire_and_process(buffer_A, buffer_B, buffer_out);

    // Stops the transaction
    vadc_deinit();

    // Stop the performance counters.
    perf_stop();

    // Send back the result.
    write_result(buffer_out, VADC_ACQUISITION_SAMPLES/X_HEEP_SAMPLING_BUFFER_SAMPLES);

    return EXIT_SUCCESS;

}
