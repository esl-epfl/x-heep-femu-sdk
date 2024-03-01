# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Deniz Kasap - deniz.kasap@epfl.ch

# Import the X-HEEP Python class
from pynq import x_heep

# Load the X-HEEP bitstream
x_heep = x_heep()

# Initialize DDR memory with desired MB size
ddr = x_heep.init_ddr_mem(10)

# Compile the application
x_heep.compile_app("virtual_ddr")

# Run the application
x_heep.run_app()

# Read the DDR memory
ddr_read = x_heep.read_ddr_mem(ddr)

# Compare program outputs
expected = int(0xABABABAB)
test_passed = True
for a in range(4096):
    if ddr_read[a] != expected:
        test_passed = False
        break
        
if test_passed:
    print("Test Passed!")
else:
    print("Test Failed!")

# Release the allocated DDR memory
x_heep.release_mem(ddr)