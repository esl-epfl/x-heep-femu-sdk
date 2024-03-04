# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Deniz Kasap - deniz.kasap@epfl.ch

# Import the X-HEEP Python class
from pynq import x_heep
import random

# Load the X-HEEP bitstream
x_heep = x_heep()

# Compile the application
x_heep.compile_app("virtual_gpio_read")

# Write all ones to GPIO pins
for gpio_pin in range(30):
    x_heep.GPIO_write(1, gpio_pin)
    
# Run the application
x_heep.run_app()

# Verify the output
stdout_path = "/home/xilinx/x-heep-femu-sdk/sw/riscv/build/stdout.txt"
expected_output = "Read operation successful."
f = open(stdout_path, "r")
if f.read().strip() == expected_output:
    print("Test Passed!")
else:
    print("Test Failed!")
