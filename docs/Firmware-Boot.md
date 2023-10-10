# Firmware Boot Procedure

The chip's ROM code reads the `BOOT0_2` DIP switch and then:

- either halts (if it's set to `Debug`)
- or attempts to load a bootloader from the SD Card (if it's set to `SD`)
- or attempts to load a bootloader from the QSPI NOR Flash chip (if it's set to
  `Flash`)

and then starts executing the bootloader.

The bootloader (which is `mp1-boot`) initializes the DDR RAM and various system
peripherals (security, MMU, clocks). After that it halts if Pin 2 and 4 of the
"Control Expander" (`J102`) are shortened with a jumper.

Otherwise (no jumper detected), it will check if the rotary encoder is pressed.
If so, it loads an alternative firmware image from whatever media it booted
from (SD or Flash). On the Flash chip, USB-DFU "second-stage bootloader" (SSBL)
is preloaded. The SD card could also have an alternative firmware but this is
not used yet.

Otherwise (no jumper and rotary not pressed) it loads the firmware image from the
default location on the selected boot media and then starts execution.

### Secondary A7 core startup
 
Both A7 cores startup at the same time, but Core 2 (aka secondary core) will go to 
sleep immediately. The first core (primary, aka Core 1)
will proceed with the procedure descrived above.

The MetaModule firmware awakens the secondary core and tells it to start executing from
the `aux_core_start` assembly code in 'firmware/lib/mdrivlib/target/stm32mp1_ca7/boot/startup_ca7.s`
which does some basic stack setup and then jumps to
the `aux_core_main()` function in `firmware/src/core_a7/aux_core_main.cc`. Here, the
secondary core handles the screen updates and runs the LVGL tasks. It also gets interrupted 
by the primary core to help with audio processing.


### M4 startup

The M4 firmware is bundled inside the A7 firmware. After power-on there is no
M4 firmware running (there is no internal flash to store the M4 firmware), so
the M4 core is just sitting idle. The A7 core does some early init and then
loads the M4 firmware and starts that core.

The M4 firmware is responsible for reading all controls and the gate jacks. It also
handles all USB and SD Card transactions.
