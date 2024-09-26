## Building Firmware

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
cmake --fresh --preset full -GNinja -DLOG_LEVEL=DEBUG

# MinGW:
cmake --fresh --preset full -G"Unix Makefiles" -DLOG_LEVEL=DEBUG
```

(The work-around for MinGW is documented with [issue #78](https://github.com/4ms/metamodule/issues/78))

The `make all` command is a shortcut for running:

```
cmake --build --preset full
```

You can set a different LOG_LEVEL, if you want, to control 
how much gets sent to the console via UART. See [Firmware
Debugging](firmware-debugging.md).

### Using an SD Card

*Optional*: If you plan to flash firmware to an SD Card, then you can specify the
path the SD Card device to save time. If you don't do this, then the system
will prompt you whenever you run one of the SD Card flashing scripts. The
device path should be to the entire SD Card device (not just one partition).
```
cmake --preset full -DSD_DISK_DEV=/dev/disk4

# Alternatively, set an environment variable:
export SD_DISK_DEV=/dev/disk4
```

The firmware is built as `firmware/build/main.uimg`. This binary file contains
images for the M4 and A7 cores. For debugging, the symbols are in
`firmware/build/mp1corea7/medium/main.elf` and
`firmware/build/mp1corem4/medium/main_m4.elf`..


### Specifying the toolchain

*Optional*: if you have multiple versions of the gcc arm toolchain installed and don't want to 
change your PATH for this project, you can set the TOOLCHAIN_BASE_DIR var like this:

```
# Put in your bashrc/zshrc for convenience:
# Note the trailing slash (required)
export TOOLCHAIN_BASE_DIR=/path/to/arm-gnu-toolchain-12.x-relX/bin/
```

Remember that arm-none-eabi-gcc v12.2 or v12.3 is required.


