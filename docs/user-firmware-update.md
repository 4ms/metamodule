## MetaModule Users Guide:

To have a patch play automatically at startup:

 - Save the patch as `patch.yml` and put it on the SD Card
 - If there are any supporting files (.wav files, etc), then put them on the SD Card also

To load plugins:

 - Put plugins in the `metamodule-plugins/` folder on the SD Card or USB drive.
 - Make sure there's a file called `preload_all_plugins` on the SD Card or USB drive. If 
   it's not present on the SD Card or USB drive then make a new file with that name
   (the contents of the file don't matter). The file should go in the root of the drive,
   (NOT inside the plugins folder).

To auto update the firmware:

 - Put the `metamodule-firmware/` folder on this SD Card, like you normally would do to update MetaModule firmware.
 - Rename the file `done_autoupdate_fw` to `autoupdate_fw`. If for some reason this file is not present, then just make a blank text file and save it as `autoupdate_fw`.
 - Reboot. It will automatically install the new firmware and then when it's done it'll rename the file `done_autoupdate_fw` and then reboot.


To make an SD Card like this one for another mp153-devboard:

 - Make sure it is FAT32 format
 - Create or copy all of the above files and folders (patch.yml, metamodule-plugins dir, preload_all_plugins file)

To use a JTAG debugger:

 - Attach debugger to the 10-pin header (small pins, 1.27mm spacing).
 - Install a jumper on the two left-most pins of the right-angle header. These are the two pins closest to the JTAG header. This is known as the "FREEZE jumper".
 - Optionally (recommended!!!) attach a UART-USB dongle to the right-most pins on the right-angle header. The top pin is UART TX (devboard TX -> computer RX) and the bottom pin is GND.
 - Power off and back on
 - You will see a message on the console telling you to load firmware, and then set a certain register. 
 - Follow the instructions at [firmware-debugging.md](docs/firmware-debugging.md) for GDB, Ozone, TRACE32, VSCode, etc, depending on what tools you want to use.



### USB-DFU update method:

1) Build firmware and find the `build/main.uimg` file.

2) Connect a USB cable from a computer to the module.

3) Power cycle the module while holding down the USB DFU button on the dev board.

4) The UART console will say a message saying you're in DFU bootloader mode.

5) Open [this web-based DFU
loader](https://devanlai.github.io/webdfu/dfu-util/)

6) Click Connect, and then select "STM Device in DFU Mode". 

7) Then click "Choose File" and select the main.uimg file you just downloaded.

8) Click "Download".

9) Wait a couple minutes... it takes a while. There will be this error message:

`DFU GETSTATUS failed: ControlTransferIn failed: NetworkError: Failed to
execute 'controlTransferIn' on 'USBDevice': A transfer error has occurred.`

This is normal, and is not a problem. It's safe to ignore this.

10) When the web page says it's done, then unplug the USB cable and power cycle
the module

