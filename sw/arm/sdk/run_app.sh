# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Simone Machetti - simone.machetti@epfl.ch

#!/bin/bash

# Quit screen sessions
pkill screen
sudo pkill screen

# Run UART
cd /home/xilinx/x-heep-femu-sdk/sw/arm/tools/uart/
sudo ./run_uart.sh
cd - > /dev/null 2>&1

# Run OpenOCD
cd /home/xilinx/x-heep-femu-sdk/sw/arm/tools/openocd
sudo ./run_openocd.sh
cd - > /dev/null 2>&1

# Run GDB
cd /home/xilinx/x-heep-femu-sdk/sw/arm/tools/gdb

if [ $# -eq 0 ]
then
	sudo ./run_gdb.sh all > /dev/null 2>&1
	res=$?
elif [ $1 = "debug" ]
then
	sudo ./run_gdb.sh debug
	res=$?
else
	echo "Wrong parameter!"
fi

cd - > /dev/null 2>&1

# Quit OpenOCD
sudo screen -X -S openocd quit

# Quit UART
sudo screen -X -S uart quit
cat /home/xilinx/x-heep-femu-sdk/sw/riscv/build/stdout.txt
exit $res