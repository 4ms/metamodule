### Building Firmware

This requires `arm-none-eabi-gcc` version 12.2 or later installed on your PATH.
Please see the [setup guide](../docs/Setup.md) for some important notes about this.

Make sure you are in the right branch and you already updated the submodules.

To prepare the build system: (only needs to be run once)

```
make configure
```

To compile, run:

```
make all
```

The `make configure` command is a shortcut for running:

```
# MacOS, Linux:
cmake --fresh --preset base -GNinja

# MinGW:
cmake --fresh --preset base -G"Unix Makefiles"
```

(The work-around for MinGW is documented with [issue #78](https://github.com/4ms/metamodule/issues/78))

The `make all` command is a shortcut for running:

```
cmake --build --preset base
```

### Limiting the modules built

You also can limit the modules built to substantially reduce the compilation
and link times, as well as binary size. Create a text file with the modules
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


### Using an SD Card

*Optional*: If you plan to flash firmware to an SD Card, then you can specify the
path the SD Card device to save time. If you don't do this, then the system
will prompt you whenever you run one of the SD Card flashing scripts. The
device path should be to the entire SD Card device (not just one partition).
```
cmake --preset base -DSD_DISK_DEV=/dev/disk4

# Alternatively, set an environment variable:
export SD_DISK_DEV=/dev/disk4
```

The firmware is built as `firmware/build/mp1corea7/medium/main.elf` and `main.uimg` 
in the same directory. The .elf file is used when debugging, and the .uimg file
is used when copying firmware to NOR Flash or an SD card.


### Specifying the toolchain

*Optional*: if you have multiple versions of the gcc arm toolchain installed and don't want to 
change your PATH for this project, you can set the METAMODULE_ARM_NONE_EABI_PATH var like this:

```
# Put in your bashrc/zshrc for convenience:
# Note the trailing slash (required)
export METAMODULE_ARM_NONE_EABI_PATH=/path/to/arm-gnu-toolchain-12.x-relX/bin/
```


### Automatically generated materials

Several files are automatically generated using python scripts, e.g. faceplate
LVGL code. These generated files are already committed for a few reasons: 1)
the conversion process uses some specific external programs (inkscape CLI, and
a particular version of node); 2) generating all the assets takes a long time;
3) the assets don't change very often (if ever) and are completely orthogonal
to the code. Also conversion from SVG to PNG can generate a file that is
visually the same but has a different binary representation, causing lots of
noise in the git diffs. However if you wish to (re)-generate these files, the
following commands can be run:

```
# Generating LVGL image files for components
make comp-images

# Generating LVGL image files for faceplates
make faceplate-images

# Updating/creating 4ms VCV artwork SVGs files from *_info.svg files
make vcv-images

# Updating/creating CoreModule *_info.hh files from *_info.svg
make module-infos

# All of the above
make regenerate-all
```

If you just want to re-generate one image (that is, convert one SVG to a PNG and LVGL format), then you can invoke the python script directly.

Here are some examples. These commands can be run from anywhere, but for these examples we'll show it from the firmware dir:

```
cd firmware/
```


Make sure the output directories exist first:

```
mkdir -p src/gui/images/BRANDNAME/components/
mkdir -p src/gui/images/BRANDNAME/modules/
```

Convert a component SVG:
(The DPI will be automatically detected and the output will be rescaled properly)

```
../shared/svgextract/svgextract.py convertSvgToLvgl \
                                   path/to/newcomponent.svg  \
                                   src/gui/images/BRANDNAME/components/newcomponent.c
```

Convert a faceplate SVG:
This is the same as converting a component SVG, except for Alpha blending is disabled, and the height is fixed at 240px.

```
../shared/svgextract/svgextract.py createLvglFaceplate \
                                   path/to/newfaceplate.svg \
                                   src/gui/images/BRANDNAME/modules/newfaceplate.c
```

Optionally, you can only export one layer from a faceplate SVG file by specifying the layer name as a 3rd argument:

```
../shared/svgextract/svgextract.py createLvglFaceplate \
                                   path/to/newfaceplate.svg \
                                   src/gui/images/BRANDNAME/modules/newfaceplate.c \
                                   artworklayer

```

The svgextract script can do more, to see its help and view available commands:

```
../shared/svgextract/svgextract.py 
```


