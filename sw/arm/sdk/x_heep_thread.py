# Copyright 2024 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Juan Sapriza - juan.sapriza@epfl.ch

import threading

def thread_start( verbose, thread_process ):
    stop_flag = threading.Event()   # Create a stop flag to halt the process later
    # Create the thread running the selected process
    thread = threading.Thread( target=thread_process,  args=(stop_flag, verbose) )
    thread.start() # Launch the thread
    return thread, stop_flag

def thread_stop( thread, stop_flag ):
    stop_flag.set() # Set the stop flag to stop the thread
    thread.join()   # Wait for the thread to finish