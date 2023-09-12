For information on how to use the firmware simulator, please see [README.md](./README.md).

### Building the Simulator

The simulator uses SDL2, which must be installed on your host machine. It 
simulates graphics and audio output. The window can be re-sized in order to
examine precise pixel alignment.

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

See the simulator [README.md](./README.md) for arguments details.

When adding/removing assets, sometimes you need to clean the build:

```
rm -rf build
```

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
