# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Simone Machetti - simone.machetti@epfl.ch

from pynq import MMIO
from pynq import allocate

R_OBI_AXI_BRIDGE_OFFSET            = 0x43C30000
R_OBI_BAA_AXI_ADDRESS_ADDER_OFFSET = 0x43C40000
OBI_AXI_ADDRESS_ADDER_OFFSET       = 0x43C10000

class OBI():

    def __init__(self):
        # Allocate OBI memory
        self.obi = allocate(shape=(1024,))
        # Write OBI memory base address to AXI address adder
        axi_address_adder = MMIO(OBI_AXI_ADDRESS_ADDER_OFFSET, 0x4)
        axi_address_adder.write(0x0, self.obi.physical_address)
        # Reset OBI memory
        self.obi[:] = 0


    def reset_obi_mem(self):
        # Reset OBI memory
        self.obi[:] = 0


    def write_obi_mem(self, write_list):
        # Write OBI memory
        self.obi[:] = write_list


    def read_obi_mem(self):
        # Read OBI memory
        return list(self.obi)

    def release_mem(self):
        self.obi.freebuffer()

class rOBI():

    def __init__(self, memory_bank_id):
        # Write reverse OBI memory base address to AXI address adder
        self.axi_address_adder = MMIO(R_OBI_BAA_AXI_ADDRESS_ADDER_OFFSET, 0x4)
        self.axi_address_adder.write(0x0, 0x00008000 * memory_bank_id)


    def write_r_obi(self, data, offset, width):
        # Write reverse OBI
        reverse_obi_bridge = MMIO(R_OBI_AXI_BRIDGE_OFFSET, width)
        reverse_obi_bridge.write(offset, data)


    def read_r_obi(self, offset, width):
        # Read reverse OBI
        reverse_obi_bridge = MMIO(R_OBI_AXI_BRIDGE_OFFSET, width)
        data_read = reverse_obi_bridge.read(offset)
        return data_read


    def release_mem(self):
        self.axi_address_adder.freebuffer()