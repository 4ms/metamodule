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

You must have the Rack-SDK on your computer already. Version 2.2.3 is known to
work. Set the environment variable `RACK_DIR` equal to the patch to the
location of Rack-SDK:

```
export RACK_DIR=/Users/MyName/projects/Rack-SDK
```

Enter the vcv directory. All VCV Rack plugin code is in here, as well as in
`shared/`

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

This will create the plugin file and install it in your local VCV Rack plugin
directory. The next time you start VCV Rack, it will load the modified plugin.


### Building Simulator

The simulator uses SDL2, which must be installed on your host machine. It only
simulates graphics right now (audio can be added -- TODO). The window can be
re-sized in order to examine precise pixel alignment.

Navigate using the left and right arrows to simulate the encoder turning CCW
and CW.

The down arrow pushes the encoder button. The up arrow pushes the RGB Button
(Back)

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

As a shortcut, there is a Makefile wrapping the above cmake commands. (Yes,
Makefile running Cmake generating Ninja) So, you can just do:

```
# Generate build system (if needed) and build:
make

# Run the simulator:
make run

# Clean:
make clean
```


### Building Firmware

This requires arm-none-eabi-gcc versions 12.2 or later installed on your $PATH.

Make sure you are in the right branch and you already updated the submodules.

To build the firmware:

```
make -j16 
```

This will generate the firmware in `firmware/build/mp1corea7/medium/main.elf`.
It also generates `main.uimg` in the same dir, which is used when copying
firmware to NOR Flash or an SD card.
The firmware file contains the Cortex-M4 firwmare embedded in it, which is
loaded automatically by the Cortex-A7 core.

There is a bootloader that runs before the application, and it outputs useful
messages over a UART. You can view the console output by connecting a USB-UART
cable to the TX pin of the debug header (next to the SWD header). The TX pin is
labeled (upper-right pin). The bottom four pins are all GND. Settings are
115200, 8N1.


#### Load in RAM over SWD/JTAG

This is the preferred method for active firmware development. It requires a JTAG programmer.

Attach a JTAG debugger to the 10-pin connector at the top of the module labeled "SWD". The protocol is actually JTAG, despite the header's name, 
though SWD may work since the only difference is the tRST pin instead of NRST.

If you are already running the application and just need to debug, you can just attach without loading.

If you need to load new firmware, then do this:

1) Install a jumper on Control Expander header that bridges the top-left pin and the pin just to the right of it.
To be clear, the jumper should be horizontal, not vertical, on the top row of pins all the way to the left:

```
  Control
 Expander
          [====] o  o 
           o  o  o  o
```

2) Power off and back on. 

The console will show:

```
Freeze pin detected active, freezing.
Ready to load firmware to DDR RAM via SWD/JTAG.
```

Use Jflash, TRACE32, Ozone, arm-none-eabi-gdb, etc to load the main.elf file.
If you have a JLink connected, you can program with this;

```
make jprog
```

For other methods, just load the .elf file and then start executing from 0xC0200040.

Note: If you are familiar with flashing Cortex-M series MCUs, you will notice
some differences. One is that Flash is an external chip. Another difference is
that the main RAM (DDR RAM) is not available until software initializes it. The
on-board NOR Flash chip has a bootloader installed (MP1-Boot, which is the
FSBL). This is loaded by the BOOTROM on power-up. The MP1-Boot bootloader is
responsible for initializing the DDR RAM peripheral. Obviously, this must be
done before loading the firmware into DDR RAM. So, unlike a Cortex-M chip, you
must run a bootloader before programming the device. However, one of the first
things an application does when it starts running is to enable the MMU and
setup various memory regions, some of which are not writable. Thus, the only
time in which it's possible to load firmware to RAM is after the bootloader has
initialized RAM but before the application has started. To handle this,
MP1-Boot has a "Freeze pin" option. When this pin is detected low (jumper is
installed), then MP1-Boot will halt execution (freeze) after initializing RAM.
 
#### Load into NOR Flash over DFU-USB

Loading onto NOR Flash will flash the firmware into the on-board FLASH chip so
you can boot normally without a computer connected. It takes a minute or two,
so this is a good way to flash firmware infrequently, for example, flashing the
latest stable firwmare version. This is not recommended if you're doing active
firmware development (use SWD/JTAG in that case).

Power cycle the module while holding down the rotary encoder button. This
forces an alt firmware to be loaded from NOR Flash (which is a USB-DFU
bootloader). If you are using the UART console, then you'll see this in the
console:

```
USB DFU Loader Starting...
QSPI is initialized.
Connect a USB cable to the computer.
Run `dfu-util --list` in a terminal and you should see this device.
```

The button will be flashing green when in USB-DFU bootloader mode.

Connect a USB cable from a computer to the module. 

You can use a web-based loader [such as this
one](https://devanlai.github.io/webdfu/dfu-util/). Click Connect, and then
select "STM Device in DFU Mode". Then click "Choose File" and select the uimg
file you just built at `build/mp1corea7/medium/main.uimg`. Then click
"Download". There may be an error `DFU GETSTATUS failed: ControlTransferIn
failed: NetworkError: Failed to execute 'controlTransferIn' on 'USBDevice': A
transfer error has occurred.` This is normal, and is not an error. It's safe to
ignore this.


Or use the command line (you must have [dfu-util](https://dfu-util.sourceforge.net/) installed):

```
dfu-util -a 0 -s 0x70080000 -D build/mp1corea7/medium/main.uimg
```

This command loads the main.uimg file to the default address (0x70080000).

When it's done, unplug the USB cable, power-cycle, and the new code will start up.



#### Boot from SD Card

Use `dd` to copy main.uimg to the third partition of an SD Card that contains mp1-boot on the first two sectors. 
Then, change the BOOT DIP switches to be both to the left (see diagram on PCB). Power cycle.

(more instructions TODO)

### Converting assets

(TODO)

To create the artwork files from the SVGs, you must have Inkscape installed an on your PATH

...To Be Continued...
