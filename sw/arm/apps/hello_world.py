# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Simone Machetti - simone.machetti@epfl.ch

from pynq import x_heep                 # Import the X-HEEP Python class
x_heep = x_heep()                       # Load the X-HEEP bitstream
x_heep.compile_app("hello_world")   # Compile the application
x_heep.run_app();                       # Run the application

# Verify the output
stdout_path = "/home/xilinx/x-heep-femu-sdk/sw/riscv/build/stdout.txt"
expected_output = "Hello World!"
f = open(stdout_path, "r")
if f.read().strip() == expected_output:
    print("Test Passed!")
else:
    print("Test Failed!")