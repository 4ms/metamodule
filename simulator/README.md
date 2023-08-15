## MetaModule Simulator

This simulates the screen and the audio outputs. The pixels should be identical to the actual hardware's pixels.

The audio should be 1:1 the same as in hardware (though, your sound card might be AC-coupled, vs. the hardware is DC-coupled).

### Keyboard Control

The simulator simulates the hardware's rotary encoder, button, knobs, and jacks
(patching/unpatching) using the host computer's keyboard.

#### Navigation

- `Left Arrow`: Turn encoder counter-clockwise
- `Right Arrow`: Turn encoder clockwise
- `Down Arrow`: Press the encoder
- `Up Arrow`: Press the button (typically goes to the previous page)

#### Knobs

The knobs on the Metamodule are labeled with letters (A-F, and u-z). These can be turned with the keyboard
by first pressing a letter to select the knob you want to turn, and then pressing ] or [ to increment/decrement the knob;

- `a`: select knob A
- `b`: select knob B
- `c`: select knob C
- `d`: select knob D
- `e`: select knob E
- `f`: select knob F
- `u`: select knob u
- `v`: select knob v
- `w`: select knob w
- `x`: select knob x
- `y`: select knob y
- `z`: select knob z

- `[`: turn knob down 5%
- `]`: turn knob up 5%

TODO: make `{` and `}` inc/dec by small amounts

#### Audio Routing
By default, Audio Out 1 and Audio Out 2 are patched to the soundcard's left and right outputs, respectively.
Pressing a number button will change the routing:

- `1`: Audio Out 1 -> Left, Audio Out 2 -> Right
- `2`: Audio Out 2 -> Left, Audio Out 3 -> Right
- `3`: Audio Out 3 -> Left, Audio Out 4 -> Right
- `4`: Audio Out 4 -> Left, Audio Out 5 -> Right
- `5`: Audio Out 5 -> Left, Audio Out 6 -> Right
- `6`: Audio Out 6 -> Left, Audio Out 7 -> Right
- `7`: Audio Out 7 -> Left, Audio Out 8 -> Right
- `8`: Audio Out 8 -> Left, Audio Out 1 -> Right

For now, the only way to test the inputs of a virtual module is to create a patch that runs signals
from a virtual module into the virtual module to be tested.
Future features include:
- Route a .wav file on the host computer to an input jack and play it on startup, and/or when a key is pressed.
- Route an audio interface's input jacks to input jacks.

### Arguments
 
Command-line arguments can be passed to the executable. To see the valid arguments, run:

```
build/simulator -h
```

Or you can type `-help` instead of `-h`

Currently these are the options:

#### Audio Output Device

`-a #`: specify the audio device index to use for output. Run the simulator and look at the console log to see what devices
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

  
