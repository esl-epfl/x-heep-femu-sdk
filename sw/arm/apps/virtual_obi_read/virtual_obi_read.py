# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Simone Machetti - simone.machetti@epfl.ch

# Import the X-HEEP Python class
from pynq import x_heep

# Load the X-HEEP bitstream
x_heep = x_heep()

# Compile the application
x_heep.compile_app("virtual_obi_read")

# Init the OBI memory
obi = x_heep.init_obi_mem()

# Reset the OBI memory
x_heep.reset_obi_mem(obi)

# Write to the OBI memory
write_list = list()
for i in range(1024):
    write_list.append(i ** 2)
x_heep.write_obi_mem(write_list, obi)

# Run the application
x_heep.run_app()

# Release the allocated memory
x_heep.release_mem(obi)

# Delete OBI
del obi

# Verify the output
stdout_path = "/home/xilinx/x-heep-femu-sdk/sw/riscv/build/stdout.txt"
expected_output = "Read operation successful."
f = open(stdout_path, "r")
if f.read().strip() == expected_output:
    print("Test Passed!")
else:
    print("Test Failed!")
