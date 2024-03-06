# Copyright 2024 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Simone Machetti - simone.machetti@epfl.ch

from pynq import GPIO

def write(bit, pin):

    # Writes to a specifc GPIO pin (pin attribute starts from 0 and
    # first 8 GPIO bits on PS are used)
    gpio_pin = GPIO(GPIO.get_gpio_pin(8+pin), 'out')
    gpio_pin.write(bit)

def write_restricted(bit, pin):

    # Writes to a specifc GPIO pin (pin attribute starts from 0 and
    # first 8 GPIO bits on PS are used)
    gpio_pin = GPIO(GPIO.get_gpio_pin(pin), 'out')
    gpio_pin.write(bit)

def read(pin):

    # Reads from a specifc GPIO pin (pin attribute starts from 0 and
    # first 8 GPIO bits on PS are used)
    gpio_pin = GPIO(GPIO.get_gpio_pin(pin), 'in')
    pin_read = gpio_pin.read()
    return pin_read