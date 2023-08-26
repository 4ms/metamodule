For information on how to use the firmware simulator, please see [README.md](./README.md).

### Building Simulator

The simulator uses SDL2, which must be installed on your host machine. It 
simulates graphics and audio output. The window can be re-sized in order to
examine precise pixel alignment.

See the [README.md](simulator/README.md) in the simulator directory for details on using the simulator.

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

See the simulator README.md for arguments details.

When adding/removing assets, sometimes you need to clean the build:

```
rm -rf build
```

As a shortcut, there is a Makefile wrapping the above cmake commands. (Yes,
Makefile running Cmake generating Ninja) So, you can just do:

```
# Generate build system (if needed) and build:
make

# Run the simulator:
make run

# Clean:
make clean
```

The `make run` doesn't allow you to pass arguments.