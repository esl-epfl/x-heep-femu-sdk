# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Simone Machetti - simone.machetti@epfl.ch


from pynq import MMIO
from pynq import allocate

class Flash():
    def __init__(self, x_heep):
        # Allocate Flash
        self.flash = allocate(shape=(32768,))
        # Write Flash base address to AXI address adder
        self.FLASH_AXI_ADDRESS_ADDER_OFFSET = x_heep.address_map["AXI_S_FLASH"]
        axi_address_adder = MMIO(self.FLASH_AXI_ADDRESS_ADDER_OFFSET, 0x4)
        axi_address_adder.write(0x0, self.flash.physical_address)
        # Reset Flash
        self.flash[:] = 0

    def reset_flash(self):
        # Reset Flash
        self.flash[:] = 0

    def write_flash(self):
        # Write Flash from binary file
        file = open("/home/xilinx/x-heep-femu-sdk/sw/riscv/build/flash_in.bin", mode="rb")
        file_byte = file.read()
        for i in range(int(len(file_byte)/4)):
            self.flash[i] = (file_byte[i*4+3] << 24) | (file_byte[i*4+2] << 16) | (file_byte[i*4+1] << 8) | file_byte[i*4];
        file.close()

    def read_flash(self):
        # Read Flash to binary file
        file = open("/home/xilinx/x-heep-femu-sdk/sw/riscv/build/flash_out.bin", mode="wb")
        byte_array = bytearray(self.flash)
        file.write(byte_array)
        file.close()

    def release_mem(self):
        self.flash.freebuffer()