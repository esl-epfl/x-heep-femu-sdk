# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Simone Machetti - simone.machetti@epfl.ch

#!/bin/bash

if [ -f /home/xilinx/x-heep-femu-sdk/sw/riscv/build/stdout.txt ] ; then
    sudo rm /home/xilinx/x-heep-femu-sdk/sw/riscv/build/stdout.txt
fi
sudo screen -S uart -d -m -L -Logfile /home/xilinx/x-heep-femu-sdk/sw/riscv/build/stdout.txt /dev/ttyPS1 115200
