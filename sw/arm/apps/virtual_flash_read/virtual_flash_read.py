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

# Delete flash
del flash
