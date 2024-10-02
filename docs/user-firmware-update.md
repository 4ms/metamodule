## MetaModule Users Guide:


### How to upgrade firmware:

1) Download the latest firmware release from the [MetaModule Github
releases](https://github.com/4ms/metamodule/releases). You only need the
`metamodule-firmware-vX.X.X-firmware-assets.zip` file.

2) Unzip this file. It will create a folder called `metamodule-firmware`

3a) Copy the entire `metamodule-firmware` folder to an SD card or USB drive (the folder *and*
    the contents).

4) Insert the SD card or USB drive into the MetaModule.

5) Go to the Main Menu > Settings > Update

6) It will detect the `metamodule-firmware/metamodule.json` file and display an
"Update Firmware" button. Click this button. A pop-up will display making sure
you want to update. Click OK.

7) Wait for it to perform the update, and do not power off until it's done. If
it fails, it's best to reboot before trying again.


### USB-DFU update method:

1) Download the latest firmware release from the [MetaModule Github
releases](https://github.com/4ms/metamodule/releases). Unzip the files. You
only need the `main.uimg` file which is inside the `metamodule-firmware` folder.

2) Connect a USB cable from a computer to the module.

3) Power cycle the module while holding down the rotary encoder.

4) The button will be flashing green, this tells you that you are in USB-DFU
bootloader mode

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

