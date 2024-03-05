# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Simone Machetti - simone.machetti@epfl.ch

from pynq import Overlay
from pynq import MMIO
from pynq import allocate
import x_heep_thread as xht

import os
import subprocess
import serial


FLASH_AXI_ADDRESS_ADDER_OFFSET = 0x44A00000



class x_heep(Overlay):

    def __init__(self, **kwargs):
        # Load bitstream
        super().__init__("/home/xilinx/x-heep-femu-sdk/hw/x_heep.bit", **kwargs)
        self.uart_data = []
        print("✅ Bitstream loaded")


    def load_bitstream(self):
        # Load bitstream
        x_heep = Overlay("/home/xilinx/x-heep-femu-sdk/hw/x_heep.bit")
        print("✅ Bitstream loaded")
        return x_heep


    def compile_app(self, app_name):
        try:
            # Run the command and capture the output
            result = subprocess.run("/home/xilinx/x-heep-femu-sdk/sw/arm/sdk/compile_app.sh " + app_name,
                                     shell=True,
                                     check=True,
                                     stdout=subprocess.PIPE,
                                     stderr=subprocess.PIPE,
                                     text=True)
            output = result.stdout
            error_output = result.stderr
            if error_output != "":
                print("Error:\n", output, "\n", error_output)
                return False
            else:
                print("✅ Compile SUCCESS")
                return True

        except subprocess.CalledProcessError as e:
            # Handle errors raised by the command
            print("Command failed with return code", e.returncode, "and error output:", e.stderr)

    def run_app(self, verbose=True, perfCounters = None):
        # Start a background thread that reads from the UART
        t, sf = xht.thread_start(verbose, self.thread_process_uart_read )
        # Run the command and capture the output
        result = subprocess.run("/home/xilinx/x-heep-femu-sdk/sw/arm/sdk/run_app.sh",
                                    shell=True,
                                    check=False, # Will not raise an exception is return code is != 0
                                    stdout=subprocess.PIPE,
                                    stderr=subprocess.PIPE,
                                    text=True)
        output = result.stdout
        error_output = result.stderr
        if result.returncode != 0: print("❌ Return FAILED:",result.returncode,"\n", error_output, output)
        else: print("✅ Return SUCCESS\n", output)
        # Stop the background thread that reads from the UART
        xht.thread_stop(t, sf)
        if perfCounters is not None: perfCounters.stop_perf_cnt()
        return output, error_output

    def thread_process_uart_read(self, stop_event, verbose):
        # Background thread reading the input from the UART
        serialPort = serial.Serial(port = "/dev/ttyPS1", baudrate=115200, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)
        self.uart_data = []
        while not stop_event.is_set():
            line = serialPort.readline().decode('utf-8')
            if line != "":
                if verbose: print(line, end="")
                self.uart_data.append(line)

    def run_app_debug(self):
        # Debug application (no Jupyter support)
        os.system("/home/xilinx/x-heep-femu-sdk/sw/arm/sdk/run_app.sh debug")

    def init_flash(self):

        # Allocate Flash
        flash = allocate(shape=(32768,))

        # Write Flash base address to AXI address adder
        axi_address_adder = MMIO(FLASH_AXI_ADDRESS_ADDER_OFFSET, 0x4)
        axi_address_adder.write(0x0, flash.physical_address)

        # Reset Flash
        flash[:] = 0

        return flash


    def reset_flash(self, flash):

        # Reset Flash
        flash[:] = 0


    def write_flash(self, flash):

        # Write Flash from binary file
        file = open("/home/xilinx/x-heep-femu-sdk/sw/riscv/build/flash_in.bin", mode="rb")
        file_byte = file.read()
        for i in range(int(len(file_byte)/4)):
            flash[i] = (file_byte[i*4+3] << 24) | (file_byte[i*4+2] << 16) | (file_byte[i*4+1] << 8) | file_byte[i*4];
        file.close()


    def read_flash(self, flash):

        # Read Flash to binary file
        file = open("/home/xilinx/x-heep-femu-sdk/sw/riscv/build/flash_out.bin", mode="wb")
        byte_array = bytearray(flash)
        file.write(byte_array)
        file.close()


