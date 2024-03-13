# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Simone Machetti - simone.machetti@epfl.ch

#!/bin/bash

gdb_output=$(sudo /tools/riscv/bin/riscv32-unknown-elf-gdb --command=./$1.init)
return_value=$(echo "$gdb_output" | awk '/\$1 =/ {print $NF}')
exit $return_value
