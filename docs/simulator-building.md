## Building the Simulator

The simulator uses SDL2, which must be installed on your host machine. It 
simulates graphics and audio output. 
Install the requirements as described in [Setup](../docs/Setup.md)

Make sure you are in the right branch and you already updated the submodules.

Go to the simulator directory:

```bash
cd simulator
```

Generate the build system:

```bash
make config-sim

# The above is a shortcut for
# cmake --fresh --preset Default -DLOG_LEVEL=DEBUG
```

`make config-sim` logs at the DEBUG level to the console. To change this, use
the second command and change `-DLOG_LEVEL=...` (levels: NONE, ERROR, WARN,
INFO, DEBUG, TRACE, DUMP).

Build it:

```bash
make

# The above is a shortcut for:
# cmake --build build
```

Run it:

```bash
make run

# The above is a shortcut for:
# build/simulator
```

Note that `make run` doesn't allow you to pass arguments.
To see the possible command-line arguments:

```bash
build/simulator --help

```

See the [Simulator Usage guide](simulator-usage.md) for arguments details.

## Simulating MetaModule MP2 (pro)

By default the simulator is built for MP1 (MetaModule). To build for MP2
(MetaModule Pro), add `PRESET=mp2` to any of the make commands above:

```bash
make PRESET=mp2 config-sim
make PRESET=mp2
make PRESET=mp2 run

# The above are shortcuts for:
# cmake --fresh --preset mp2 -DLOG_LEVEL=DEBUG
# cmake --build build-mp2
# build-mp2/simulator
```

The MP2 simulator builds in `build-mp2/`, so it doesn't overwrite the MP1 build
in `build/`. Its screen defaults to 1280x720 (MP1's is 320x240); use
`--screenw` and `--screenh` to change this.

## Debug builds

Debugging with gdb and lldb is usually easier with optimizations off (-O0). 
This is the default when running the debug build.

To (re-)build with optimizations off and run the debugger (gdb or lldb, automatically detected):

```bash
make debug
```

Playing patches with complex audio DSP may not work, as -O0 is generally too slow to process non-trivial DSP at 48kHz. If you need to debug and run with optimizations, do this:

```bash
make config-sim
make
gdb build/simulator
#or: lldb build/simulator
```

## Adding/removing PNG images from assets directory

When adding/removing images in the `firmware/assets` dir, you must re-build the
assets tar image before the simulator will show the updated image assets. This
is done automatically whenever you build the firmware normally, or you can
build the `asset-image` cmake target:

```bash
# edit/add/remove some graphical asset in the firmware/assets dir

cd ../firmware
cmake -B build -GNinja      #Or whatever build system you want
cmake --build build -- asset-image
cd ../simulator

# now running the simulator will use the updated assets
```


The reason is that the simulator does not access the `firmware/assets` dir on the host filesystem
directly, instead it does the same thing that the firmware does: untar the assets tarball into a virtual FatFS ram disk. 

If you need to force rebuilding the assets (especially useful with external plugins):

```bash
rm -rf build/assets*
make
```
