# Copyright 2024 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Simone Machetti - simone.machetti@epfl.ch

from pynq import MMIO
from pynq import allocate
import csv

# PERFORMANCE_COUNTERS_OFFSET = 0x44A10000
PERFORMANCE_COUNTERS_OFFSET = 0x43C20000

class PerfCounters():
    def __init__(self):

        # Map performance counters
        self.pc = MMIO(PERFORMANCE_COUNTERS_OFFSET, 256)

        # Reset performance counters
        self.pc.write(0x0, 0x1)
        self.pc.write(0x0, 0x0)

        self.reset_perf_cnt()
        self.start_perf_cnt_manual()


    def reset_perf_cnt(self):

        # Reset performance counters
        self.pc.write(0x0, 0x1)
        self.pc.write(0x0, 0x0)


    def start_perf_cnt_automatic(self):

        # Start perf cnt in automatic mode
        self.pc.write(0x4, 0x1)


    def start_perf_cnt_manual(self):

        # Start perf cnt in manual mode
        self.pc.write(0x4, 0x2)


    def stop_perf_cnt(self):

        # Stop performance counters
        self.pc.write(0x4, 0x0)


    def read_perf_cnt(self):

        # Save performance counters to CSV file
        with open('/home/xilinx/x-heep-femu-sdk/sw/riscv/build/self.csv', mode='w') as perf_cnt_file:
            perf_cnt_writer = csv.writer(perf_cnt_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)

            perf_cnt_writer.writerow(['module', '', '',                        'active cycles',        'clock-gate cycles',        'power-gate cycles',         'retentive cycles', ''])
            perf_cnt_writer.writerow(['x-heep', '', '',                                     '',                         '',                         '',                         '', ''])
            perf_cnt_writer.writerow(['', 'cpu', '',                 (hex(self.pc.read(3*4))),  (hex(self.pc.read(4*4))),  (hex(self.pc.read(5*4))),                        '-', ''])
            perf_cnt_writer.writerow(['', 'bus ao', '',              (hex(self.pc.read(6*4))),  (hex(self.pc.read(7*4))),                        '-',                        '-', ''])
            perf_cnt_writer.writerow(['', 'debug ao', '',            (hex(self.pc.read(8*4))),  (hex(self.pc.read(9*4))),                        '-',                        '-', ''])
            perf_cnt_writer.writerow(['', 'always-on peripheral subsystem', '',             '',                         '',                         '',                         '', ''])
            perf_cnt_writer.writerow(['', '', 'soc ctrl ao',        (hex(self.pc.read(10*4))), (hex(self.pc.read(11*4))),                        '-',                        '-', ''])
            perf_cnt_writer.writerow(['', '', 'boot rom ao',        (hex(self.pc.read(12*4))), (hex(self.pc.read(13*4))),                        '-',                        '-', ''])
            perf_cnt_writer.writerow(['', '', 'spi flash ao',       (hex(self.pc.read(14*4))), (hex(self.pc.read(15*4))),                        '-',                        '-', ''])
            perf_cnt_writer.writerow(['', '', 'spi ao',             (hex(self.pc.read(16*4))), (hex(self.pc.read(17*4))),                        '-',                        '-', ''])
            perf_cnt_writer.writerow(['', '', 'power manager ao',   (hex(self.pc.read(18*4))), (hex(self.pc.read(19*4))),                        '-',                        '-', ''])
            perf_cnt_writer.writerow(['', '', 'timer ao',           (hex(self.pc.read(20*4))), (hex(self.pc.read(21*4))),                        '-',                        '-', ''])
            perf_cnt_writer.writerow(['', '', 'dma ao',             (hex(self.pc.read(22*4))), (hex(self.pc.read(23*4))),                        '-',                        '-', ''])
            perf_cnt_writer.writerow(['', '', 'fast int ctrl ao',   (hex(self.pc.read(24*4))), (hex(self.pc.read(25*4))),                        '-',                        '-', ''])
            perf_cnt_writer.writerow(['', '', 'gpio ao',            (hex(self.pc.read(26*4))), (hex(self.pc.read(27*4))),                        '-',                        '-', ''])
            perf_cnt_writer.writerow(['', '', 'uart ao',            (hex(self.pc.read(28*4))), (hex(self.pc.read(29*4))),                        '-',                        '-', ''])
            perf_cnt_writer.writerow(['', 'peripheral subsystem', '',                       '',                         '',                         '',                         '', ''])
            perf_cnt_writer.writerow(['', '', 'plic',               (hex(self.pc.read(30*4))), (hex(self.pc.read(31*4))), (hex(self.pc.read(32*4))),                        '-', ''])
            perf_cnt_writer.writerow(['', '', 'gpio',               (hex(self.pc.read(33*4))), (hex(self.pc.read(34*4))), (hex(self.pc.read(35*4))),                        '-', ''])
            perf_cnt_writer.writerow(['', '', 'i2c',                (hex(self.pc.read(36*4))), (hex(self.pc.read(37*4))), (hex(self.pc.read(38*4))),                        '-', ''])
            perf_cnt_writer.writerow(['', '', 'timer',              (hex(self.pc.read(39*4))), (hex(self.pc.read(40*4))), (hex(self.pc.read(41*4))),                        '-', ''])
            perf_cnt_writer.writerow(['', '', 'spi',                (hex(self.pc.read(42*4))), (hex(self.pc.read(43*4))), (hex(self.pc.read(44*4))),                        '-', ''])
            perf_cnt_writer.writerow(['', 'memory subsystem', '',                           '',                         '',                         '',                         '', ''])
            perf_cnt_writer.writerow(['', '', 'ram bank 0',         (hex(self.pc.read(45*4))), (hex(self.pc.read(46*4))), (hex(self.pc.read(47*4))), (hex(self.pc.read(48*4))), ''])
            perf_cnt_writer.writerow(['', '', 'ram bank 1',         (hex(self.pc.read(49*4))), (hex(self.pc.read(50*4))), (hex(self.pc.read(51*4))), (hex(self.pc.read(52*4))), ''])
            perf_cnt_writer.writerow(['', '', 'ram bank 2',         (hex(self.pc.read(53*4))), (hex(self.pc.read(54*4))), (hex(self.pc.read(55*4))), (hex(self.pc.read(56*4))), ''])
            perf_cnt_writer.writerow(['', '', 'ram bank 3',         (hex(self.pc.read(57*4))), (hex(self.pc.read(58*4))), (hex(self.pc.read(59*4))), (hex(self.pc.read(60*4))), ''])
            perf_cnt_writer.writerow(['', '', '', '', '', '', '', ''])
            perf_cnt_writer.writerow(['Total cycles', '', '', '', '', '', '', (hex(self.pc.read(2*4)))])

            perf_cnt_file.close()


    def estimate_performance(self, verbose=False):

        with open('/home/xilinx/x-heep-femu-sdk/sw/riscv/build/self.csv') as perf_cnt_file:
            perf_cnt_reader = csv.reader(perf_cnt_file, delimiter=',')
            self = []
            for row in perf_cnt_reader:
                self.append(row)

            with open('/home/xilinx/x-heep-femu-sdk/sw/riscv/build/perf_estim.csv', mode='w') as perf_estim_file:
                perf_estim_writer = csv.writer(perf_estim_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)

                # Save performance estimation to CSV file
                perf_estim_writer.writerow(['module', '', '',                                                             'active cycles',                                    'clock-gate cycles',                                    'power-gate cycles',                                     'retentive cycles', ''])
                perf_estim_writer.writerow(['x-heep', '', '',                                                                          '',                                                     '',                                                     '',                                                     '', ''])
                perf_estim_writer.writerow(['', 'cpu', '',                          float(int(self[2][3], base=16)*float(0.00000005)),  float(int(self[2][4], base=16)*float(0.00000005)),  float(int(self[2][5], base=16)*float(0.00000005)),                                                    '-', ''])
                perf_estim_writer.writerow(['', 'bus ao', '',                       float(int(self[3][3], base=16)*float(0.00000005)),  float(int(self[3][4], base=16)*float(0.00000005)),                                                    '-',                                                    '-', ''])
                perf_estim_writer.writerow(['', 'debug ao', '',                     float(int(self[4][3], base=16)*float(0.00000005)),  float(int(self[4][4], base=16)*float(0.00000005)),                                                    '-',                                                    '-', ''])
                perf_estim_writer.writerow(['', 'always-on peripheral subsystem', '',                                                  '',                                                     '',                                                     '',                                                     '', ''])
                perf_estim_writer.writerow(['', '', 'soc ctrl ao',                  float(int(self[6][3], base=16)*float(0.00000005)),  float(int(self[6][4], base=16)*float(0.00000005)),                                                    '-',                                                    '-', ''])
                perf_estim_writer.writerow(['', '', 'boot rom ao',                  float(int(self[7][3], base=16)*float(0.00000005)),  float(int(self[7][4], base=16)*float(0.00000005)),                                                    '-',                                                    '-', ''])
                perf_estim_writer.writerow(['', '', 'spi flash ao',                 float(int(self[8][3], base=16)*float(0.00000005)),  float(int(self[8][4], base=16)*float(0.00000005)),                                                    '-',                                                    '-', ''])
                perf_estim_writer.writerow(['', '', 'spi ao',                       float(int(self[9][3], base=16)*float(0.00000005)),  float(int(self[9][4], base=16)*float(0.00000005)),                                                    '-',                                                    '-', ''])
                perf_estim_writer.writerow(['', '', 'power manager ao',            float(int(self[10][3], base=16)*float(0.00000005)), float(int(self[10][4], base=16)*float(0.00000005)),                                                    '-',                                                    '-', ''])
                perf_estim_writer.writerow(['', '', 'timer ao',                    float(int(self[11][3], base=16)*float(0.00000005)), float(int(self[11][4], base=16)*float(0.00000005)),                                                    '-',                                                    '-', ''])
                perf_estim_writer.writerow(['', '', 'dma ao',                      float(int(self[12][3], base=16)*float(0.00000005)), float(int(self[12][4], base=16)*float(0.00000005)),                                                    '-',                                                    '-', ''])
                perf_estim_writer.writerow(['', '', 'fast int ctrl ao',            float(int(self[13][3], base=16)*float(0.00000005)), float(int(self[13][4], base=16)*float(0.00000005)),                                                    '-',                                                    '-', ''])
                perf_estim_writer.writerow(['', '', 'gpio ao',                     float(int(self[14][3], base=16)*float(0.00000005)), float(int(self[14][4], base=16)*float(0.00000005)),                                                    '-',                                                    '-', ''])
                perf_estim_writer.writerow(['', '', 'uart ao',                     float(int(self[15][3], base=16)*float(0.00000005)), float(int(self[15][4], base=16)*float(0.00000005)),                                                    '-',                                                    '-', ''])
                perf_estim_writer.writerow(['', 'peripheral subsystem', '',                                                            '',                                                     '',                                                     '',                                                     '', ''])
                perf_estim_writer.writerow(['', '', 'plic',                        float(int(self[17][3], base=16)*float(0.00000005)), float(int(self[17][4], base=16)*float(0.00000005)), float(int(self[17][5], base=16)*float(0.00000005)),                                                    '-', ''])
                perf_estim_writer.writerow(['', '', 'gpio',                        float(int(self[18][3], base=16)*float(0.00000005)), float(int(self[18][4], base=16)*float(0.00000005)), float(int(self[18][5], base=16)*float(0.00000005)),                                                    '-', ''])
                perf_estim_writer.writerow(['', '', 'i2c',                         float(int(self[19][3], base=16)*float(0.00000005)), float(int(self[19][4], base=16)*float(0.00000005)), float(int(self[19][5], base=16)*float(0.00000005)),                                                    '-', ''])
                perf_estim_writer.writerow(['', '', 'timer',                       float(int(self[20][3], base=16)*float(0.00000005)), float(int(self[20][4], base=16)*float(0.00000005)), float(int(self[20][5], base=16)*float(0.00000005)),                                                    '-', ''])
                perf_estim_writer.writerow(['', '', 'spi',                         float(int(self[21][3], base=16)*float(0.00000005)), float(int(self[21][4], base=16)*float(0.00000005)), float(int(self[21][5], base=16)*float(0.00000005)),                                                    '-', ''])
                perf_estim_writer.writerow(['', 'memory subsystem', '',                                                                '',                                                     '',                                                     '',                                                     '', ''])
                perf_estim_writer.writerow(['', '', 'ram bank 0',                  float(int(self[23][3], base=16)*float(0.00000005)), float(int(self[23][4], base=16)*float(0.00000005)), float(int(self[23][5], base=16)*float(0.00000005)), float(int(self[23][6], base=16)*float(0.00000005)), ''])
                perf_estim_writer.writerow(['', '', 'ram bank 1',                  float(int(self[24][3], base=16)*float(0.00000005)), float(int(self[24][4], base=16)*float(0.00000005)), float(int(self[24][5], base=16)*float(0.00000005)), float(int(self[24][6], base=16)*float(0.00000005)), ''])
                perf_estim_writer.writerow(['', '', 'ram bank 2',                  float(int(self[25][3], base=16)*float(0.00000005)), float(int(self[25][4], base=16)*float(0.00000005)), float(int(self[25][5], base=16)*float(0.00000005)), float(int(self[25][6], base=16)*float(0.00000005)), ''])
                perf_estim_writer.writerow(['', '', 'ram bank 3',                  float(int(self[26][3], base=16)*float(0.00000005)), float(int(self[26][4], base=16)*float(0.00000005)), float(int(self[26][5], base=16)*float(0.00000005)), float(int(self[26][6], base=16)*float(0.00000005)), ''])
                perf_estim_writer.writerow(['', '', '', '', '', '', '', ''])
                perf_estim_writer.writerow(['Total time', '', '', '', '', '', '', float(int(self[28][7], base=16)*float(0.00000005))])

                # Print performance estimation to stdout
                if verbose:
                    print("\n--- PERFORMANCE ESTIMATION AT 20MHz ---\n")

                    print("total time:                 %Es\n"    % (float(int(self[28][7], base=16)*float(0.00000005))))

                    print("x-heep\n")

                    print("    cpu\n")

                    print("     - active time:         %Es"      % (float(int(self[2][3], base=16)*float(0.00000005))))
                    print("     - clock-gate time:     %Es"      % (float(int(self[2][4], base=16)*float(0.00000005))))
                    print("     - power-gate time:     %Es\n"    % (float(int(self[2][5], base=16)*float(0.00000005))))

                    print("    bus ao\n")

                    print("     - active time:         %Es"      % (float(int(self[3][3], base=16)*float(0.00000005))))
                    print("     - clock-gate time:     %Es\n"    % (float(int(self[3][4], base=16)*float(0.00000005))))

                    print("    debug ao\n")

                    print("     - active time:         %Es"      % (float(int(self[4][3], base=16)*float(0.00000005))))
                    print("     - clock-gate time:     %Es\n"    % (float(int(self[4][4], base=16)*float(0.00000005))))

                    print("    always-on peripheral subsystem\n")

                    print("        soc ctrl ao\n")

                    print("         - active time:     %Es"      % (float(int(self[6][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es\n"    % (float(int(self[6][4], base=16)*float(0.00000005))))

                    print("        boot rom ao\n")

                    print("         - active time:     %Es"      % (float(int(self[7][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es\n"    % (float(int(self[7][4], base=16)*float(0.00000005))))

                    print("        spi flash ao\n")

                    print("         - active time:     %Es"      % (float(int(self[8][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es\n"    % (float(int(self[8][4], base=16)*float(0.00000005))))

                    print("        spi ao\n")

                    print("         - active time:     %Es"      % (float(int(self[9][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es\n"    % (float(int(self[9][4], base=16)*float(0.00000005))))

                    print("        power manager ao\n")

                    print("         - active time:     %Es"      % (float(int(self[10][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es\n"    % (float(int(self[10][4], base=16)*float(0.00000005))))

                    print("        timer ao\n")

                    print("         - active time:     %Es"      % (float(int(self[11][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es\n"    % (float(int(self[11][4], base=16)*float(0.00000005))))

                    print("        dma ao\n")

                    print("         - active time:     %Es"      % (float(int(self[12][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es\n"    % (float(int(self[12][4], base=16)*float(0.00000005))))

                    print("        fast int ctrl ao\n")

                    print("         - active time:     %Es"      % (float(int(self[13][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es\n"    % (float(int(self[13][4], base=16)*float(0.00000005))))

                    print("        gpio ao\n")

                    print("         - active time:     %Es"      % (float(int(self[14][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es\n"    % (float(int(self[14][4], base=16)*float(0.00000005))))

                    print("        uart ao\n")

                    print("         - active time:     %Es"      % (float(int(self[15][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es\n"    % (float(int(self[15][4], base=16)*float(0.00000005))))

                    print("    peripheral subsystem\n")

                    print("        plic\n")

                    print("         - active time:     %Es"      % (float(int(self[17][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es"      % (float(int(self[17][4], base=16)*float(0.00000005))))
                    print("         - power-gate time: %Es\n"    % (float(int(self[17][5], base=16)*float(0.00000005))))

                    print("        gpio\n")

                    print("         - active time:     %Es"      % (float(int(self[18][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es"      % (float(int(self[18][4], base=16)*float(0.00000005))))
                    print("         - power-gate time: %Es\n"    % (float(int(self[18][5], base=16)*float(0.00000005))))

                    print("        i2c\n")

                    print("         - active time:     %Es"      % (float(int(self[19][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es"      % (float(int(self[19][4], base=16)*float(0.00000005))))
                    print("         - power-gate time: %Es\n"    % (float(int(self[19][5], base=16)*float(0.00000005))))

                    print("        timer\n")

                    print("         - active time:     %Es"      % (float(int(self[20][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es"      % (float(int(self[20][4], base=16)*float(0.00000005))))
                    print("         - power-gate time: %Es\n"    % (float(int(self[20][5], base=16)*float(0.00000005))))

                    print("        spi\n")

                    print("         - active time:     %Es"      % (float(int(self[21][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es"      % (float(int(self[21][4], base=16)*float(0.00000005))))
                    print("         - power-gate time: %Es\n"    % (float(int(self[21][5], base=16)*float(0.00000005))))

                    print("    memory subsystem\n")

                    print("        ram bank 0\n")

                    print("         - active time:     %Es"      % (float(int(self[23][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es"      % (float(int(self[23][4], base=16)*float(0.00000005))))
                    print("         - power-gate time: %Es"      % (float(int(self[23][5], base=16)*float(0.00000005))))
                    print("         - retentive time:  %Es\n"    % (float(int(self[23][6], base=16)*float(0.00000005))))

                    print("        ram bank 1\n")

                    print("         - active time:     %Es"      % (float(int(self[24][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es"      % (float(int(self[24][4], base=16)*float(0.00000005))))
                    print("         - power-gate time: %Es"      % (float(int(self[24][5], base=16)*float(0.00000005))))
                    print("         - retentive time:  %Es\n"    % (float(int(self[24][6], base=16)*float(0.00000005))))

                    print("        ram bank 2\n")

                    print("         - active time:     %Es"      % (float(int(self[25][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es"      % (float(int(self[25][4], base=16)*float(0.00000005))))
                    print("         - power-gate time: %Es"      % (float(int(self[25][5], base=16)*float(0.00000005))))
                    print("         - retentive time:  %Es\n"    % (float(int(self[25][6], base=16)*float(0.00000005))))

                    print("        ram bank 3\n")

                    print("         - active time:     %Es"      % (float(int(self[26][3], base=16)*float(0.00000005))))
                    print("         - clock-gate time: %Es"      % (float(int(self[26][4], base=16)*float(0.00000005))))
                    print("         - power-gate time: %Es"      % (float(int(self[26][5], base=16)*float(0.00000005))))
                    print("         - retentive time:  %Es"      % (float(int(self[26][6], base=16)*float(0.00000005))))

                perf_estim_file.close()

            perf_cnt_file.close()


    def estimate_energy(self, cells, verbose=False):

        with open('/home/xilinx/x-heep-femu-sdk/sw/riscv/pwr_val/TSMC_65nm_' + cells + '_20MHz.csv') as power_values_file:
            power_values_reader = csv.reader(power_values_file, delimiter=',')
            power_values = []
            for row in power_values_reader:
                power_values.append(row)

            with open('/home/xilinx/x-heep-femu-sdk/sw/riscv/build/perf_estim.csv') as perf_estim_file:
                perf_estim_reader = csv.reader(perf_estim_file, delimiter=',')
                perf_estim = []
                for row in perf_estim_reader:
                    perf_estim.append(row)

                               # active power                 # active time                     # leakage power                # clock-gate time                            # power-gate time                # retentive power               # retentive time
                energy  =   (  float(power_values[2][5])  *   float(perf_estim[2][3]) )  +   (  float(power_values[2][3])  *   float(perf_estim[2][4]) )    +   ( 0   *    float(perf_estim[2][5]) )     + \
                            (  float(power_values[3][5])  *   float(perf_estim[3][3]) )  +   (  float(power_values[3][3])  *   float(perf_estim[3][4]) )    + \
                            (  float(power_values[4][5])  *   float(perf_estim[4][3]) )  +   (  float(power_values[4][3])  *   float(perf_estim[4][4]) )    + \
                            (  float(power_values[6][5])  *   float(perf_estim[6][3]) )  +   (  float(power_values[6][3])  *   float(perf_estim[6][4]) )    + \
                            (  float(power_values[7][5])  *   float(perf_estim[7][3]) )  +   (  float(power_values[7][3])  *   float(perf_estim[7][4]) )    + \
                            (  float(power_values[8][5])  *   float(perf_estim[8][3]) )  +   (  float(power_values[8][3])  *   float(perf_estim[8][4]) )    + \
                            (  float(power_values[9][5])  *   float(perf_estim[9][3]) )  +   (  float(power_values[9][3])  *   float(perf_estim[9][4]) )    + \
                            ( float(power_values[10][5])  *  float(perf_estim[10][3]) )  +   ( float(power_values[10][3])  *  float(perf_estim[10][4]) )    + \
                            ( float(power_values[11][5])  *  float(perf_estim[11][3]) )  +   ( float(power_values[11][3])  *  float(perf_estim[11][4]) )    + \
                            ( float(power_values[12][5])  *  float(perf_estim[12][3]) )  +   ( float(power_values[12][3])  *  float(perf_estim[12][4]) )    + \
                            ( float(power_values[13][5])  *  float(perf_estim[13][3]) )  +   ( float(power_values[13][3])  *  float(perf_estim[13][4]) )    + \
                            ( float(power_values[14][5])  *  float(perf_estim[14][3]) )  +   ( float(power_values[14][3])  *  float(perf_estim[14][4]) )    + \
                            ( float(power_values[15][5])  *  float(perf_estim[15][3]) )  +   ( float(power_values[15][3])  *  float(perf_estim[15][4]) )    + \
                            ( float(power_values[17][5])  *  float(perf_estim[17][3]) )  +   ( float(power_values[17][3])  *  float(perf_estim[17][4]) )    +   ( 0   *   float(perf_estim[17][5]) )   + \
                            ( float(power_values[18][5])  *  float(perf_estim[18][3]) )  +   ( float(power_values[18][3])  *  float(perf_estim[18][4]) )    +   ( 0   *   float(perf_estim[18][5]) )   + \
                            ( float(power_values[19][5])  *  float(perf_estim[19][3]) )  +   ( float(power_values[19][3])  *  float(perf_estim[19][4]) )    +   ( 0   *   float(perf_estim[19][5]) )   + \
                            ( float(power_values[20][5])  *  float(perf_estim[20][3]) )  +   ( float(power_values[20][3])  *  float(perf_estim[20][4]) )    +   ( 0   *   float(perf_estim[20][5]) )   + \
                            ( float(power_values[21][5])  *  float(perf_estim[21][3]) )  +   ( float(power_values[21][3])  *  float(perf_estim[21][4]) )    +   ( 0   *   float(perf_estim[21][5]) )   + \
                            ( float(power_values[23][5])  *  float(perf_estim[23][3]) )  +   ( float(power_values[23][3])  *  float(perf_estim[23][4]) )    +   ( 0   *   float(perf_estim[23][5]) )   +   ( float(power_values[23][6])  *   float(perf_estim[23][6]) ) + \
                            ( float(power_values[24][5])  *  float(perf_estim[24][3]) )  +   ( float(power_values[24][3])  *  float(perf_estim[24][4]) )    +   ( 0   *   float(perf_estim[24][5]) )   +   ( float(power_values[24][6])  *   float(perf_estim[24][6]) ) + \
                            ( float(power_values[25][5])  *  float(perf_estim[25][3]) )  +   ( float(power_values[25][3])  *  float(perf_estim[25][4]) )    +   ( 0   *   float(perf_estim[25][5]) )   +   ( float(power_values[25][6])  *   float(perf_estim[25][6]) ) + \
                            ( float(power_values[26][5])  *  float(perf_estim[26][3]) )  +   ( float(power_values[26][3])  *  float(perf_estim[26][4]) )    +   ( 0   *   float(perf_estim[26][5]) )   +   ( float(power_values[26][6])  *   float(perf_estim[26][6]) ) + \
                            \
                            ( float(power_values[28][5])  *  float(perf_estim[28][7]) )

                with open('/home/xilinx/x-heep-femu-sdk/sw/riscv/build/energy_estim.csv', mode='w') as energy_estim_file:
                    energy_estim_writer = csv.writer(energy_estim_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)

                    # Save energy estimation to CSV file
                    energy_estim_writer.writerow(['module', '', '',                                                          'active energy',                                  'clock-gate energy',        'power-gate energy',                                   'retentive energy', ''])
                    energy_estim_writer.writerow(['x-heep', '', '',                                                                       '',                                                   '',                         '',                                                   '', ''])
                    energy_estim_writer.writerow(['', 'cpu', '',                           float(power_values[2][5])*float(perf_estim[2][3]),    float(power_values[2][3])*float(perf_estim[2][4]),  0*float(perf_estim[2][3]),                                                  '-', ''])
                    energy_estim_writer.writerow(['', 'bus ao', '',                        float(power_values[3][5])*float(perf_estim[3][3]),    float(power_values[3][3])*float(perf_estim[3][4]),                        '-',                                                  '-', ''])
                    energy_estim_writer.writerow(['', 'debug ao', '',                      float(power_values[4][5])*float(perf_estim[4][3]),    float(power_values[4][3])*float(perf_estim[4][4]),                        '-',                                                  '-', ''])
                    energy_estim_writer.writerow(['', 'always-on peripheral subsystem', '',                                               '',                                                   '',                         '',                                                   '', ''])
                    energy_estim_writer.writerow(['', '', 'soc ctrl ao',                   float(power_values[6][5])*float(perf_estim[6][3]),    float(power_values[6][3])*float(perf_estim[6][4]),                        '-',                                                  '-', ''])
                    energy_estim_writer.writerow(['', '', 'boot rom ao',                   float(power_values[7][5])*float(perf_estim[7][3]),    float(power_values[7][3])*float(perf_estim[7][4]),                        '-',                                                  '-', ''])
                    energy_estim_writer.writerow(['', '', 'spi flash ao',                  float(power_values[8][5])*float(perf_estim[8][3]),    float(power_values[8][3])*float(perf_estim[8][4]),                        '-',                                                  '-', ''])
                    energy_estim_writer.writerow(['', '', 'spi ao',                        float(power_values[9][5])*float(perf_estim[9][3]),    float(power_values[9][3])*float(perf_estim[9][4]),                        '-',                                                  '-', ''])
                    energy_estim_writer.writerow(['', '', 'power manager ao',             float(power_values[10][5])*float(perf_estim[10][3]),  float(power_values[10][3])*float(perf_estim[10][4]),                        '-',                                                 '-', ''])
                    energy_estim_writer.writerow(['', '', 'timer ao',                     float(power_values[11][5])*float(perf_estim[11][3]),  float(power_values[11][3])*float(perf_estim[11][4]),                        '-',                                                 '-', ''])
                    energy_estim_writer.writerow(['', '', 'dma ao',                       float(power_values[12][5])*float(perf_estim[12][3]),  float(power_values[12][3])*float(perf_estim[12][4]),                        '-',                                                 '-', ''])
                    energy_estim_writer.writerow(['', '', 'fast int ctrl ao',             float(power_values[13][5])*float(perf_estim[13][3]),  float(power_values[13][3])*float(perf_estim[13][4]),                        '-',                                                 '-', ''])
                    energy_estim_writer.writerow(['', '', 'gpio ao',                      float(power_values[14][5])*float(perf_estim[14][3]),  float(power_values[14][3])*float(perf_estim[14][4]),                        '-',                                                 '-', ''])
                    energy_estim_writer.writerow(['', '', 'uart ao',                      float(power_values[15][5])*float(perf_estim[15][3]),  float(power_values[15][3])*float(perf_estim[15][4]),                        '-',                                                 '-', ''])
                    energy_estim_writer.writerow(['', 'peripheral subsystem', '',                                                          '',                                                   '',                         '',                                                  '', ''])
                    energy_estim_writer.writerow(['', '', 'plic',                         float(power_values[17][5])*float(perf_estim[17][3]),  float(power_values[17][3])*float(perf_estim[17][4]), 0*float(perf_estim[17][5]),                                                 '-', ''])
                    energy_estim_writer.writerow(['', '', 'gpio',                         float(power_values[18][5])*float(perf_estim[18][3]),  float(power_values[18][3])*float(perf_estim[18][4]), 0*float(perf_estim[18][5]),                                                 '-', ''])
                    energy_estim_writer.writerow(['', '', 'i2c',                          float(power_values[19][5])*float(perf_estim[19][3]),  float(power_values[19][3])*float(perf_estim[19][4]), 0*float(perf_estim[19][5]),                                                 '-', ''])
                    energy_estim_writer.writerow(['', '', 'timer',                        float(power_values[20][5])*float(perf_estim[20][3]),  float(power_values[20][3])*float(perf_estim[20][4]), 0*float(perf_estim[20][5]),                                                 '-', ''])
                    energy_estim_writer.writerow(['', '', 'spi',                          float(power_values[21][5])*float(perf_estim[21][3]),  float(power_values[21][3])*float(perf_estim[21][4]), 0*float(perf_estim[21][5]),                                                 '-', ''])
                    energy_estim_writer.writerow(['', 'memory subsystem', '',                                                              '',                                                   '',                         '',                                                  '', ''])
                    energy_estim_writer.writerow(['', '', 'ram bank 0',                   float(power_values[23][5])*float(perf_estim[23][3]),  float(power_values[23][3])*float(perf_estim[23][4]), 0*float(perf_estim[23][5]), float(power_values[23][6])*float(perf_estim[23][6]), ''])
                    energy_estim_writer.writerow(['', '', 'ram bank 1',                   float(power_values[24][5])*float(perf_estim[24][3]),  float(power_values[24][3])*float(perf_estim[24][4]), 0*float(perf_estim[24][5]), float(power_values[24][6])*float(perf_estim[24][6]), ''])
                    energy_estim_writer.writerow(['', '', 'ram bank 2',                   float(power_values[25][5])*float(perf_estim[25][3]),  float(power_values[25][3])*float(perf_estim[25][4]), 0*float(perf_estim[25][5]), float(power_values[25][6])*float(perf_estim[25][6]), ''])
                    energy_estim_writer.writerow(['', '', 'ram bank 3',                   float(power_values[26][5])*float(perf_estim[26][3]),  float(power_values[26][3])*float(perf_estim[26][4]), 0*float(perf_estim[26][5]), float(power_values[26][6])*float(perf_estim[26][6]), ''])
                    energy_estim_writer.writerow(['', '', '', '', '', '', '', ''])
                    energy_estim_writer.writerow(['Total energy', '', '', '', '', '', '', energy])

                    if verbose:
                        # Print energy estimation to stdout
                        print("\n--- ENERGY ESTIMATION AT 20MHz ---\n")

                        print("total energy:                 %EJ\n"    % (energy))

                        print("x-heep\n")

                        print("    cpu\n")

                        print("     - active energy:         %EJ"      % (float(power_values[2][5])*float(perf_estim[2][3])))
                        print("     - clock-gate energy:     %EJ"      % (float(power_values[2][3])*float(perf_estim[2][4])))
                        print("     - power-gate energy:     %EJ\n"    % (0*float(perf_estim[2][3])))

                        print("    bus ao\n")

                        print("     - active energy:         %EJ"      % (float(power_values[3][5])*float(perf_estim[3][3])))
                        print("     - clock-gate energy:     %EJ\n"    % (float(power_values[3][3])*float(perf_estim[3][4])))

                        print("    debug ao\n")

                        print("     - active energy:         %EJ"      % (float(power_values[4][5])*float(perf_estim[4][3])))
                        print("     - clock-gate energy:     %EJ\n"    % (float(power_values[4][3])*float(perf_estim[4][4])))

                        print("    always-on peripheral subsystem\n")

                        print("        soc ctrl ao\n")

                        print("         - active energy:     %EJ"      % (float(power_values[6][5])*float(perf_estim[6][3])))
                        print("         - clock-gate energy: %EJ\n"    % (float(power_values[6][3])*float(perf_estim[6][4])))

                        print("        boot rom ao\n")

                        print("         - active energy:     %EJ"      % (float(power_values[7][5])*float(perf_estim[7][3])))
                        print("         - clock-gate energy: %EJ\n"    % (float(power_values[7][3])*float(perf_estim[7][4])))

                        print("        spi flash ao\n")

                        print("         - active energy:     %EJ"      % (float(power_values[8][5])*float(perf_estim[8][3])))
                        print("         - clock-gate energy: %EJ\n"    % (float(power_values[8][3])*float(perf_estim[8][4])))

                        print("        spi ao\n")

                        print("         - active energy:     %EJ"      % (float(power_values[9][5])*float(perf_estim[9][3])))
                        print("         - clock-gate energy: %EJ\n"    % (float(power_values[9][3])*float(perf_estim[9][4])))

                        print("        power manager ao\n")

                        print("         - active energy:     %EJ"      % (float(power_values[10][5])*float(perf_estim[10][3])))
                        print("         - clock-gate energy: %EJ\n"    % (float(power_values[10][3])*float(perf_estim[10][4])))

                        print("        timer ao\n")

                        print("         - active energy:     %EJ"      % (float(power_values[11][5])*float(perf_estim[11][3])))
                        print("         - clock-gate energy: %EJ\n"    % (float(power_values[11][3])*float(perf_estim[11][4])))

                        print("        dma ao\n")

                        print("         - active energy:     %EJ"      % (float(power_values[12][5])*float(perf_estim[12][3])))
                        print("         - clock-gate energy: %EJ\n"    % (float(power_values[12][3])*float(perf_estim[12][4])))

                        print("        fast int ctrl ao\n")

                        print("         - active energy:     %EJ"      % (float(power_values[13][5])*float(perf_estim[13][3])))
                        print("         - clock-gate energy: %EJ\n"    % (float(power_values[13][3])*float(perf_estim[13][4])))

                        print("        gpio ao\n")

                        print("         - active energy:     %EJ"      % (float(power_values[14][5])*float(perf_estim[14][3])))
                        print("         - clock-gate energy: %EJ\n"    % (float(power_values[14][3])*float(perf_estim[14][4])))

                        print("        uart ao\n")

                        print("         - active energy:     %EJ"      % (float(power_values[15][5])*float(perf_estim[15][3])))
                        print("         - clock-gate energy: %EJ\n"    % (float(power_values[15][3])*float(perf_estim[15][4])))

                        print("    peripheral subsystem\n")

                        print("        plic\n")

                        print("         - active energy:     %EJ"      % (float(power_values[17][5])*float(perf_estim[17][3])))
                        print("         - clock-gate energy: %EJ"      % (float(power_values[17][3])*float(perf_estim[17][4])))
                        print("         - power-gate energy: %EJ\n"    % (                         0*float(perf_estim[17][5])))

                        print("        gpio\n")

                        print("         - active energy:     %EJ"      % (float(power_values[18][5])*float(perf_estim[18][3])))
                        print("         - clock-gate energy: %EJ"      % (float(power_values[18][3])*float(perf_estim[18][4])))
                        print("         - power-gate energy: %EJ\n"    % (                         0*float(perf_estim[18][5])))

                        print("        i2c\n")

                        print("         - active energy:     %EJ"      % (float(power_values[19][5])*float(perf_estim[19][3])))
                        print("         - clock-gate energy: %EJ"      % (float(power_values[19][3])*float(perf_estim[19][4])))
                        print("         - power-gate energy: %EJ\n"    % (                         0*float(perf_estim[19][5])))

                        print("        timer\n")

                        print("         - active energy:     %EJ"      % (float(power_values[20][5])*float(perf_estim[20][3])))
                        print("         - clock-gate energy: %EJ"      % (float(power_values[20][3])*float(perf_estim[20][4])))
                        print("         - power-gate energy: %EJ\n"    % (                         0*float(perf_estim[20][5])))

                        print("        spi\n")

                        print("         - active energy:     %EJ"      % (float(power_values[21][5])*float(perf_estim[21][3])))
                        print("         - clock-gate energy: %EJ"      % (float(power_values[21][3])*float(perf_estim[21][4])))
                        print("         - power-gate energy: %EJ\n"    % (                         0*float(perf_estim[21][5])))

                        print("    memory subsystem\n")

                        print("        ram bank 0\n")

                        print("         - active energy:     %EJ"      % (float(power_values[23][5])*float(perf_estim[23][3])))
                        print("         - clock-gate energy: %EJ"      % (float(power_values[23][3])*float(perf_estim[23][4])))
                        print("         - power-gate energy: %EJ"      % (                         0*float(perf_estim[23][5])))
                        print("         - retentive energy:  %EJ\n"    % (float(power_values[23][6])*float(perf_estim[23][6])))

                        print("        ram bank 1\n")

                        print("         - active energy:     %EJ"      % (float(power_values[24][5])*float(perf_estim[24][3])))
                        print("         - clock-gate energy: %EJ"      % (float(power_values[24][3])*float(perf_estim[24][4])))
                        print("         - power-gate energy: %EJ"      % (                         0*float(perf_estim[24][5])))
                        print("         - retentive energy:  %EJ\n"    % (float(power_values[24][6])*float(perf_estim[24][6])))

                        print("        ram bank 2\n")

                        print("         - active energy:     %EJ"      % (float(power_values[25][5])*float(perf_estim[25][3])))
                        print("         - clock-gate energy: %EJ"      % (float(power_values[25][3])*float(perf_estim[25][4])))
                        print("         - power-gate energy: %EJ"      % (                         0*float(perf_estim[25][5])))
                        print("         - retentive energy:  %EJ\n"    % (float(power_values[25][6])*float(perf_estim[25][6])))

                        print("        ram bank 3\n")

                        print("         - active energy:     %EJ"      % (float(power_values[26][5])*float(perf_estim[26][3])))
                        print("         - clock-gate energy: %EJ"      % (float(power_values[26][3])*float(perf_estim[26][4])))
                        print("         - power-gate energy: %EJ"      % (                         0*float(perf_estim[26][5])))
                        print("         - retentive energy:  %EJ"      % (float(power_values[26][6])*float(perf_estim[26][6])))

                    energy_estim_file.close()

                perf_estim_file.close()

            power_values_file.close()