# Copyright 2023 EPFL
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Simone Machetti - simone.machetti@epfl.ch

MAKE               = make

RISCV              ?= /tools/riscv
RISCV_EXE_PREFIX   = $(RISCV)/bin/riscv32-unknown-elf-

TARGET             ?= sim

CUSTOM_GCC_FLAGS   =
LIB_CRT            = $(wildcard lib/crt/*.S)
LIB_BASE           = $(wildcard lib/base/*.c)
LIB_RUNTIME        = $(wildcard lib/runtime/*.c)
LIB_DRIVERS        = $(wildcard lib/hal/soc_ctrl/*.c)
LIB_DRIVERS        += $(wildcard lib/hal/uart/*.c)
LIB_DRIVERS        += $(wildcard lib/hal/rv_plic/*.c)
LIB_DRIVERS        += $(wildcard lib/hal/rv_timer/*.c)
LIB_DRIVERS        += $(wildcard lib/hal/gpio/*.c)
LIB_DRIVERS        += $(wildcard lib/hal/i2c/*.c)
LIB_DRIVERS        += $(wildcard lib/hal/dma/*.c)
LIB_DRIVERS        += $(wildcard lib/hal/power_manager/*.c)
LIB_DRIVERS        += $(wildcard lib/hal/fast_intr_ctrl/*.c)
LIB_DRIVERS        += $(wildcard lib/hal/spi_mem/*.c)
LIB_DRIVERS        += $(wildcard lib/hal/spi_memio/*.c)
LIB_DRIVERS        += $(wildcard lib/hal/spi_host/*.c)
LIB_DRIVERS        += $(wildcard lib/hal/pad_control/*.c)
INC_FOLDERS        = $(sort $(dir $(wildcard lib/target/)))
INC_FOLDERS        += $(sort $(dir $(wildcard lib/base/)))
INC_FOLDERS        += $(sort $(dir $(wildcard lib/hal/*/)))
INC_FOLDERS        += $(sort $(dir $(wildcard lib/runtime/)))
INC_FOLDERS_GCC    = $(addprefix -I ,$(INC_FOLDERS))

%.bin: %.elf
	$(RISCV_EXE_PREFIX)objcopy -O binary $< $@

%.dis: %.elf
	$(RISCV_EXE_PREFIX)objdump -S $< > $@

apps/hello_world/hello_world.elf: apps/hello_world/hello_world.c
	$(RISCV_EXE_PREFIX)gcc -march=rv32imc -o $@ -w -Os -g -nostdlib \
		$(CUSTOM_GCC_FLAGS) \
		-DHOST_BUILD \
		-T link/link.ld \
		-I $(RISCV)/riscv32-unknown-elf/include \
		$(INC_FOLDERS_GCC) \
		-static \
		$(LIB_CRT) \
		$^ $(LIB_RUNTIME) \
		$(LIB_BASE) \
		$(LIB_DRIVERS) \
		-Wl,-Map=apps/hello_world/hello_world.map \
		-L $(RISCV)/riscv32-unknown-elf/lib \
		-lc -lm -lgcc -flto -ffunction-sections -fdata-sections -specs=nano.specs

apps/virtual_flash_write/virtual_flash_write.elf: apps/virtual_flash_write/virtual_flash_write.c
	$(RISCV_EXE_PREFIX)gcc -march=rv32imc -o $@ -w -Os -g -nostdlib \
		$(CUSTOM_GCC_FLAGS) \
		-DHOST_BUILD \
		-T link/link.ld \
		-I $(RISCV)/riscv32-unknown-elf/include \
		$(INC_FOLDERS_GCC) \
		-static \
		$(LIB_CRT) \
		$^ $(LIB_RUNTIME) \
		$(LIB_BASE) \
		$(LIB_DRIVERS) \
		-Wl,-Map=apps/virtual_flash_write/virtual_flash_write.map \
		-L $(RISCV)/riscv32-unknown-elf/lib \
		-lc -lm -lgcc -flto -ffunction-sections -fdata-sections -specs=nano.specs

apps/virtual_flash_read/virtual_flash_read.elf: apps/virtual_flash_read/virtual_flash_read.c
	$(RISCV_EXE_PREFIX)gcc -march=rv32imc -o $@ -w -Os -g -nostdlib \
		$(CUSTOM_GCC_FLAGS) \
		-DHOST_BUILD \
		-T link/link.ld \
		-I $(RISCV)/riscv32-unknown-elf/include \
		$(INC_FOLDERS_GCC) \
		-static \
		$(LIB_CRT) \
		$^ $(LIB_RUNTIME) \
		$(LIB_BASE) \
		$(LIB_DRIVERS) \
		-Wl,-Map=apps/virtual_flash_read/virtual_flash_read.map \
		-L $(RISCV)/riscv32-unknown-elf/lib \
		-lc -lm -lgcc -flto -ffunction-sections -fdata-sections -specs=nano.specs

