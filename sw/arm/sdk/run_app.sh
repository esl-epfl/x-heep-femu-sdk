# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Simone Machetti - simone.machetti@epfl.ch

#!/bin/bash

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
# sudo screen -X -S openocd quit
# sudo screen -X quit
sudo killall screen # The previous approaches would, for reasons escaping my understanding, leave screen sessions open

exit $res