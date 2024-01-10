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
x_heep.compile_app("virtual_adc_write")

# Init the ADC memory
adc = x_heep.init_adc_mem()

# Reset the ADC memory
x_heep.reset_adc_mem(adc)

# Run the application
x_heep.run_app()

# Read the ADC memory
x_heep.read_adc_mem(adc)

# Delete adc
del adc

# Verify the output
file_expected = open("/home/xilinx/x-heep-femu-sdk/sw/riscv/build/adc_out.bin", mode="rb")
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
