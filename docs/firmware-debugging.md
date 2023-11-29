
# Debugging 

1) Attach a JTAG debugger to the 10-pin connector at the top of the module labeled
"SWD". The protocol is actually JTAG, despite the header's name, though SWD may
work since the only difference is the tRST pin instead of NRST.

2) Install a "Freeze jumper" on `Control Expander` header that bridges the top-left pin
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

3) Power off and back on (full power-cycle is required).

The console will show:

```
Freeze pin detected active: booting from DDR
Please load a multi-uimg binary into an address in DDR RAM.
Then write the address to the TAMP_BKP6 register at 0x5C00A118
System will hang until TAMP_BKP6 register is changed...
```

At this point you can choose to debug with gdb, Segger Ozone, VSCode, or TRACE32.
Skip to the relevant section below:

## GDB

First, you need to start a gdb server. Either openocd (v0.12.0) or Segger JLinkGDBServer
(v7.90) works.


For openocd, run this in a separate terminal window:

```
openocd -f board/stm32mp15x_dk2.cfg
```

For JLinkGDBServe, run this in a separate terminal window:

```
JLinkGDBServer -select USB=0 -device STM32MP15xx_A7 -endian little -if JTAG -speed 4000 -noir -noLocalhostOnly -nologtofile
 -port 3333 
```

You may need to adjust the command `JLinkGDBServer` for your OS (i.e. add
`.exe` and/or specify the path to it).

Or, you can launch the JLinkGDBServer GUI program. Choose JTAG for the
interface, and set the port to 3333 manually (by default it's 2331). Note: if
want to use a different port than 3333, you can change the first line in the
gdbscript (see next step).

Now that the gdb server is running in a separate terminal window, start
debugging using arm-none-eabi-gdb.

```
arm-none-eabi-gdb --command=flashing/multi.gdbinit
```

This will launch gdb and run the `multi.gdbinit` script. The script is very short
and you should inspect the contents if anything is not working. All it does is
connect to the gdb server at port 3333, and then loads the symbols from the A7
elf file. Then it loads the multi-uimg file (`build/main.uimg`) to an arbitrary
address, 0xD0000000. Finally, it notifies the bootloader to start parsing the
multi-uimg file by writing 0xD0000000 to a designated register (the TAMP_BKP6R
register).

The loading may take a while, depending on the debugger hardware (ST-LINK or JLink),
and the binary size (i.e. whether you compiled the full binary or limited it with
`make limit LIMITFILE`).


## Ozone

Instead of using command-line gdb, you can also use Segger's Ozone GUI program.
This uses gdb behind the scenes, but has a different project configuration method.

Create a new project using the Wizard: 
- Device: STM32MP15xx_A7
- Register Set: Cortex-A7
- Peripherals file: load the svd file: `flashing/STM32MP15xxx.svd`.
- Target Interface: JTAG
- ELF file: load the a7 elf file: `build/mp1corea7/medium/main.elf`
- For Initial PC and Initial Stack Pointer: Do Not Set

In the Tools > System Variables page, set "Reset Mode" to "Reset and Run".

Save the project.

After power-cycling with the Freeze jumper installed, 
select Attach & Halt Program from the Debug menu. 
 
From the File menu, select Open, and load the `build/main.uimg` file as a binary file to address 0xD0000000.

Then, use the Registers window to find the TAMP_BKP6R register and set its value to 0xD0000000.

Then, continue execution (do not reset, just "unpause").

## TRACE32

Lauterbach TRACE32 can be used to debug as well.
After power-cycling with the Freeze jumper installed, 
the `flashing/mm-a7-t32.cmm` script can be run to load the firmware and symbols.

Both A7 cores can be accessed (use the command `Core 0` for the main core, or `Core 1` for switch to the secondary A7 core).
To debug the M4 core, you can use the `flashing/switch-to-m4.cmm` script.


## Using VSCode

VSCode can be used to debug, using OpenOCD and gdb.


Some configuration files (for the mp1 bootloader, so they will need to be adapted to MetaModule):
[here](https://github.com/danngreen/stm32mp1-baremetal/tree/vscode/bootloaders/mp1-boot/.vscode)
and [here](https://github.com/kamejoko80/stm32mp1-baremetal-1/tree/vscode/bootloaders/mp1-boot/.vscode)

And also [some discussion:](https://github.com/4ms/stm32mp1-baremetal/issues/20)

TODO: Adapt this to MetaModule.



## GPIO pin debugging (pin flipping)

You can toggle some GPIO pins to indicate states from firmware with minimal impact on firmware timing.
Typically you would read the pins using an oscilloscope or logic probe.

There are 6 header pins and two SMD pads on the PCB dedicated to this. They can be used like this:

```
#include "debug.hh"   // Found in firmware/src/medium/

Debug::Pin0::high();
Debug::Pin0::low();
Debug::Pin1::set(true); //same as ::high()
Debug::Pin1::set(false); //same as ::low()
```

The pins and pads are located on the PCB as shown here:
![PCB header locations](./images/pcb-headers.png)


## Console output (printf debugging)

You can view the console output by connecting a USB-UART cable to the TX pin of
the debug header (next to the SWD header). The TX pin is labeled (upper-right
pin). The bottom four pins are all GND. Settings are 115200, 8N1. See image above.

Use `pr_dbg()`, `pr_warn()`, `pr_err()`, and `pr_trace()` for debug output. These
require the `pr_dbg.hh` header.


## Notes

### Startup

Note: If you are familiar with flashing Cortex-M series MCUs, you will notice
some differences. One is that Flash is on an external chip. Another difference is
that the main RAM (DDR RAM) is not available until software initializes it. The
on-board NOR Flash chip has a bootloader installed
([MP1-Boot](https://github.com/4ms/mp1-boot), which is the FSBL or "first-stage
bootloader"). The bootloader is loaded by the BOOTROM on power-up. MP1-Boot is
responsible for initializing the DDR RAM peripheral. Obviously, this must be
done before loading the firmware into DDR RAM. So, unlike a Cortex-M chip, you
must run a bootloader before programming the device. However, one of the first
things an application does when it starts running is to enable the MMU and
setup various memory regions, some of which are not writable. Thus, the only
time in which it's possible to load firmware to RAM is after the bootloader has
initialized RAM but before the application has started. To handle this,
MP1-Boot has a "Freeze pin" option. When this pin is detected low (jumper is
installed), then MP1-Boot will halt execution (freeze) after initializing RAM.
It'll stay halted until it detects something written to the TAMP_BKP6R
register. At that point, it will try to load a multi-uimg file from the address
written to this register. If the multi-uimg contains an entry point, it will
start executing from that point after loading.

### Multi-uimg format

The multi-uimg format is what's used for the firmware binary. This is just a
series of uimg files concatenated to each other. Each uimg section is a 64
byte header (same header as in U-Boot's uimg format), immediately followed by
the binary data. The header says how big the image is, where it should be
loaded, and optionaly where to start execution.
The multi-uimg file is generated from the M4 and A7 .elf files with the 
`flashing/elf_to_uimg.py` and `flashing/uimg_header.py` scripts.


### Multi-core debugging

Debuggers have a hard time handling multiple cores. Halting one core when
debugging (to examing a variable, for example) could cause another core to
time-out and the application will not run properly when you continue.
