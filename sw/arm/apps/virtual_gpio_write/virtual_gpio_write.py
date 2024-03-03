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
x_heep.compile_app("virtual_gpio_write")

# Run the application
x_heep.run_app()

# Compare the results
bit_array_read = ""
bit_array_expected = "101010101010101010101010101010"

for gpio_pin in range(30):
    pin_read = x_heep.GPIO_read(gpio_pin+8)
    bit_array_read += str(pin_read)
print(bit_array_read)

if bit_array_read == bit_array_expected:
    print("Test Passed!")
else:
    print("Test Failed!")
