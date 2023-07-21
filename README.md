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

#### Load in RAM over SWD/JTAG

Attach a JTAG debugger to the 10-pin connector at the top of the module labeled "SWD".

If you are already running the application and just need to debug, you can just attach without loading.

Install a jumper at ????
(TODO: add new jumper position to make mp1-boot hang instead of jumping to app.)

Power cycle the module. The console will show MP1-Boot started up, intialized RAM, and is waiting.

Use jflash, TRACE32, Ozone, arm-none-eabi-gdb, etc to load the main.elf file.

Execution can begin immediately from 0xC0200040.

TODO: detailed instructions using J-flash, and also gdb.
 
#### Load into NOR Flash over DFU-USB

Power cycle the module with a jumper installed on the Control Expander header. The jumper
must bridge the top-left pin and the pin to the right of that.
This forces an alt firmware to be loaded from NOR Flash (which is a USB-DFU bootloader).

The button will be flashing green when in USB-DFU bootloader mode.

Connect a USB cable from a computer to the module. 

You can use a web-based loader [such as this one](https://devanlai.github.io/webdfu/dfu-util/).
(detailed instructions TODO)

Or use the command line (you must have [dfu-util](https://dfu-util.sourceforge.net/) installed):

```
dfu-util -a 0 -s 0x70080000 -D build/mp1corea7/medium/main.uimg
```

Load the main.uimg file to the default address (0x70080000). It will take a minute or two.

At the end, if you are using the web version, there may be an error `DFU
GETSTATUS failed: ControlTransferIn failed: NetworkError: Failed to execute
'controlTransferIn' on 'USBDevice': A transfer error has occurred.` This is
normal, and is not an error. It's safe to ignore this.

Remove the jumper and power-cycle, and the new code will start up.



#### Boot from SD Card

Use `dd` to copy main.uimg to the third partition of an SD Card that contains mp1-boot on the first two sectors. 
Then, change the BOOT DIP switches to be both to the left (see diagram on PCB). Power cycle.

(more instructions TODO)

### Converting assets

(TODO)

To create the artwork files from the SVGs, you must have Inkscape installed an on your PATH

...To Be Continued...
