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
    
    for (int i=0; i < 30; i++){
        gpio_res = gpio_init(gpio_params, &gpio);
        gpio_res = gpio_output_set_enabled(&gpio, i+2, true);
        if (i % 2 == 0){
            gpio_write(&gpio, i+2, true);
        }else{
            gpio_write(&gpio, i+2, false);
        }
    }

    return EXIT_SUCCESS;
}
