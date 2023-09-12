### Building Firmware

This requires `arm-none-eabi-gcc` version 12.2 or later installed on your PATH.
Please see the [setup guide](../Setup.md) for some important notes about this.

Make sure you are in the right branch and you already updated the submodules.

To prepare the build system: (only needs to be run once)

```
make configure
```

To compile, run:

```
make all
```

The `make configure` command is a shortcut for running:

```
# MacOS, Linux:
cmake --fresh --preset base -GNinja

# MinGW:
cmake --fresh --preset base -G"Unix Makefiles"
```

(The work-around for MinGW is documented with [issue #78](https://github.com/4ms/metamodule/issues/78))

The `make all` command is a shortcut for running:

```
cmake --build --preset base
```

*Optional*: If you plan to flash firmware to an SD Card, then you can specify the
path the SD Card device to save time. If you don't do this, then the system
will prompt you whenever you run one of the SD Card flashing scripts. The
device path should be to the entire SD Card device (not just one partition).
```
cmake --preset base -DSD_DISK_DEV=/dev/disk4

# Alternatively, set an environment variable:
export SD_DISK_DEV=/dev/disk4
```

The firmware is built as `firmware/build/mp1corea7/medium/main.elf` and `main.uimg` 
in the same directory. The .elf file is used when debugging, and the .uimg file
is used when copying firmware to NOR Flash or an SD card.

*Optional*: if you have multiple versions of the gcc arm toolchain installed and don't want to 
change your PATH for this project, you can set the METAMODULE_ARM_NONE_EABI_PATH var like this:

```
# Put in your bashrc/zshrc for convenience:
# Note the trailing slash (required)
export METAMODULE_ARM_NONE_EABI_PATH=/path/to/arm-gnu-toolchain-12.x-relX/bin/
```

### Console output

You can view the console output by connecting a USB-UART cable to the TX pin of
the debug header (next to the SWD header). The TX pin is labeled (upper-right
pin). The bottom four pins are all GND. Settings are 115200, 8N1.


### Loading firmware onto the device

You have several choices for how to load the firmware applcation. Each one is covered 
in a section below:

1) Load in RAM over SWD/JTAG

2) Load into NOR Flash over DFU-USB

3) Boot from SD Card


#### Load in RAM over SWD/JTAG

This is the preferred method for active firmware development. It requires a
JTAG programmer.

Attach a JTAG debugger to the 10-pin connector at the top of the module labeled
"SWD". The protocol is actually JTAG, despite the header's name, though SWD may
work since the only difference is the tRST pin instead of NRST.

If you are already running the application and just need to debug, you can just
attach without loading.

If you need to load new firmware, then do this:

1) Install a jumper on `Control Expander` header that bridges the top-left pin
and the pin just to the right of it. Make sure you use the right header, it's
the one above the Wifi header, near the `y` and `z` pots. The jumper should be
horizontal, not vertical, on the top row of pins all the way to the left:

```
  Control
 Expander
          [====] o  o 
           o  o  o  o
```

2) Power off and back on (full power-cycle is required).

The console will show:

```
Freeze pin detected active, freezing.
Ready to load firmware to DDR RAM via SWD/JTAG.
```

Use Jflash, TRACE32, Ozone, openOCD/arm-none-eabi-gdb, etc to load the main.elf file.
If you have a JLink connected, you can program with this;

```
make jprog
```

This should take 15-30 seconds.

For other methods, just load the .elf file and then start executing from 0xC0200040.

