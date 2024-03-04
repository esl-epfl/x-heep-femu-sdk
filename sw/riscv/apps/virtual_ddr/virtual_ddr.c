/*
* Copyright 2023 EPFL
* Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
* SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
*
* Author: Deniz Kasap - deniz.kasap@epfl.ch
*/

#include <stdio.h>
#include <stdlib.h>

__attribute__((section(".ram_ext"))) unsigned int test_array[4096] = {[0 ... 4095] = 0xABABABAB};

int main(int argc, char *argv[])
{
    for(int i=0; i<4096; i++)
    {
        printf("0x%X", (unsigned int)test_array[i]);
    }
    return EXIT_SUCCESS;
}
