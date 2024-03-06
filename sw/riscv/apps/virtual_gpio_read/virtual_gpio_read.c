/*
* Copyright 2023 EPFL
* Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
* SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
*
* Author: Deniz Kasap - deniz.kasap@epfl.ch
*/

#include <stdio.h>
#include <stdlib.h>
#include "csr.h"
#include "hart.h"
#include "handler.h"
#include "core_v_mini_mcu.h"
#include "gpio.h"

int main(int argc, char *argv[])
{
    gpio_params_t gpio_params;
    gpio_t gpio;
    gpio_result_t gpio_res;

    //Start writing to GPIO of Always-On Peripheral [7:0]
    gpio_params.base_addr = mmio_region_from_addr((uintptr_t)GPIO_AO_START_ADDRESS);
    bool read_from_pin;

    for (int i=2; i < 8; i++){ //Skip first 2 GPIO's since they are alread used
        gpio_res = gpio_init(gpio_params, &gpio);
        gpio_res = gpio_input_enabled(&gpio, i, true);
        gpio_res = gpio_read(&gpio, i, &read_from_pin);
        if (read_from_pin != 1){
            printf("An element does not match!");
            printf("Not matching at GPIO-AO at pin %d", i);
            return EXIT_FAILURE;
        }
    }

    //Start writing to GPIO of Peripheral [31:8]
    gpio_params.base_addr = mmio_region_from_addr((uintptr_t)GPIO_START_ADDRESS);

    for (int i=8; i < 32; i++){
        gpio_res = gpio_init(gpio_params, &gpio);
        gpio_res = gpio_input_enabled(&gpio, i, true);
        gpio_res = gpio_read(&gpio, i, &read_from_pin);
        if (read_from_pin != 1){
            printf("An element does not match!");
            printf("Not matching at GPIO at pin %d", i);
            return EXIT_FAILURE;
        }
    }

    printf("Read operation successful.");

    return EXIT_SUCCESS;
}
