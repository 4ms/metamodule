## MetaModule

### Start

First, clone the repo and `cd` into the new directory.

Then, make sure you are in the right branch:

```
git checkout BRANCHNAME
```

Init and update the submodules recursively:

```
git submodule update --init --recursive
```

### Building VCV Rack Plugin

You must have the Rack-SDK on your computer already. Version 2.2.3 is known to work. Set the environment variable `RACK_DIR` equal to the patch to the location of Rack-SDK:

```
export RACK_DIR=/Users/MyName/projects/Rack-SDK
```

Enter the vcv directory. All VCV Rack plugin code is in here, as well as in `shared/`

```
cd vcv
```

To run the unit tests 

```
make tests
```

To build the plugin, run:

```
make -j16 install
```

This will create the plugin file and install it in your local VCV Rack plugin directory. The next time you start VCV Rack, it will load the modified plugin.


### Building Simulator

The simulator uses SDL2, which must be installed on your host machine.
It only simulates graphics right now (audio can be added -- TODO).
The window can be re-sized in order to examine precise pixel alignment.

Navigate using the left and right arrows to simulate the encoder turning CCW and CW.

The down arrow pushes the encoder button. The up arrow pushes the RGB Button (Back)

Make sure you are in the right branch and you already updated the submodules.

Go to the simulator directory:

```
cd simulator
```

Build it:

```
cmake -B build -GNinja      #Or whatever build system you want
cmake --build build
```


Run it:
```
build/simulator
```


When adding/removing assets, sometimes you need to clean the build:

```
rm -rf build
```

As a shortcut, there is a Makefile wrapping the above cmake commands. (Yes, Makefile generating Cmake generating Ninja)
So, you can just do:

```
# Generate build system (if needed) and build:
make

# Run the simulator:
make run

# Clean:
make clean
```


### Building Firmware

Make sure you are in the right branch and you already updated the submodules.

To run the unit tests 

```
make tests
```
To build the firmware:

```
make -j16 
```

This will generate the firmware in `firmware/build/mp1corea7/medium/main.elf`.
It also generates `main.uimg` in the same dir, which is used when copying
firmware to NOR Flash or an SD card.
The firmware file contains the Cortex-M4 firwmare embedded in it, which is
loaded automatically by the Cortex-A7 core.

You can view the console output by connecting a USB-UART cable to the TX pin
of the debug header (next to the SWD header). The bottom four pins are all GND.
Settings are 115200, 8N1.

Note that the on-board NOR Flash chip has a bootloader installed already
(MP1-Boot, as the FSBL). It also has an alt bootloader (USB-DFU) installed,
which is loaded by powering on with a particular jumper installed.

To load onto hardware, there are several options:

#### Load over SWD

Power cycle the module with the jumper installed on the top-left and the pin to the right of that,
on the Control Expander header. This forces alt firmware mode (which is DFU-USB mode). After power cycling, you can use gdb,
Ozone, jflash, TRACE32, etc to load the elf file.
 
#### Load over DFU-USB

Power cycle the module with the jumper installed on the top-left and the pin to the right of that,
on the Control Expander header. This forces alt firmware mode (which is DFU-USB mode).
Connect a USB cable from a computer to the module, and open a DFU loader. (TODO)

#### Boot from SD Card

Use `dd` to copy main.uimg to the third partition of an SD Card that contains mp1-boot on the first two sectors. 
Then, change the BOOT DIP switches to be both to the right (see diagram on PCB).
(more instructions TODO)

### Converting assets

(TODO)

To create the artwork files from the SVGs, you must have Inkscape installed an on your PATH

...To Be Continued...
