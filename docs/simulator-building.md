### Building the Simulator

The simulator uses SDL2, which must be installed on your host machine. It 
simulates graphics and audio output. 
Install the requirements as described in [Setup](../docs/Setup.md)

Make sure you are in the right branch and you already updated the submodules.

Go to the simulator directory:

```
cd simulator
```

Generate the build system:

```
cmake -B build -GNinja      #Or whatever build system you want
```

Build it:

```
cmake --build build
```

Run it:

```
build/simulator

# To see the possible command-line arguments:
build/simulator --help
```

See the [Simulator Usage guide](simulator-usage.md) for arguments details.

As a shortcut, there is a Makefile wrapping the above cmake commands. 
You can just do:

```
# Generate build system (if needed) and build:
make

# Run the simulator:
make run

# Clean:
make clean
```

Note that `make run` doesn't allow you to pass arguments.

## Adding/removing PNG images from assets directory

When adding/removing images in the `firmware/assets` dir, you must re-build the assets tar image before the simulator will 
show the updated image assets. This is done automatically whenever you build the firmware normally, or you can build the `asset-image` cmake target:

```
# edit/add/remove some graphical asset in the firmware/assets dir

cd ../firmware
cmake --build build -- asset-image
cd ../simulator

# now running the simulator will use the updated assets
```

The reason is that the simulator does not access the `firmware/assets` dir on the host filesystem
directly, instead it does the same thing that the firmware does: untar the assets tarball into a virtual FatFS ram disk. 
