/*
* Copyright 2023 EPFL
* Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
* SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
*
* Author: Simone Machetti - simone.machetti@epfl.ch
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
    gpio_params.base_addr = mmio_region_from_addr((uintptr_t)GPIO_AO_START_ADDRESS);
    gpio_res = gpio_init(gpio_params, &gpio);

    gpio_res = gpio_output_set_enabled(&gpio, 1, true);
    gpio_write(&gpio, 1, true);

    printf("Hello World!\n\r");

    gpio_write(&gpio, 1, false);

    return EXIT_SUCCESS;
}
