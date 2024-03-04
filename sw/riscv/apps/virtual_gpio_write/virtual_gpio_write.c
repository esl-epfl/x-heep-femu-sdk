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
    
    for (int i=2; i < 8; i++){ //Skip first 2 GPIO's since they are alread used
        gpio_res = gpio_init(gpio_params, &gpio);
        gpio_res = gpio_output_set_enabled(&gpio, i, true);
        if (i % 2 == 0){
            gpio_write(&gpio, i, true);
            printf("Written true to pin %i \n", i);
        }else{
            gpio_write(&gpio, i, false);
            printf("Written false to pin %i \n", i);
        }
    }
    
    //Start writing to GPIO of Peripheral [31:8]
    gpio_params.base_addr = mmio_region_from_addr((uintptr_t)GPIO_START_ADDRESS);
    
    for (int i=8; i < 32; i++){
        gpio_res = gpio_init(gpio_params, &gpio);
        gpio_res = gpio_output_set_enabled(&gpio, i, true);
        if (i % 2 == 0){
            gpio_write(&gpio, i, true);
            printf("Written true to pin %i \n", i);
        }else{
            gpio_write(&gpio, i, false);
            printf("Written false to pin %i \n", i);
        }
    }
    printf("Write operation successful.");

    return EXIT_SUCCESS;
}
