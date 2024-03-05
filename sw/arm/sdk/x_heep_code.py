# Copyright 2024 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Juan Sapriza - juan.sapriza@epfl.ch


class Definitions():

    def_filename = ''

    def __init__(self, filename, tag):
        self.def_filename = filename
        with open( filename, 'w+') as f:
            f.write(f"#ifndef _{tag.upper()}_H\n#define _{tag.upper()}_H\n\n")

    def add(self, alias, value):
        with open( self.def_filename, 'a') as f:
            if type(value) == int or type(value) == float:
                f.write(f"#define {alias} \t{value}\n")
            else:
                f.write(f'#define {alias} \t"{value}"\n')

    def close(self ):
        with open( self.def_filename, 'a') as f:
            f.write("#endif")