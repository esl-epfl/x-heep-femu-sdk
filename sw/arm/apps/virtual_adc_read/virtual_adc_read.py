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
x_heep.compile_app("virtual_adc_read")

# Init the ADC memory
adc = x_heep.init_adc_mem()

# Reset the ADC memory
x_heep.reset_adc_mem(adc)

# Write the ADC memory
x_heep.write_adc_mem(adc)

# Run the application
x_heep.run_app()

# Delete adc
del adc
