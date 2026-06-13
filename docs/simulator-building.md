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
