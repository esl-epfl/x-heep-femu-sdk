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

# Init the OBI
obi = x_heep.init_obi()

# Reset the OBI Memory
x_heep.reset_obi(obi)

#Write the OBI Memory
write_list = list()
for i in range(1024):
    write_list.append(i ** 2)
x_heep.write_obi_memory(write_list, obi)

#Check if OBI memory is as desired
obi_read = x_heep.read_obi(obi)

# Run the application
x_heep.run_app()

# Delete OBI
del obi
