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
x_heep.compile_app("performance_estimation")

# Init the performance counters
perf_cnt = x_heep.init_perf_cnt()

# Reset the performance counters
x_heep.reset_perf_cnt(perf_cnt)

# Start the performance counters
x_heep.start_perf_cnt_manual(perf_cnt)

# Run the application
x_heep.run_app()

# Stop the performance counters
x_heep.stop_perf_cnt(perf_cnt)

# Read the performance counters
x_heep.read_perf_cnt(perf_cnt)

# Estimate the performance
x_heep.estimate_performance()

# Delete perf_cnt
del perf_cnt

# Verify the output
stdout_path = "/home/xilinx/x-heep-femu-sdk/sw/riscv/build/stdout.txt"
expected_output = "Hello World!"
f = open(stdout_path, "r")
if f.read().strip() == expected_output:
    print("Test Passed!")
else:
    print("Test Failed!")