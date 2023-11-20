# X-HEEP-based FPGA EMUlation Platform (FEMU)

We ported our custom [eXtendable Heterogeneous Energy-Efficient Platform (X-HEEP)](https://github.com/esl-epfl/x-heep) microcontroller to the TUL Pynq-Z2 board, based on the Xilinx Zynq-7020 chip, in order to realize a valuable FPGA-based emulation platform for performing software explorations of ultra-low-power edge-computing applications.

## Requirements

The needed material for using our FPGA platform is the following:

 - a [TUL Pynq-Z2](https://www.tulembedded.com/fpga/ProductsPYNQ-Z2.html) with power supply.
 - A Micro USB cable.
 - A Ethernet cable.
 - A MicroSD card with at least 16GB of memory.
 - A PC (the Linux operating system is suggested) with a Web browser installed.

## Setup

Follow these steps to get started with our FPGA platform:

 1. Download our pre-compiled PetaLinux-based image from this Drive [FEMU MicroSD Image](http://tiny.cc/femu_microsd_image) and load it to your MicroSD card. You can find more information about the writing process in this documentation: [Write SD card](https://pynq.readthedocs.io/en/latest/appendix/sdcard.html).
 2. Insert your MicroSD card in your Pynq-Z2 board and make sure the boot jumper is in the SD position. Then, power up the board.
 3. You can now connect to the board.

## Board connection

You can access Linux running on the board in the following 3 ways:

**USB (terminal)**
Connect your PC to the board using the Micro USB cable and run this command from your terminal:
```
sudo screen /dev/<your_usb_dev_name> 115200
```
NOTE: this method has several limitations and is suggested only for quick initial configurations.

**Ethernet (terminal)**
Connect the board to the same network of your PC using the Ethernet cable. The Linux ETH interface has the assigned static IP address `192.168.2.99` for direct connections, but can also be configured through DHCP, for router connections. Once you know the IP address of your board, run the following command from your terminal:
```
ssh -X xilinx@<board_ip>
```
**Ethernet (browser)**
Connect the board to the same network of your PC using the Ethernet cable (as explained in the previous paragraph). Then, open your browser and navigate to `<board_ip>:9090` to open the Jupyter environment.

NOTE: the Linux username and password are `xilinx` and `xilinx`, respectively.

## Download SDK

Connect to the board using the `Ethernet` way. Then, navigate to your `home` directory and run this command from your terminal to download the Software Development Kit (SDK):
```
git clone https://github.com/simone-machetti/x-heep-femu-sdk.git
```

## Software exploration

Read our `Read the Docs` documentation at the following link to learn in detail how to run your own applications on our FPGA platform and enjoy all its software exploration functionalities: [FEMU Documentation](http://tiny.cc/femu_documentation).

*---Enjoy our FPGA platform!*

## Modify the SDK

This section quickly describes the content of this repository, so that you may be able to modify the SDK if needed.

    .
    ├── .github
    ├── hw
    │   ├── x_heep.bit
    │   └── x_heep.hwh
    ├── sw
    │   ├── arm
    │   │   ├── jupyter_notebooks
    │   │   ├── apps
    │   │   ├── sdk
    │   │   └── tools
    │   └── riscv
    │   │   ├── apps
    │   │   ├── lib
    │   │   ├── link
    │   │   ├── pwr_val
    │   │   └── Makefile
    ├── init.sh
    └── README.md

The **hw/** folder contains the hardware files of the platform:

 - **x_heep.bit** is the bitstream file.
 - **x_heep.hwh** is the hardware configuration file.

NOTE: you can modify the hardware and re-generate these files using the following repository:
```
https://github.com/simone-machetti/x-heep-femu.git
```

The **sw/** folder is organized as follows:

 - **arm/** contains the software running on Linux on the Processing System (PS) side of the Pynq-Z2 board.
 - **arm/jupyter_notebooks/** contains notebooks that you can use to run our sample applications.
 - **arm/apps/** contains our sample Python applications.
 - **arm/sdk/** contains our X-HEEP Python class.
 - **arm/tools/** contains the needed tools to interact with X-HEEP.
 - **riscv/** contains the code running on X-HEEP implemented on the Programmable Logic (PL) side of the Pynq-Z2 board.
 - **riscv/apps/** contains our sample C applications.
 - **riscv/lib/** contains the needed hardware abstraction layer (HAL).
 - **riscv/link/** contains the linker script.
 - **riscv/pwr_val/** contains the power values for our energy model.
 - **riscv/Makefile** is the Makefile used to compile our RISC-V applications.
