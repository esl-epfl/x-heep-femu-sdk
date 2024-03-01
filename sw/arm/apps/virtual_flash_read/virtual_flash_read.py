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
x_heep.compile_app("virtual_flash_read")

# Init the Flash
flash = x_heep.init_flash()

# Reset the Flash
x_heep.reset_flash(flash)

# Write the Flash
x_heep.write_flash(flash)

# Run the application
x_heep.run_app()

# Release the allocated memory
x_heep.release_mem(flash)

# Delete flash
del flash

# Verify the output
file_expected = open("/home/xilinx/x-heep-femu-sdk/sw/riscv/build/flash_in.bin", mode="rb")
expected_byte = file_expected.read()
file_stdout = open("/home/xilinx/x-heep-femu-sdk/sw/riscv/build/stdout.txt", "r")
stdout_byte = file_stdout.readlines()

allEqual = True
for i in range(int(len(expected_byte)/4)):
    written = int((expected_byte[i*4] << 24) | (expected_byte[i*4+1] << 16) | (expected_byte[i*4+2] << 8) | expected_byte[i*4+3])
    read = int(stdout_byte[2*i].strip().split(" ")[1], 16)
    if written != read:
        allEqual = False
        break

if allEqual:
    print("Test Passed!")
else:
    print("Test Failed!")
