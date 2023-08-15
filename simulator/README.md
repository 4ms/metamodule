## MetaModule Simulator

This simulates the screen and the audio outputs. The pixels should be identical to the actual hardware's pixels.

The audio should be 1:1 the same as in hardware (though, your sound card might be AC-coupled, vs. the hardware is DC-coupled).

### Arguments
 
Command-line arguments can be passed to the executable. To see the valid arguments, run:

```
build/simulator -h
```

Or you can type `-help` instead of `-h`

Currently these are the options:

#### Audio Output Device

`-a #`: specify the audio device index to use. Run the simulator and look at the console log to see what devices
are available. For example, you might see:

```
SDL: 3 audio devices found
0: DELL P2415Q (selected)
1: Studio Display Speakers
2: Mac Studio Speakers
```

Device 0 is chosen if the option is not specificed. If you were to do:

```
build/simulator -a 1
```

then the Studio Display Speakers would be chosen.


#### Zoom level

`-z ###': specify the initial zoom amount, as a percentage. Default is 100 (1 hardware pixel = 1 simulator pixel). 

A zoom of 300 or more is useful for inspecting pixel alignment.

You can also change the zoom while the simulator is running by re-sizing the window with the mouse. 

#### Patch files

There are two mock "volumes" containing patch files. The `Internal` volume is the list of factory default patches. 

Patches are also loaded from a local host computer directory, and appear in the `SD Card` volume.

The directory to search or patch files can be passed as an argument to the simulator:

```
build/simulator -p path/to/patchfile/dir/
```

If no path is specified, `../shared/patch/` will be used. 

If a directory with no valid patch files (or an invalid directory) is specificed, the simulator will print an error and just load the Internal volume(default patches).

  
