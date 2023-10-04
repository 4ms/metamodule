# Firmware Boot Procedure

The chip's ROM code reads the `BOOT0_2` DIP switch and then

- either halts (if it's set to `Debug`)
- or attempts to load a bootloader from the SD Card (if it's set to `SD`)
- or from the QSPI NOR Flash chip (if it's set to `Flash`)

and then starts executing the bootloader.

The bootloader (which is `mp1-boot`) initializes the DDR RAM and various system peripherals (security, MMU, clocks).
After that it halts if Pin 2 and 4 of the "Control Expander" (`J102`) are shortened with a jumper.

Otherwise it will check if the rotary encoder is pressed. If so, it loads an alternative firmware image from whatever media it booted from (SD or Flash). On the Flash chip, USB-DFU "second-stage bootloader" (SSBL) is preloaded. The SD card could also have an alternative firmware but this is not used yet.

Otherwise - if the rotary is not pressed - it loads the firmware image from the default location on the selected boot media and then starts execution.

The M4 firmware is bundled inside the A7 firmware.
After power-on there is no M4 firmware running (there is no internal flash to store the M4 firmware), so the M4 core is just sitting idle.
The A7 core does some early init and then loads the M4 firmware and starts that core.
