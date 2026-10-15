# MetaModule MP2 ("pro") firmware

Firmware for the STM32MP25x hardware revision: 2x Cortex-A35 (AArch64, EL3
secure) + Cortex-M33. See `docs/MP2-Port-Plan.md` for the roadmap and
decisions.

This is a sibling CMake project to `firmware/` (the MP1 "medium" firmware) —
one CMake project cannot mix the two required toolchains (aarch64-none-elf for
the A35s, arm-none-eabi for the M33). Portable app code is consumed from
`firmware/src/` via include paths and `firmware/src/shared_sources.cmake`, the
same way `simulator/` does; board config lives in `src/pro/conf/` selected by
include path (the `firmware/src/medium/conf/` mechanism).

## Prerequisites

- `aarch64-none-elf-gcc` (same toolchain as stm32mp2-baremetal)
- A sibling checkout of [4ms/stm32mp2-baremetal](https://github.com/4ms/stm32mp2-baremetal)
  for the **patched** MP2 CMSIS pack + ST HAL (or set `-DMP2_BAREMETAL_DIR`).
  Do not substitute stock ST headers: ST's `POSITION_VAL` is broken on 64-bit
  and the A35 device headers are not in the Cube release.
- mdrivlib submodule (`firmware/lib/mdrivlib`) with the `target/stm32mp2*` dirs.

## Building

```
cmake --preset pro
cmake --build build
```

Produces `main_a35.elf` / `main_a35.bin`. Boot it the same way as the
stm32mp2-baremetal examples for now: TF-A BL2 (4ms fork) + FIP on SD card, or
load over SWD (see that repo's README). Image packaging (FIP assembly, the
`elf_to_uimg.py` successor) is TODO.

For CI machines that only have `aarch64-linux-gnu-gcc`:
`cmake --preset pro-linux-gnu && cmake --build build-linux-gnu --target a35_core`
(compile-check only; the final link needs newlib).

## Layout

- `src/core_a35/` — A35 application (currently a boot skeleton on the mdrivlib
  `target/stm32mp2_ca35` boot path)
- `src/core_m33/` — M33 coprocessor firmware (placeholder; separate project)
- `src/pro/conf/` — per-peripheral board config headers (mostly TBD until the
  hardware pin list exists)
- `system/` — MMU config + linker script (copied from mdrivlib templates,
  customize here)
- `cmake/` — toolchain + arch flags for both cores
