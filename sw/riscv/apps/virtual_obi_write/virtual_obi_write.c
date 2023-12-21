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
    unsigned int* pointer = (unsigned int*)EXT_SLAVE_START_ADDRESS;
    
    int i;
    
    for (i=0; i < 1024; i++){
        *pointer = i*i; //write the squared index to the DDR memory on PS side
        pointer++; 
    }
    
    return EXIT_SUCCESS;
}
