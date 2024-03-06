# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Simone Machetti - simone.machetti@epfl.ch

from pynq import x_heep                 # Import the X-HEEP Python class
x_heep = x_heep()                       # Load the X-HEEP bitstream
x_heep.compile_app("hello_world")   # Compile the application
x_heep.run_app();                       # Run the application
