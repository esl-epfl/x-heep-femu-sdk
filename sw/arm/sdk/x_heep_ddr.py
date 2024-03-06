# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Simone Machetti - simone.machetti@epfl.ch


from pynq import MMIO
from pynq import allocate

OBI_AXI_ADDRESS_ADDER_OFFSET = 0x43C10000

class DDR():
    def init(self, mem_size):
        # Allocate DDR memory
        # Default DDR dtype is 32 bit unsigned, which is of size 4B.
        self.ddr = allocate(shape=(int(1048576*mem_size/4),))
        # Write DDR memory base address to AXI address adder
        axi_address_adder = MMIO(OBI_AXI_ADDRESS_ADDER_OFFSET, 0x4)
        axi_address_adder.write(0x0, self.ddr.physical_address)
        # Reset DDR memory
        self.ddr[:] = 0

    def read_ddr_mem(self):
        # Read DDR memory
        return list(self.ddr)

    def release_ddr_mem(self):
        self.ddr.freebuffer()