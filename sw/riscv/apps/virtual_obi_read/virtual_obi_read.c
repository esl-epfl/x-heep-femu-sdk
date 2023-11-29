/*
* Copyright 2023 EPFL
* Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
* SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
*
* Author: Simone Machetti - simone.machetti@epfl.ch
*/

#include <stdio.h>
#include <stdlib.h>
#include "core_v_mini_mcu.h"

int main(int argc, char *argv[])
{
    printf("Started!\n\r");
    
    unsigned int* pointer = (unsigned int*)EXT_SLAVE_START_ADDRESS;
    unsigned int value = *pointer;
    
    for (int i=0; i < 1024; i++){
        value = *pointer;
        if (value != i * i){
            printf("An element does not match!");
            printf("Not Matching!: %d -- %d", value, i*i);
            return 1;
        }
        pointer++; 
    }
    
    printf("Read operation successful!");
    return EXIT_SUCCESS;
}
