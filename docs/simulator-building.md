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

### Limiting the modules built

You also can limit the modules built to substantially reduce the compilation
and link times. Create a text file with the modules
you want built, one per line. Each line should contain an
entry in the form `Brand:Module`. For example:

```
echo "4ms:EnOsc" >> quickbuild.txt
echo "Befaco:EvenVCO" >> quickbuild.txt
echo "hetrickcv:PhasorGen" >> quickbuild.txt

make limit quickbuild.txt
```

This would tell CMake to re-configure the project and just build those three modules.
You can still open patches containing other modules, but their artwork won't be shown
and you can't play them.

