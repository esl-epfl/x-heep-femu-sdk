# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Simone Machetti - simone.machetti@epfl.ch

#!/bin/bash

screen -S openocd -d -m
screen -r openocd -X stuff $'sudo source /home/xilinx/.bashrc\n'
screen -r openocd -X stuff $'sudo openocd -f /home/xilinx/x-heep-femu-sdk/sw/arm/tools/openocd/gpio_bitbang.cfg\n'
