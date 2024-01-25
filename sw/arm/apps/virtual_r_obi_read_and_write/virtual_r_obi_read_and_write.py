# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Deniz Kasap - deniz.kasap@epfl.ch

# Import the X-HEEP Python class
from pynq import x_heep

# Load the X-HEEP bitstream
x_heep = x_heep()

# Choose the X-HEEP memory bank
# First bank  = 0
# Second bank = 1
# Third bank  = 2
# Fourth bank = 3
x_heep.init_r_obi(2)

# Write the memory bank
for a,b in enumerate(range(0,0x00010000,0x00000004)):
    data = a ** 2
    x_heep.write_r_obi(data, b, 0x00010000)

# Read the memory bank and compare
allMatch = True
for a,b in enumerate(range(0,0x00008000,0x00000004)):
    data_read = x_heep.read_r_obi(b, 0x00008000)
    if data_read != a**2:
        allMatch = False
        break

if allMatch:
    print("Test Passed!")
else:
    print("Test Failed!")