Note: If you are familiar with flashing Cortex-M series MCUs, you will notice
some differences. One is that Flash is on an external chip. Another difference is
that the main RAM (DDR RAM) is not available until software initializes it. The
on-board NOR Flash chip has a bootloader installed
([MP1-Boot](https://github.com/4ms/mp1-boot), which is the FSBL). This is
loaded by the BOOTROM on power-up. The MP1-Boot bootloader is responsible for
initializing the DDR RAM peripheral. Obviously, this must be done before
loading the firmware into DDR RAM. So, unlike a Cortex-M chip, you must run a
bootloader before programming the device. However, one of the first things an
application does when it starts running is to enable the MMU and setup various
memory regions, some of which are not writable. Thus, the only time in which
it's possible to load firmware to RAM is after the bootloader has initialized
RAM but before the application has started. To handle this, MP1-Boot has a
"Freeze pin" option. When this pin is detected low (jumper is installed), then
MP1-Boot will halt execution (freeze) after initializing RAM.
 
#### Load into NOR Flash over DFU-USB

Loading onto NOR Flash will flash the firmware into the on-board FLASH chip so
you can boot normally without a computer connected. It takes a minute or two,
so this is a good way to flash firmware infrequently, for example, flashing the
latest stable firwmare version. This is not recommended if you're doing active
firmware development since it's slow (use SWD/JTAG in that case).

Power cycle the module while holding down the rotary encoder button. This
forces an alt firmware to be loaded from NOR Flash (which is a USB-DFU
bootloader). Make sure the jumper mentioned in the SWD/JTAG section is not installed.
If you are using the UART console, then you'll see this in the console:

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
make flash-dfu
```


This command loads the main.uimg file to the default address (0x70080000).
It calls `dfu-util -a 0 -s 0x70080000 -D build/mp1corea7/medium/main.uimg`

This will take between 60 and 120 seconds.
When it's done, unplug the USB cable, power-cycle, and the new code will start up.


#### Boot from SD Card

You need a dedicated SD Card, all contents will be erased. A 16GB card is common and works fine,
but smaller or larger should work too.

You first need to format, partition, and install the bootloader on the card. This only needs
to happen once when you use a new SD Card. 

```
make format-sd
```

This will ask you for the device path (/dev/disk4, for example). Make sure you get it right, because the
script will run `mkfs` or `diskutil eraseDisk`.

After running this, you will need to eject and re-insert the SD Card because the volumes have changed.

Then do:

```
make flash-bootloader-sd
```

This will build the bootloader (mp1-boot) and use `dd` to load it onto the first two partitions of the SD Card.
You will again be asked for the drive name.

You now have a bootable SD Card. You shouldn't need to repeat the above steps unless you get a new SD Card.

To flash the application, do this:

```
make flash-app-sd
```

This will build the application as normal, and then use `dd` to copy it to the fourth partition.

Eject the card and insert it into the Meta Module.

To tell the Meta Module to boot using the SD Card, you need to change the BOOT DIP switches.
These are located on the back of the PCB, under the screen near the rotary encoder.
They are labeled "BOOT0_2". There are two switches. Look at the diagram printed on the PCB.
To boot with the SD, both switches should be pushed to the left.
If you want to back to booting from Flash (internal Flash chip), then flip the bottom switch to the right.

### Automatically generated materials

Several files are automatically generated using python scripts, e.g. faceplate LVGL code. These generated files are already committed for a few reasons: 1) the conversion process uses some specific external programs (inkscape CLI, and a particular version of node); 2) generating all the assets takes a long time; 3) the assets don't change very often (if ever) and are completely orthogonal to the code. Also conversion from SVG to PNG can generate a file that is visually the same but has a different binary representation, causing lots of noise in the git diffs. However if you wish to (re)-generate these files, the following commands can be run:

```
# Generating LVGL image files for components
make comp-images

# Generating LVGL image files for faceplates
make faceplate-images

# Update image_list.hh
make image-list

# Updating/creating 4ms VCV artwork SVGs files from *_info.svg files
make vcv-images

# Updating/creating CoreModule *_info.hh files from *_info.svg
make module-infos

# All of the above
make regenerate-all
```

### Instructions for adding a new module (WIP)

First step is add the module code as a git submodule:

```
git submodule https://github.com/<user>/<repo> firmware/vcv_ports/<Brand>
```

Create folder:

```
firmware/src/gui/images/<Brand>/modules/
```

TODO which glue files to make/how, currently too complicated:

* `firmware/vcv_ports/glue/<Brand>/modules.cmake` - list of modules mainly + list of svgs
* `firmware/vcv_ports/glue/<Brand>/CMakeLists.txt` - creates library, include directories, compile arguments


Add the following to `firmware\CMakeLists.txt`:

```
# List of brands
set(brands
  <Brand>
  ...
)
```

You will also need to add the plugin to the Hub whitelist (see `vcv/src/mapping/module_directory.hh`).
