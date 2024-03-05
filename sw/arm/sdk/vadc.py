# Copyright 2024 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Ruben Rodriguez - ruben.rodriguezalvarez@epfl.ch

from pynq import MMIO
from pynq import allocate
import threading
import math

VIRTUAL_ADC_OFFSET = 0x80000000
ADC_OFFSET = 0x40000000

class vADC():

    def __init__(self, bin_file_name, DDR_buffer_size_64B=512):
        # Create a stop flag to halt the process later
        self.stop_flag = threading.Event()

        # Create and program the virtual ADC controller in the PL
        self.init_virtual_adc(DDR_buffer_size_64B)

        # Create the thread running the selected process
        self.thread = threading.Thread( target=self.ddr_circular_buffer_thread,  args=(self.stop_flag, bin_file_name, self.DDR_buffer, DDR_buffer_size_64B) )

        # Launch the thread
        self.thread.start()

    def init_virtual_adc(self, size_8B):

        # Allocate Virtual ADC DDR buffer
        # The size is in 32 bit words, meaning that 4*size bytes will ber reserved
        self.DDR_buffer = allocate(shape=(size_8B*2,), dtype='u4')
        # Reset all values to 0
        self.DDR_buffer[:] = 0

        # Map the Virtual ADC block
        self.vadc_instance = MMIO(VIRTUAL_ADC_OFFSET, 64*1024) # Size mapped by Vivado

        adc_mem = MMIO(ADC_OFFSET, 8192)
        adc_mem.read(0)

        # Reset all values to default
        self.vadc_instance.write(0x10, size_8B)                        # DDR_SIZE_BUFFER     0x10/4 (WRITE) // 64-bits word
        # self.vadc_instance.read(0x18)                                # DDR_CONS_ADDR       0x18/4 (READ)
        # self.vadc_instance.read(0x1C)                                # DDR_CONS_ADDR_CTRL  0x1C/4 (READ) // Valid (bit 0)
        self.vadc_instance.write(0x28, 0)                              # DDR_PROD_ADDR       0x28/4 (WRITE)
        self.vadc_instance.write(0x30, 0)                              # DDR_READY           0x30/4 (WRITE) // Valid (bit 0)
        self.vadc_instance.write(0x38, self.DDR_buffer.physical_address)    # DDR_MASTER_OFF_1    0x38/4 (WRITE)
        self.vadc_instance.write(0x3C, 0)                              # DDR_MASTER_OFF_2    0x3C/4 (WRITE)
        self.vadc_instance.write(0x44, 0)                              # ADC_ERROR_I         0x44/4 (WRITE)
        self.vadc_instance.write(0x30, 1)                              # DDR_READY           0x30/4 (WRITE) // Valid (bit 0)
        # self.vadc_instance.read(0x4C)                                # ADC_ERROR_O         0x4C/4 (READ)
        # self.vadc_instance.read(0x50)                                # ADC_ERROR_CTL       0x50/4 (READ)

    def reset_virtual_adc(self):
        self.vadc_instance.write(0x44, 0)                              # ADC_ERROR_I         0x44/4 (WRITE)
        self.vadc_instance.write(0x30, 0)                              # DDR_READY           0x30/4 (WRITE) // Valid (bit 0)
        self.vadc_instance.write(0x28, 0)                              # DDR_PROD_ADDR       0x28/4 (WRITE)

    def ddr_circular_buffer_thread(self, stop_event, bin_file_name, DDR_buffer, DDR_buffer_size_64B):
        # variables
        file = open(bin_file_name, mode="rb")
        end_of_file = 0
        ddr_producer = 0
        file_byte = list(file.read(8))
        for i in range(8):
                    DDR_buffer[ddr_producer * 2] = (file_byte[0] << 24) | (file_byte[0+1] << 16) | (file_byte[0+2] << 8) | file_byte[0+3]
                    DDR_buffer[ddr_producer * 2 + 1] = (file_byte[0+4] << 24) | (file_byte[0+5] << 16) | (file_byte[0+6] << 8) | file_byte[0+7]
        ddr_producer = 1
        self.vadc_instance.write(0x28, ddr_producer)

        # Buffer control
        while (not stop_event.is_set()) and (end_of_file ==  0):
            ddr_consumer = self.vadc_instance.read(0x18)

            if( ddr_consumer > ddr_producer + 1 ): # Case 1

                gap_32words = (ddr_consumer - ddr_producer - 1) * 2

                file_byte = list(file.read(gap_32words * 4))
                if ( len(file_byte) < (gap_32words * 4) ):
                    end_of_file = 1
                    gap_32words = int(len(file_byte)/4)

                for i in range(gap_32words):
                    DDR_buffer[ddr_producer * 2 + i] = (file_byte[i*4] << 24) | (file_byte[i*4+1] << 16) | (file_byte[i*4+2] << 8) | file_byte[i*4+3]

                ddr_producer = ddr_producer + math.ceil(gap_32words/2)

            elif ( ddr_consumer < ddr_producer + 1 ):
                gap_32words = (DDR_buffer_size_64B - ddr_producer)*2
                if (ddr_consumer == 0):
                    gap_32words = gap_32words - 2

                if (gap_32words > 0):

                    file_byte = list(file.read(gap_32words * 4))
                    if ( len(file_byte) < (gap_32words * 4) ):
                        end_of_file = 1
                        gap_32words = int(len(file_byte)/4)

                    for i in range(gap_32words):
                        DDR_buffer[ddr_producer * 2 + i] = (file_byte[i*4] << 24) | (file_byte[i*4+1] << 16) | (file_byte[i*4+2] << 8) | file_byte[i*4+3]

                    if(ddr_consumer == 0):
                        dr_producer = DDR_buffer_size_64B - 1
                    else:
                        ddr_producer = 0

                        gap_32words = (ddr_consumer - 1)*2

                        file_byte = list(file.read(gap_32words * 4))
                        if ( len(file_byte) < (gap_32words * 4) ):
                            end_of_file = 1
                            gap_32words = int(len(file_byte)/4)

                        for i in range(gap_32words):
                            DDR_buffer[ddr_producer * 2 + i] = (file_byte[i*4] << 24) | (file_byte[i*4+1] << 16) | (file_byte[i*4+2] << 8) | file_byte[i*4+3]

                        ddr_producer = ddr_producer + math.ceil(gap_32words/2)

            gap_32words = 0
            self.vadc_instance.write(0x28, ddr_producer)

        file.close()




    def init_adc_mem(self):

        # Map ADC memory
        adc_mem = MMIO(ADC_OFFSET, 8192)

        # Reset ADC memory
        for i in range(2048):
            adc_mem.write(i*4, 0x0)

        return adc_mem


    def reset_adc_mem(self, adc_mem):

        # Reset ADC mem
        for i in range(2048):
            adc_mem.write(i*4, 0x0)


    def write_adc_mem(self, adc_mem):

        # Write ADC memory from binary file
        file = open("/home/xilinx/x-heep-femu-sdk/sw/riscv/build/adc_in.bin", mode="rb")
        file_byte = file.read()
        for i in range(int(len(file_byte)/4)):
            # adc_mem.write(i*4, (file_byte[i*4+3] << 24) | (file_byte[i*4+2] << 16) | (file_byte[i*4+1] << 8) | file_byte[i*4])
            adc_mem.write(i*4, (file_byte[i*4+0] << 24) | (file_byte[i*4+1] << 16) | (file_byte[i*4+2] << 8) | file_byte[i*4+3])
        file.close()


    def read_adc_mem(self, adc_mem):

        # Read ADC memory to binary file
        file = open("/home/xilinx/x-heep-femu-sdk/sw/riscv/build/adc_out.bin", mode="wb")
        for i in range(2048):
            file.write(adc_mem.read(i*4).to_bytes(4, 'little'))
        file.close()


    def stop(self):
        xht.thread_stop(self.thread, self.stop_flag)