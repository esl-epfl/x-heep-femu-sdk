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
x_heep.compile_app("virtual_flash_write")

# Init the Flash
flash = x_heep.init_flash()

# Reset the Flash
x_heep.reset_flash(flash)

# Run the application
x_heep.run_app()

# Read the Flash
x_heep.read_flash(flash)

# Delete flash
del flash

# Verify the output
file_expected = open("/home/xilinx/x-heep-femu-sdk/sw/riscv/build/flash_out.bin", mode="rb")
expected_byte = file_expected.read()

allEqual = True
for i in range(32):
    written = int((expected_byte[i*4] << 24) | (expected_byte[i*4+1] << 16) | (expected_byte[i*4+2] << 8) | expected_byte[i*4+3])
    if written != i:
        allEqual = False
        break

if allEqual:
    print("Test Passed!")
else:
    print("Test Failed!")
