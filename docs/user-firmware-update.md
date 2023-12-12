## MetaModule Users Guide:

### How to upgrade firmware

1) Download the latest firmware release from the [MetaModule Github
releases](https://github.com/4ms/metamodule/releases). You only need the
main.uimg file, the other files are just for doing debugging.

2) Connect a USB cable from a computer to the module.

3) Power cycle the module while holding down the rotary encoder.

4) The button will be flashing green, this tells you that you are in USB-DFU
bootloader mode

5) Open [this web-based DFU
loader](https://devanlai.github.io/webdfu/dfu-util/)

6) Click Connect, and then select "STM Device in DFU Mode". 

7) Then click "Choose File" and select the main.uimg file you just downloaded.

8) Click "Download".

9) Wait a couple minutes... it takes a while. There may be this error message:

`DFU GETSTATUS failed: ControlTransferIn failed: NetworkError: Failed to
execute 'controlTransferIn' on 'USBDevice': A transfer error has occurred.`

This is normal, and is not a problem. It's safe to ignore this.

10) When the web page says it's done, then unplug the USB cable and power cycle
the module


### How to upgrade your bootloader

**You only need to do this if you received your beta MetaModule prior to Dec 12,
2023.**

1) Download the `flash_loader.uimg` file from the [MetaModule Github
releases](https://github.com/4ms/metamodule/releases) for Firmware version
v0.6.0. If you don't see a file with this exact name, make sure you are looking
at Firmwa Release version 0.6.0

2) Follow the instructions in the section above, starting with step 2. When you
get to step 7, select the `flash_loader.uimg` file that you just downloaded.

3) After you power cycle, the unit will run the flash loader to update your
bootloader. This will take just a few seconds. When it's done, the button will
flash blue and green. 

3) Power your unit down.

4) Now you may update your firmware normally. Follow the instructions in the
section above to update to the latest release.

Note: You do not need to do this before each firmware update. Once you see the
button flash green and blue, your bootloader is updated and you do not need to
repeat the procedure again.
