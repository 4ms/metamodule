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

For CI machines that only have `aarch64-linux-gnu-gcc`:
`cmake --preset mp2-linux-gnu && cmake --build build-mp2-linux-gnu --target a35_core`

Load and boot it over SWD with TRACE32: `make PRESET=mp2 flash-t32`
(`flashing/flash-t32-mp2.py`). Or boot it the same way as the
stm32mp2-baremetal examples: TF-A BL2 (4ms fork) + FIP on SD card (see that
repo's README). Image packaging via FIP assembly is TODO.

MP2 can't read the assets (module images, fonts) from flash yet, so the assets
image is embedded in the firmware image. The MP2 build doesn't make one yet: it
uses the MP1 build's `build/assets.uimg` (set `MP2_ASSETS_UIMG` to use
another), so build MP1 first.

## What runs

- **M33:** patch storage (MP1's `PatchStorage`): SD card, and the internal
  patch volume on the NOR flash. And the controls, which it writes into the
  param blocks the audio stream reads, as MP1's M4 does (see Controls below).
  And the USB device (see USB below).
- **A35:** MP1's GUI (`PageManager` and all the pages), rendered at MP1's
  320x240 and scaled 3x into the middle of the panel, and MP1's audio stream
  (`src/audio/audio.cc`), which plays the patch in the codec's DMA interrupt.
  The patch is split between the two A35 cores the same way as on MP1: the
  second core runs MP1's `AuxPlayer` (`src/core_a35/aux_core.cc`). Unlike MP1,
  the GUI stays on the first core, so the second core only plays modules.
  Built-in modules: the 4ms modules and the `vcv_ports` brands. The assets
  are unpacked into a RamDisk, which modules can read with libc (`fopen`, etc).
- **Not yet:** most of the hardware controls, jack sense (all jacks are reported as
  patched), MIDI, plugins, USB host mode, WiFi, and libc file access on the SD card and USB.

## NOR flash

The 16MB W25Q128JV on OCTOSPI1 (on the mp2-devboard) is driven by mdrivlib's
`OSpiFlash` (`target/stm32mp2/drivers/ospi_flash_driver.hh`), which has the same
API as MP1's QSPI driver; `src/mp2-stubs/drivers/qspi_flash_driver.hh` makes it
the `QSpiFlash` that shared code uses. The layout is MP1's
(`src/fs/norflash_layout.hh`): the boot loader (TF-A) in the first 512kB, the
patch volume (LittleFS) in the top 2MB
minus 4kB, and the calibration data in the top 4kB.

Only one core may use it at a time: the A35 reads the calibration at startup,
before it starts the M33, and after that the M33 owns it.

## Controls

The M33's `PanelControls` (`src/core_m33/panel_controls.hh`) is MP2's version
of MP1's `Controls` (`src/core_m4/controls.hh`). The param blocks
(`StaticBuffers::param_blocks`) are in `.sharedmem`, published in `SharedIndex`.
As on MP1, the audio stream releases a param block's HSEM when it's done with
it, and the M33 then fills that block. A 48kHz timer (TIM6) polls the controls,
in place of MP1's LRCLK pin interrupt.

So far only the control encoder (PC3/PC9, button PH10) and the Back button
(PA9) work, as MP1's rotary and button. Next: the 16 knob encoders and the
buttons on the I2C expanders. The knob encoders will be relative: the M33 sends
each one's motion, and the A35 adds it to the mapped parameter's value, so
nothing jumps when the knob set or patch changes.

The serial console can also navigate the GUI: Right/Left arrows (or `d`/`a`)
turn the encoder, Enter (or Down, `s`) clicks it, Backspace (or Up, `w`) is
the Back button.

## USB

The USB jack is on the USB3DR controller (a Synopsys DWC3), in USB2-only mode
through USB2PHY2. MP1's OTG core (DWC2) is different hardware, so only the
layers above the HAL are shared.

So far the M33 runs it as a device, always on: MP1's `UsbDeviceManager`
(`src/usb/usb_device_manager.hh`), the MIDI + CDC console composite, on ST's
DWC3 device HAL (`stm32mp2xx_hal_pcd_drd.c`). The MP2 parts:

- `mdrivlib::Usb3DR` (`target/stm32mp2/drivers/usb3dr.hh`): the clock, reset,
  and PHY sequence, from the stm32mp2-baremetal `usb-drd` example. Before it
  starts the M33, the A35 makes the controller secure and gives its DMA the
  M33's compartment ID (CID2), so the DMA can reach the M33's memory.
- `src/core_m33/usbd_conf.cc`: MP2's version of `src/usb/usbd_conf.cc`. The
  DWC3 always uses DMA and the HAL does no cache maintenance, so the HAL handle
  (event buffer, TRBs) and the class handles are in `.dma_nc`, a non-cacheable
  1MB at the top of the M33's memory (see `system_init.cc` and the linker
  script). IN data is cleaned from the cache before it's sent, and OUT data
  arrives in a per-endpoint buffer in `.dma_nc` and is copied to the class's
  buffer.
