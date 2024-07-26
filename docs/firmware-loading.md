-------------------------------------------------------

## Important breaking change!
Firmware releases 0.6.0 and later require a new bootloader.
If you received your hardware unit prior to Dec 12, 2023 
then you have the old bootloader and you MUST update your bootloader in order to run new firmware.

If you are booting from Flash (not SD Card), do this:
- Go to the (GitHub Releases page)[https://github.com/4ms/metamodule/releases]
- Look for Firmware Version 0.6.0. 
- Download the `flash_loader.uimg` file.
- Use Web-DFU or command-line dfu-util to upload this to your device as if it were a normal firmware update. 
- Reboot so that the flash loader can run once. When the lights blink green and blue, power off.
- Now download the latest normal firmware update (`main.uimg`) file from GitHub Releases and load it using Web DFU or dfu-util.
- For instructions using Web-DFU, see the [user firmware update page](../docs/user-firmware-update.md)
- For more instructions on the Flash Loader, see its [README](src/flash_loader/README.md)

If you are booting from SD Card (not flash), then you need to copy the new bootloader to the SD Card.
```
sudo dd if=firmware/src/flash_loader/fsbl.stm32 of=/dev/diskXs1
sudo dd if=firmware/src/flash_loader/fsbl.stm32 of=/dev/diskXs2
```
... where `/dev/diskXs1` and `/dev/diskXs2` are the first and second partitions of your SD Card.

Alternatively, you could create a new SD Card by following the 
Boot from SD Card instructions below.

-------------------------------------------------------

## Loading firmware onto the MetaModule

You have several choices for how to load the firmware applcation. Each one is covered 
in a section below:

1) Load via the in-app updater

2) Load in RAM over SWD/JTAG

3) Load into NOR Flash over DFU-USB

4) Boot from SD Card


### Load via in-app updater

This method is primarily used for users or those porting modules from VCV Rack to MetaModule.
The instructions are here: [MetaModule Users Guide](./user-firmware-update.md)


### Load in RAM over SWD/JTAG

![PCB header locations](./images/pcb-headers.png)

This is the preferred method for active firmware development. It requires a
JTAG programmer.

Attach a JTAG debugger to the 10-pin connector at the top of the module labeled
"SWD". The protocol is actually JTAG, despite the header's name, though SWD may
work since the only difference is the tRST pin instead of NRST.

If you are already running the application and just need to debug, you can just
attach without loading.

If you need to load new firmware and then debug it, then follow the guide in
[Debugging with gdb](firmware-debugging.md).

To load firmware (without debugging) with a JLink programmer, do this:

1) Install a "Freeze jumper" on `Control Expander` header that bridges the top-left pin
and the pin just to the right of it. Make sure you use the right header, it's
the one above the Wifi header, near the `y` and `z` pots. The jumper should be
horizontal, not vertical, on the top row of pins all the way to the left:

```
  Control
 Expander
          [====] o  o 
           o  o  o  o
```

See image above for reference.

2) Power off and back on (full power-cycle is required).

The console will show:

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

This should take 15-30 seconds. 
 
### Load into NOR Flash over DFU-USB

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

