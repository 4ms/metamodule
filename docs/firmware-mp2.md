# MetaModule MP2 ("pro") firmware

Firmware for the STM32MP25x hardware revision: 2x Cortex-A35 (AArch64, EL3
secure) + Cortex-M33.

It's built from the same `firmware/` directory as the MP1 firmware, selected by
the `METAMODULE_PLATFORM` CMake variable (the `mp2*` presets set it). The A35
application is built by `firmware/cmake/mp2.cmake`; the M33 firmware is a
separate CMake project in `firmware/src/core_m33/` (it needs the arm-none-eabi
toolchain), built as an ExternalProject and embedded in the A35 image.


## Prerequisites

- `aarch64-none-elf-gcc` (same toolchain as stm32mp2-baremetal)
- `arm-none-eabi-gcc` (same toolchain as MP1), for the M33


## Building

From `firmware/`:

```
cmake --preset mp2
cmake --build --preset mp2
```

or `make PRESET=mp2`. Until p1 boards arrive, use the `mp2-test-carrier` preset
instead of `mp2` (the mp2-devboard with the stm32mp2-baremetal breakout and a
PCM3168 module).

Produces `build-mp2/main_a35.elf` / `main_a35.bin` (`build-mp2-test-carrier/`
for the test carrier), with the M33 image (`core_m33/main_m33.bin`) embedded.
For now `main()` is a hardware bring-up test.

Load and boot it over SWD with TRACE32: `make PRESET=mp2 flash-t32`
(`flashing/flash-t32-mp2.py`). Or boot it the same way as the
stm32mp2-baremetal examples: TF-A BL2 (4ms fork) + FIP on SD card (see that
repo's README). Image packaging via FIP assembly is TODO.

For CI machines that only have `aarch64-linux-gnu-gcc`:
`cmake --preset mp2-linux-gnu && cmake --build build-mp2-linux-gnu --target a35_core`


## Layout

MP2-only files in `firmware/`:

- `src/core_a35/`, `src/core_m33/`: the A35 and M33 applications (MP1: `src/core_a7/`, `src/core_m4/`)
- `src/pro/conf/`: board conf (MP1: `src/medium/conf/`). The pro p1 pin map and
  its known hardware issues are in [src/pro/conf/README.md](../firmware/src/pro/conf/README.md).
- `src/mp2-stubs/`: stand-ins for drivers that don't exist for MP2 yet (e.g. a
  RAM-backed QSPI NOR flash), found first in the M33 include path
- `src/core_intercom/shared_index.hh`: pointers to the objects the A35 and M33 share
- `cmake/mp2.cmake`, `cmake/aarch64-none-elf-gcc.cmake`, `cmake/arch_mp25x*.cmake`
- `system/linker/stm32mp2xx_*.ld`, `system/mmu_ca35.cc`
- `system/sbrk_mp2.cc`, `system/syscall_stubs_mp2.c`: temporary, until MP2
  uses MP1's allocation and newlib support (`system/sbrk.cc`, `system/newlib/`)
- `lib/cmsis-device/stm32mp257d/`: the patched MP2 CMSIS device files
- `lib/stm32-hal/stm32mp2/`: ST HAL. Note that ST's `POSITION_VAL` is broken on
  64-bit and the A35 device headers are not in the Cube release.

Shared sources are in `firmware/src/shared_sources.cmake`.
