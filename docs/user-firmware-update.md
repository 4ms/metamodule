## MetaModule Users Guide:


### How to upgrade firmware:

This method works if you are running firmware v0.7.x or later. For earlier
versions, use the USB-DFU method described in the next section. You can check
your current firmware version by clicking Settings from the Main Menu. 


1) Download the latest firmware release from the [MetaModule Github
releases](https://github.com/4ms/metamodule/releases). You only need the
`metamodule-firmware-vX.X.X-main.zip` file.

2) Unzip this file. It will create a folder called `metamodule-firmware`

3a) Copy the unzipped files to the SD Card or USB Drive:

    - If you are upgrading from v0.8.x or v0.7.x, then copy the *contents* of
      the `metamodule-firmware` folder to the SD card or USB drive (not the
      folder itself).

    - If you are upgrading from v0.9.x or later, then copy the entire
      `metamodule-firmware` folder to an SD card or USB drive (the folder *and*
      the contents).

4) Insert the SD card or USB drive into the MetaModule.

5) Go to the Main Menu > Settings > Update

6) It will detect the `metamodule-firmware/metamodule.json` file and display an
"Update Firmware" button. Click this button. A pop-up will display making sure
you want to update. Click OK.

7) Wait for it to perform the update, and do not power off until it's done. If
it fails, it's best to reboot before trying again.


### USB-DFU update method (when upgrading from v0.7.x and earlier):

1) Download the latest firmware release from the [MetaModule Github
releases](https://github.com/4ms/metamodule/releases). Unzip the files. You
only need the main.uimg file, the other files are just for doing debugging.

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


### How to upgrade your bootloader for old units (pre-December 12, 2023)

**You only need to do this if you received your beta MetaModule prior to Dec 12,
2023 (firmware version 0.5.1 and earlier).**

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
