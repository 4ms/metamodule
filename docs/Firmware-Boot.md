# Firmware Boot Procedure

The chip's ROM code reads the `BOOT0_2` DIP switch and then:

- either halts (if the switch is set to `Debug`)
- or attempts to load a bootloader from the SD Card (if it's set to `SD`)
- or attempts to load a bootloader from the QSPI NOR Flash chip (if it's set to
  `Flash`)

and then starts executing the bootloader.

The bootloader (which is `MP1-Boot`) initializes the DDR RAM and various system
peripherals (security, MMU, clocks). 

Then it loads the firmware image from whatever media it booted from (SD Card or NOR Flash)
from a pre-specified location. This location is also used by Linux and U-Boot.
It then starts execution from the entry point specified in one of the firmware headers.

However, if Pin 2 and 4 of the "Control Expander" (`J102`) are shortened with a
jumper, then it will halt before it loads the firmware from the boot media. It
will remain halted until it detects a new value written to the TAMP_BK6R
register. At that point it will read the value in the register as an address
and then begin loading firmware from that address just like it would load from
NOR Flash or SD Card. This allows you to load a firmware image anywhere into RAM
while it's halted, and then write the location to the TAMP register, and the
bootloader will parse, load, and execute the firmware. Loading into RAM is many times
faster than loading into NOR Flash, so this method is preferred for firmware development.

Otherwise (if no jumper detected), it will check if the rotary encoder is pressed.
If so, it loads an alternative firmware image from whatever media it booted
from (SD or Flash). All MetaModules have a USB-DFU bootloader loaded into this
sector of the NOR Flash chip The USB-DFU firmware allows you to upgrade the firmware
over USB. This is the primary method for users to update firmware (see
[MetaModule User's Guide](user-firmware-update.md)



### Secondary A7 core startup
 
Both A7 cores startup at the same time, but Core 2 (aka secondary core) will go to 
sleep immediately. The first core (primary, aka Core 1) will proceed with the
procedure descrived above.

Once the primary core is intialized, MetaModule firmware awakens the secondary
core and tells it to start executing from the `aux_core_start` assembly code in
`firmware/lib/mdrivlib/target/stm32mp1_ca7/boot/startup_ca7.s` which does some
basic stack setup and then jumps to the `aux_core_main()` function in
`firmware/src/core_a7/aux_core_main.cc`. Here, the secondary core handles the
screen updates and runs the LVGL tasks. It also gets interrupted by the primary
core to help with audio processing. 


### M4 startup

The M4 firmware is bundled with the A7 firmware in the main.uimg file. Unlike
single-core Cortex-M4 chips, after power-on there is no M4 firmware running
(there is no internal flash to store the M4 firmware). The MP1-Boot bootloader
is repsonsible for loading the M4's firmware (code and data) from flash or SD
Card to internal RAM. After the bootloader is done, the main app does some
early init on the A7 core and then starts the M4 core.

The M4 firmware is responsible for reading all controls and the gate jacks. It
also handles all USB and SD Card transactions.
