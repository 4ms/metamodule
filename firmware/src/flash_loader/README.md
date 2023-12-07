## NOR Flash Bootloader Updater (aka Flash Loader)

This project is not for normal use. Very occasionally the bootloader(s) need
updating.

This project contains a snapshot of the MP1-Boot and USB-DFU bootloaders that
are known to work. It does not automatically grab the latest build of either
bootloader (this is to ensure stability of the bootloaders).

This project builds the `flash_loader` firmware, also known as the Bootloader
Updater. Building this will create the
`build/src/flash_loader/flash_loader.uimg` file which is a special application
firmware that will re-flash the NOR Flash chip on your unit with the updated
bootloaders.

Note that this will have no effect if you are always booting from SD Card -- it
only changes the bootloader that runs when booting from NOR Flash. 

Both the MP1-Boot (FSBL) and the USB-DFU (user firmware updater) are
overwritten.

If something goes wrong (i.e. power disconnected) while this firmware is
running, the unit will not boot from NOR Flash. It still will boot from SD
Card, so it's not bricked!

### Usage

To use the bootloader updater, you need to run it one time like a normal
application. You do this by loading the updater image to internal NOR Flash
just like you would load a normal application firmware, and then rebooting.

1. Make sure the BOOT switches on the back are set to Flash

2. Build this firmware:

```
cd firmware
make flash_loader
```

3. Power on with the encoder pressed to enter USB-DFU mode. The button will be
   flashing green slowly.

4. Load this firmware to your unit via USB-DFU, via the command-line:

```
make flash_loader_dfu
```

Or, you can use Web-DFU in your browser. Follow the [normal firmware updating
procedure]( ../../../docs/user-firmware-update.md), but use the file
`build/src/flash_loader/flash_loader.uimg` instead of a normal firmware
`main.uimg` file.

5. Power off, and back on again (not holding down the encoder)

6. The Bootloader Updater will run, re-flashing your bootloader. Pay attention
   to the button light. If you see:

  - Alternating blue and green: Success!

  - Flashing or solid red or magenta: Failure. Make sure you are on the latest
    branch, re-compile and start over.
   
  - No lights: Bootloader Updater did not run. Perhaps you already updated this
    unit? 

7. After you see the success animation (blue/green alternating flashing light),
   load the normal application firmware, either with the command `make flash-dfu` 
   or using Web-DFU to load main.uimg.

8. Once a normal application firmware is loaded, you can just reboot into that
   application like normal. For future firmware updates, simply update normally.

Note that the updated MP1-Boot bootloader is backwards-compatible with legacy
MetaModule firmware images, as well as legacy USB-DFU bootloader images, so you
can load older versions of firmware for testing/debugging. However, the updated
MP1-Boot bootloader is not compatible with the Bootloader Updater. That is, the
Bootloader Updater will only run if booted with the legacy MP1-Boot bootloader.
If you are having issues and you need to run the Bootloader Updater from the
new bootlader for some reason, you can use the `flash_loader_nonlegacy.uimg`
file. See the Troubleshooting section below.

### Troubleshooting

If something goes wrong, you can always boot from SD Card. That is to say,
running the Bootloader Updater has no effect on the MetaModule's ability to
boot from SD Card. If somehow your bootloader gets corrupted, you could try
creating a bootable SD Card and then loading the Bootloader Updater application
onto it like this:

```
make format-sd
make flash-bootloader-sd
make flash_loader
sudo dd if=build/src/flash_loader/flash_loader_nonlegacy.uimg of=/dev/diskXs4
```

...where `/dev/diskXs4` is the 4th partition of the SD Card.

Make sure to change the BOOT switches on the back to SD Card, and then insert
the SD Card and power cycle. You should see the success animation (green and
blue flashing). After seeing that, your bootloader is updated and you can load
and run an application firmware image like normal.

Notice that here we use the `flash_loader_nonlegacy.uimg` file. This is the
same as the other uimg file except that the uimg header is compatible with the
new (non-legacy) bootloader and not with the old (legacy) bootloader. If you
already have an SD Card with the old bootloader, then you could just type the
last line (`sudo dd...`) and use `flash_loader.uimg` since that uimg file is
compatible with the old bootloader.

