# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Simone Machetti - simone.machetti@epfl.ch

#!/bin/bash

# Quit screen sessions
pkill screen
sudo pkill screen

# Start Pynq environment
. /etc/environment
for f in /etc/profile.d/*.sh; do source $f; done
