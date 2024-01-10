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
x_heep.compile_app("virtual_obi_write")

# Init the OBI memory
obi = x_heep.init_obi_mem()

# Reset the OBI memory
x_heep.reset_obi_mem(obi)

# Run the application
x_heep.run_app()

# Read the OBI memory
obi_read = x_heep.read_obi_mem(obi)
target_read = list()
for i in range(1024):
    target_read.append(i ** 2)
if target_read == obi_read:
    print("Test Passed!")
else:
    print("Test Failed!")

# Delete OBI
del obi