- ST's HAL only picks its DWC3 driver for the MP257C (`#if defined(STM32MP257Cxx)`),
  so the generic `stm32mp2xx_hal_pcd.h`/`_ex.h`/`ll_usb.h` were changed to check
  `USB3DRD_BASE`, and the M33 compiles the `_drd.c` files directly.

Not yet:
- **VBUS sensing and role detection:** the FUSB302. Until then, the controller is
  told VBUS is always valid.
- **The console over USB:** the CDC console sends MP1's per-core console
  buffers, but on MP2 each core writes to the UART directly, so they're empty.
- **MIDI routing:** received USB MIDI is printed on the console.
- **The developer drive:** the A35 publishes a `DevDriveBlock` in `SharedIndex`, but
  doesn't serve a drive yet.
- **Host mode:** the DWC3 is an xHCI host, and ST's HAL has no host driver for
  it. The stm32mp2-baremetal `usb-drd` example's host side is U-Boot's xHCI
  driver (GPL-2.0+, so it can be used here), behind MP1's USB host library.
  (Its device side is U-Boot's DWC3 gadget driver, GPL-2.0 only, which is why
  device mode uses ST's HAL instead.)


## Layout

MP2-only files in `firmware/`:

- `src/core_a35/`, `src/core_m33/`: the A35 and M33 applications (MP1: `src/core_a7/`, `src/core_m4/`)
- `src/pro/conf/`: board conf (MP1: `src/medium/conf/`). The pro p1 pin map and
  its known hardware issues are in [src/pro/conf/README.md](../firmware/src/pro/conf/README.md).
- `src/mp2-stubs/`: MP2 versions of MP1 headers, found first in the include
  paths so they replace MP1's: stand-ins for drivers and features MP2 doesn't
  have yet (the plugin loader, the assets in flash, ...), the OSPI flash
  driver as `QSpiFlash`, and headers that are MP1-specific (`ld.h`, the file buffer)
- `src/core_intercom/shared_index.hh`: pointers to the objects the A35 and M33 share
- `cmake/mp2.cmake`, `cmake/aarch64-none-elf-gcc.cmake`, `cmake/arch_mp25x*.cmake`
- `system/linker/stm32mp2xx_*.ld`, `system/mmu_ca35.cc`
- `system/sbrk_mp2.cc`: temporary, until MP2 uses MP1's allocation (`system/sbrk.cc`)
- `system/eh_frame_ca35.cc`: registers the unwind tables for C++ exceptions
  (the A35 links without `crtbegin.o`)
- `lib/cmsis-device/stm32mp257d/`: the patched MP2 CMSIS device files
- `lib/stm32-hal/stm32mp2/`: ST HAL. Note that ST's `POSITION_VAL` is broken on
  64-bit and the A35 device headers are not in the Cube release.

Shared sources are in `firmware/src/shared_sources.cmake`.
