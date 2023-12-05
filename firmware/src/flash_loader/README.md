## NOR Flash Bootloader Updater (aka Flash Loader)

This project is not for normal use.

Very occasionally the bootloader(s) need updating.

This project contains a snapshot of the bootloaders that are known to work. It does not automatically
grab the latest build of either bootloader (this is to ensure stability of the bootloaders).

The `build/src/flash_loader/flash_loader.uimg` file conatins a special application firmware
that will re-flash the NOR Flash chip on your unit with the updated bootloaders.

Note that this will have no effect if you are always booting from SD Card -- it only changes
the bootloader that runs when booting from NOR Flash.

Both the MP1-Boot (FSBL) and the USB-DFU (user firmware updater) are overwritten.

If something goes wrong (i.e. power disconnected) while this firmware is running, the unit
will not boot from NOR Flash. It still will boot from SD Card, so it's not bricked!

### Usage

To use this, build the flash loader and copy the `build/src/flash_loader/flash_loader.uimg` file to a working, bootable SD Card like this:

```
make flash_loader
sudo dd if=build/src/flash_loader/flash_loader.uimg of=/dev/disk4s4
```

Replace `/dev/disk4s4` with the 4th partition of your SD Card device.

Alternatively, you can load this firmware to your unit via USB-DFU, either via the command-line:

```
make flash_loader_dfu
```

or via the Web-DFU page in your browser. Follow the normal firmware updating procedure for how to do that, using
the file `build/src/flash_loader/flash_loader.uimg`.

Once it's loaded, just reboot with no buttons held down. The flash_loader program will update the flash automatically. The button light will flash green/blue
if it succeeds. If it flashes red or magenta, then the update failed.

Finally, once you have gotten a green/blue success indication, restore the normal application firmware.
If you used dfu or Web-DFU to load this firmware, then use dfu or Web-DFU again to load the normal firmware.
Or, if you used an SD Card, then run `make flash-app-sd`.