apps/virtual_adc_write/virtual_adc_write.elf: apps/virtual_adc_write/virtual_adc_write.c
	$(RISCV_EXE_PREFIX)gcc -march=rv32imc -o $@ -w -Os -g -nostdlib \
		$(CUSTOM_GCC_FLAGS) \
		-DHOST_BUILD \
		-T link/link.ld \
		-I $(RISCV)/riscv32-unknown-elf/include \
		$(INC_FOLDERS_GCC) \
		-static \
		$(LIB_CRT) \
		$^ $(LIB_RUNTIME) \
		$(LIB_BASE) \
		$(LIB_DRIVERS) \
		-Wl,-Map=apps/virtual_adc_write/virtual_adc_write.map \
		-L $(RISCV)/riscv32-unknown-elf/lib \
		-lc -lm -lgcc -flto -ffunction-sections -fdata-sections -specs=nano.specs

apps/virtual_adc_read/virtual_adc_read.elf: apps/virtual_adc_read/virtual_adc_read.c
	$(RISCV_EXE_PREFIX)gcc -march=rv32imc -o $@ -w -Os -g -nostdlib \
		$(CUSTOM_GCC_FLAGS) \
		-DHOST_BUILD \
		-T link/link.ld \
		-I $(RISCV)/riscv32-unknown-elf/include \
		$(INC_FOLDERS_GCC) \
		-static \
		$(LIB_CRT) \
		$^ $(LIB_RUNTIME) \
		$(LIB_BASE) \
		$(LIB_DRIVERS) \
		-Wl,-Map=apps/virtual_adc_read/virtual_adc_read.map \
		-L $(RISCV)/riscv32-unknown-elf/lib \
		-lc -lm -lgcc -flto -ffunction-sections -fdata-sections -specs=nano.specs

apps/performance_estimation/performance_estimation.elf: apps/performance_estimation/performance_estimation.c
	$(RISCV_EXE_PREFIX)gcc -march=rv32imc -o $@ -w -Os -g -nostdlib \
		$(CUSTOM_GCC_FLAGS) \
		-DHOST_BUILD \
		-T link/link.ld \
		-I $(RISCV)/riscv32-unknown-elf/include \
		$(INC_FOLDERS_GCC) \
		-static \
		$(LIB_CRT) \
		$^ $(LIB_RUNTIME) \
		$(LIB_BASE) \
		$(LIB_DRIVERS) \
		-Wl,-Map=apps/performance_estimation/performance_estimation.map \
		-L $(RISCV)/riscv32-unknown-elf/lib \
		-lc -lm -lgcc -flto -ffunction-sections -fdata-sections -specs=nano.specs

apps/energy_estimation/energy_estimation.elf: apps/energy_estimation/energy_estimation.c
	$(RISCV_EXE_PREFIX)gcc -march=rv32imc -o $@ -w -Os -g -nostdlib \
		$(CUSTOM_GCC_FLAGS) \
		-DHOST_BUILD \
		-T link/link.ld \
		-I $(RISCV)/riscv32-unknown-elf/include \
		$(INC_FOLDERS_GCC) \
		-static \
		$(LIB_CRT) \
		$^ $(LIB_RUNTIME) \
		$(LIB_BASE) \
		$(LIB_DRIVERS) \
		-Wl,-Map=apps/energy_estimation/energy_estimation.map \
		-L $(RISCV)/riscv32-unknown-elf/lib \
		-lc -lm -lgcc -flto -ffunction-sections -fdata-sections -specs=nano.specs

apps/adc-emu/adc-emu.elf: apps/adc-emu/adc-emu.c
	$(RISCV_EXE_PREFIX)gcc -march=rv32imc -o $@ -w -Os -g -nostdlib \
		$(CUSTOM_GCC_FLAGS) \
		-DHOST_BUILD \
		-T link/link.ld \
		-I $(RISCV)/riscv32-unknown-elf/include \
		$(INC_FOLDERS_GCC) \
		-static \
		$(LIB_CRT) \
		$^ $(LIB_RUNTIME) \
		$(LIB_BASE) \
		$(LIB_DRIVERS) \
		-Wl,-Map=apps/adc-emu/adc-emu.map \
		-L $(RISCV)/riscv32-unknown-elf/lib \
		-lc -lm -lgcc -flto -ffunction-sections -fdata-sections -specs=nano.specs

clean:
	rm -rf build
