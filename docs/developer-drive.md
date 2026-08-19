# Developer Drive: installing plugins over USB

When Developer Mode is enabled, the MetaModule presents a small USB drive to
your computer alongside the USB console and MIDI device. Just enable it in 
the preferences and connect USB cable from the MetaModule to your computer.

You can then copy a `.mmplugin` file to that drive and either eject the drive or
issue a command over the console. The MetaModule will automatically install the plugin 
(uninstalling any existing plugins with the same name) letting you rapidly develop
and update plugins without swapping SD cards or USB drives.

Typically you use this with the console (see below).

## Enabling Developer Mode

- Plug a USB cable from the MetaModule's USB-C jack to your computer.
- Preferences > USB:
  - Set **USB Mode** to `Auto` or `Device Only`
  - Set **Device Mode** to `MIDI` (not `Video`). The drive is
  part of the same composite device as the console and MIDI ports
  - Enable **Developer Mode**


Developer Mode takes 16MB from the plugin memory pool for as long as it is
enabled. This is memory plugins would otherwise be able to use, so turn it off
when you are not developing. If the pool cannot supply 16MB (a lot of plugins
are loaded, for example), the console reports:

```
DevDrive: arena could not supply 16777216 bytes
```

Unload some plugins and toggle the setting off and on.

Once enumerated, the computer sees three things on the one cable:

| Function | Appears as |
| --- | --- |
| Console | `/dev/cu.usbmodem*` (macOS), `/dev/ttyACM0` (Linux) |
| MIDI | A MIDI port named MetaModule |
| Developer drive | A FAT volume labeled `DEV_MM` |


The volume label is what makes the drive findable at a known path
(`/Volumes/DEV_MM` on macOS) without knowing which disk device the OS assigned.

### Console

Typically you will also want to use the console at the same time as the Developer Drive.

The console is where firmware log output goes, and where the commands below are
typed. Any terminal program works, any of the following:

```
screen /dev/cu.usbmodemXXXX
```

```
minicom -c on -D /dev/cu.usbmodemXXXX
```

```
picocom /dev/cu.usbmodemXXXX
```

Besides seeing system warnings and errors in the console, you also can use it to debug. Anything you `printf()` 
in your plugin code will appear in the console.


## Installing a plugin: the script

`firmware/flashing/dev_drive.sh` does the whole sequence hands-off. 
When you have an `.mmplugin` file ready to test, call it like this:

```
firmware/flashing/dev_drive.sh MyPlugin.mmplugin /dev/cu.usbmodem14201
```

There's an optional third argument, which is the volume label. If missing it defaults to `DEV_MM`.

It mounts the drive if it is not mounted, copies the plugin, unmounts it, sends
`INSTALL` over the console, and waits for the drive to come back. If the drive doesn't 
come back, it mounts it itself, It works the same on macOS and
Linux. 

On Linux, mounting by label needs either an `/etc/fstab` entry for
`LABEL=DEV_MM` or `udisksctl` available.



## Installing a plugin: by hand

Two methods, depending on if you rely on the terminal or your OS's GUI:

**Eject in Finder (or your file manager)**: copy the `.mmplugin` file (drag and drop), 
then eject the DEV_MM volume. The MetaModule sees the eject and installs whatever is
on the drive. Then the MetaModule re-enumerates itself, so the drive should come back.
The console and MIDI ports will briefly disconnect. The sheer variety of OS's makes it
impossible to test this on every platform, so if this method doesn't work for you, use
the script or the manual Unmount->INSTALL method below.


**Unmount, then `INSTALL`**

```
cp MyPlugin.mmplugin /Volumes/DEV_MM/
diskutil unmount /Volumes/DEV_MM     # or: umount /mnt/DEV_MM
echo INSTALL > /dev/cu.usbmodemxxxxxx
```

Unmounting (rather than ejecting) leaves the USB device attached, so only the
volume goes away. It's important to unmount before running `INSTALL` or else the OS 
might cache the filesystem or do background writes while the MetaModule is reading
and writing the filesystem. The next time you try to copy a file, it'll corrupt
the drive.


Either way, watch the console to see what happened:

```
DevDrive: found plugin MyPlugin.mmplugin
DevDrive: installing MyPlugin.mmplugin
DevDrive: installed MyPlugin.mmplugin
DevDrive: medium restored
```

Note that after the install finishes, the drive might not show up in your OS.
If it doesn't, run `diskutil mount DEV_MM` or `mount -L
DEV_MM`. If you use the script, it does this for you.


## Console commands

Type these into the USB console, one per line. They are case-insensitive.

| Command | What it does |
| --- | --- |
| `install` | Install any `.mmplugin` files on the drive, then give the drive back |
| `eject` | Remove the medium, as if the host had ejected it |
| `mount` | Put the medium back. May require mounting from the OS, too |
| `status` | Report whether the drive is enabled, whether the medium is present, and list the `.mmplugin` files on it |
| `col` | Console color on |
| `mono` | Console color off (the default) |
| `help` (or `?`) | List the commands |


## Details

For each `.mmplugin` file in the root of the drive, in turn:

1. If a plugin of the same name is already loaded, the currently-playing patch
   is stopped and any patch using modules from that plugin is closed, then the
   plugin is unloaded. This is the same path the Plugin tab uses when you unload
   a plugin from the GUI.
2. The plugin is installed from the drive.
3. On success the file is deleted from the drive, so the next eject does not
   install it a second time.
4. A notification appears on the screen, and the result is logged to the
   console.

The install runs one step per GUI loop pass, so the screen stays responsive
while a large plugin is unpacked and linked.

Files are only seen in the root of the drive. Dot-files and zero-length 
files are skipped.


### Limitations

- **The current patch is not reloaded.** Replacing a plugin that the playing
  patch uses stops the patch and closes it. Re-open it by hand to hear the new
  build. If you didn't save your patch, it will be lost.
- **The drive is not persistent.** It is formatted fresh each time Developer
  Mode is enabled, and its contents are lost on power-down.
- **16MB total**, so one plugin at a time for large plugins.
- **The USB serial number is fixed** across MetaModules. Windows in particular
  keys removable-media handling off it, so using two MetaModules at the same time
  on one Windows host is untested.


### Troubleshooting

**The drive never appears.** Check that Developer Mode is saved, USB Mode is not
`Host Only`, Device Mode is `MIDI`, and that you re-plugged the cable since
enabling it. The console prints `Starting USB MIDI + console device + developer
drive` at enumeration when the drive is included.

**The drive appears but `INSTALL` does nothing.** Check the console for
`DevDrive: no .mmplugin files in the root directory`. If the OS still had the
volume mounted when you sent `INSTALL`, its cached copy may have hidden the file
or been written back afterwards. Always unmount before issuing "INSTALL" (or use the script).

**The install fails.** The console prints the loader's error. The usual causes
are the same ones you would hit installing from an SD card: unresolved symbols,
a plugin built against a different SDK version, crashing in the `init()`, etc.

**After ejecting in Finder, nothing comes back.** The re-enumeration takes about
a second. If the device does not return, unplug and re-plug the cable, or try
using the script or manual Unmount->INSTALL method.
