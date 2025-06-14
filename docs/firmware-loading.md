## Loading firmware onto the MetaModule

You have several choices for how to load the firmware applcation. Each one is covered 
in a section below:

1) Load via the in-app updater

2) Load in RAM over SWD/JTAG

3) Load into NOR Flash over DFU-USB

4) Boot from SD Card


### Load via in-app updater

This method is easy and the recommended way for infrequent updates.

If you built the firmware yourself, the .zip files are located in the `build/` dir.

The instructions are here: [MetaModule Docs](https://metamodule.info/docs/getting_started.html#how-to-update-firmware)


### Load in RAM over SWD/JTAG


This is the preferred method for active firmware development. It requires a
JTAG programmer. 

Attach a JTAG debugger to the 10-pin connector at the top of the module labeled
"SWD". The protocol is actually JTAG, despite the header's name, though SWD may
work since the only difference is the tRST pin instead of NRST.

If you are already running the application and just need to debug, you can just
attach without loading.

If you need to load new firmware and then debug it, then follow the guide in
[Debugging with gdb](firmware-debugging.md).


#### Freeze Jumper

To load firmware (without debugging) with a JLink programmer, you need to install a "Freeze Jumper".

There are two bootloader versions. If you see a blue light flash when you start up normally,
then you have the current bootloader. If not, then you have the earlier bootloader.

1a) Current bootloader: The jumper goes on the two left-most pins of the 2x4 debug header. 
This is the header located next to the SWD/JTAG header that contains the connections for 
the UART (RX/TX).

```
     _      RX  TX 
    |o|  o   o   o
    |o|  o   o   o
     -
```

1b) Early bootloader (pre-Nov 2024): The jumper goes on the `Control Expander` header
that bridges the top-left pin and the pin just to the right of it. Make sure
you use the right header, it's the one above the Wifi header, near the `y` and
`z` pots. The jumper should be horizontal, not vertical, on the top row of pins
all the way to the left:

```
  Control
 Expander
          [o==o] o  o 
           o  o  o  o
```


Up until Nov 1, 2024 all shipped units had the older bootloader unless
you intentionally installed a newer one. 
Updating the bootloaders is done via loading a release file that has "-bl-" in the name,
where the release tag is `firmware-v2.0.0-dev-2` or later.

#### Loading firmware

Power off and back on (full power-cycle is required).

The UART console will show:

```
Freeze pin detected active: booting from DDR
Please load a multi-uimg binary into an address in DDR RAM.
Then write the address to the TAMP_BKP6 register at 0x5C00A118
System will hang until TAMP_BKP6 register is changed...
```

Connect a Jlink programmer and run this:

```
make jprog
```

This should take 8-30 seconds. The firmware should boot automatically.

 
### Load into NOR Flash over USB DFU

Simplified instructions here: [MetaModule Docs: USB-DFU Bootloader](https://metamodule.info/docs/troubleshooting.html#usb-dfu-bootloader)

#### More detailed instructions

Loading onto NOR Flash will flash the firmware into the on-board FLASH chip so
you can boot normally without a computer connected. It takes a minute or two,
so this is a good way to flash firmware infrequently, for example, flashing the
latest stable firwmare version. This is not recommended if you're doing active
firmware development since it's slow (use SWD/JTAG in that case).

First make sure the Freeze jumper is not installed.

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
file you just built at `build/main.uimg`. Then click
"Download". There may be an error `DFU GETSTATUS failed: ControlTransferIn
failed: NetworkError: Failed to execute 'controlTransferIn' on 'USBDevice': A
transfer error has occurred.` This is normal, and is not an error. It's safe to
ignore this.


Or use the command line (you must have [dfu-util](https://dfu-util.sourceforge.net/) installed):

```
make flash-dfu
```


This command loads the main.uimg file to the default address (0x70080000).
It calls `dfu-util -a 0 -s 0x70080000 -D build/main.uimg`

This will take between 60 and 120 seconds.
When it's done, unplug the USB cable, power-cycle, and the new code will start up.


### Boot from SD Card

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

Eject the card and insert it into the MetaModule.

To tell the MetaModule to boot using the SD Card, you need to change the BOOT DIP switches.
These are located on the back of the PCB, under the screen near the rotary encoder.
They are labeled "BOOT0_2". There are two switches. Look at the diagram printed on the PCB.
To boot with the SD, both switches should be pushed to the left.
If you want to back to booting from Flash (internal Flash chip), then flip the bottom switch to the right.

