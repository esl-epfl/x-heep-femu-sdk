# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Simone Machetti - simone.machetti@epfl.ch

#!/bin/bash

# Quit screen sessions
pkill screen
sudo pkill screen

# Compile application
cd /home/xilinx/x-heep-femu-sdk/sw/riscv/
make clean apps/$1/$1.bin
make apps/$1/$1.dis
mkdir build
mv apps/$1/$1.bin build/code.bin
mv apps/$1/$1.elf build/code.elf
mv apps/$1/$1.dis build/code.dis
mv apps/$1/$1.map build/code.map
if [ -f apps/$1/flash_in.bin ]; then
    cp apps/$1/flash_in.bin build/flash_in.bin
fi
if [ -f apps/$1/adc_in.bin ]; then
    cp apps/$1/adc_in.bin build/adc_in.bin
fi
cd - > /dev/null 2>&1
