# MetaModule MP2 ("pro") firmware

Firmware for the STM32MP25x hardware revision: 2x Cortex-A35 (AArch64, EL3
secure) + Cortex-M33. 

This is a sibling CMake project to `firmware/` (the MP1 "medium" firmware).

It's structured like the simulator is: separate project, but uses files from `firmware/`. Eventually we will combine this with `firmware/`, presumably by just combining like-named directories (e.g. `system/`, `lib/`)


## Prerequisites

- `aarch64-none-elf-gcc` (same toolchain as stm32mp2-baremetal)


## Building

```
cmake --preset pro
cmake --build build
```

Produces `main_a35.elf` / `main_a35.bin`. For now `main()` is a hardware bring-up test for the pro p1 board:
it probes every I2C device, lights the button LEDs, plays a triangle wave on all outputs, and prints control changes. Boot it the same way as the
stm32mp2-baremetal examples for now: TF-A BL2 (4ms fork) + FIP on SD card, or
load over SWD (see that repo's README). 

Image packaging via FIP assembly is TODO.

For CI machines that only have `aarch64-linux-gnu-gcc`:
`cmake --preset pro-linux-gnu && cmake --build build-linux-gnu --target a35_core`

## Layout

Board conf for this is in `firmware-mp2/src/pro/conf/` vs. for the original MetaModule it's in `firmware/src/medium/conf/`.
The pro p1 pin map and its known hardware issues are in [src/pro/conf/README.md](src/pro/conf/README.md).

Shared sources are in `firmware/src/shared_sources.cmake`

The patched MP2 CMSIS device files are in `firmware-mp2/lib/cmsis-device/`

ST HAL is in `firmware-mp2/lib/stm32-hal/`.
Note that ST's `POSITION_VAL` is broken on 64-bit and the A35 device headers are not in the Cube release.

