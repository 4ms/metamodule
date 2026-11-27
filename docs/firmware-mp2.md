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

Produces `build-mp2/main_a35.elf` and `build-mp2/main.uimg`
(`build-mp2-test-carrier/` for the test carrier), with the M33 image
(`core_m33/main_m33.bin`) embedded.

For CI machines that only have `aarch64-linux-gnu-gcc`:
`cmake --preset mp2-linux-gnu && cmake --build build-mp2-linux-gnu --target a35_core`

Load and boot the ELF over SWD with TRACE32: `make PRESET=mp2 flash-t32`
(`flashing/flash-t32-mp2.py`).

Or boot `main.uimg` the same way as the stm32mp2-baremetal examples: TF-A BL2
(4ms fork) loads it from the SD card's `app` partition (see that repo's README).
This has not been tried on hardware yet.

`main.uimg` is a self-extracting image, like MP1's (`flashing/selfextract_mp2`).
TF-A loads one image to one place, 32MB at most (`_A35_BOOT` in
`system/linker/memory_mp2.ld`). The A35 image is bigger than that, and its code
and its `.data` go to different places. So TF-A loads a small stub with the A35
image LZ4-packed inside it, and the stub unpacks each part to where it's linked
and jumps to it. The build fails if the packed image is over 32MB.
`flashing/selfextract_mp2/test_qemu.py` runs the stub in QEMU and checks what it
unpacked. If the image is corrupted, the stub hangs without printing anything.

MP2 can't read the assets (module images, fonts) from flash yet, so the assets
image is embedded in the firmware image. It's the MP1 build's
`build/assets.uimg` (set `MP2_ASSETS_UIMG` to use another), so build MP1 first,
with the SVG faceplates and components in `firmware/assets-svg/` in place of
the PNG ones.

MP2 draws module faceplates and components from SVG files only. They are still
named by their `.png` files (in the module info, and by plugins): the `.svg`
file with the same path is what's drawn, and a module or component that has no
SVG is not drawn (`src/gui/elements/svg_file.hh`).

## What runs

- **M33:** patch storage (MP1's `PatchStorage`): SD card, and the internal
  patch volume on the NOR flash. And the controls, which it writes into the
  param blocks the audio stream reads, as MP1's M4 does (see Controls below).
  And the USB device (see USB below).
- **A35:** MP1's GUI (`PageManager` and all the pages), rendered at MP1's
  320x240 and scaled 3x into the middle of the panel, and MP1's audio stream
  (`src/audio/audio.cc`), which plays the patch in the codec's DMA interrupt.
  The patch is split between the two A35 cores the same way as on MP1: the
  second core runs MP1's `AuxPlayer` (`src/core_a35/aux_core.cc`). As on MP1,
  the second core also runs the GUI: only the first core does the parts of each
  audio frame that aren't split between the cores, so the second core has time
  left for the GUI even when the first is overloaded.
  Built-in modules: the 4ms modules and the `vcv_ports` brands. The assets
  are unpacked into a RamDisk, which modules can read with libc (`fopen`, etc).
- **Plugins:** `.mm2plugin` files (AArch64 builds, made by the plugin SDK next to the
  `.mmplugin`), loaded by MP1's plugin loader from the SD card, USB drive, or developer drive. The
  M33 finds them and sends the A35 the list (`src/dynload/plugin_list_serial.hh`).
- **Not yet:** most of the hardware controls, jack sense (all jacks are reported as
  patched), MIDI, WiFi, and libc file access on the SD card and USB (from modules and plugins).

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
it, and the M33 then fills that block, one frame per audio frame, from an
interrupt on the SAI's frame clock (LRCLK, PE11, EXTI1 line 11:
`src/pro/conf/frame_rate_conf.hh`, mdrivlib's `stm32mp2_cm33/drivers/pin_change.hh`),
like MP1's LRCLK pin interrupt. The HSEM interrupt only flags the new block; the
frame interrupt switches to it. The M33 says on the console once the frame clock
interrupts start (or that they haven't, 15s after it starts).

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

The M33 runs MP1's `UsbManager` (`src/usb/usb_manager.hh`) unchanged: the
FUSB302 picks the role (and handles PD and the awkward partners, as on MP1). As
a device it runs MP1's `UsbDeviceManager`, the MIDI + CDC console composite, on
ST's DWC3 device HAL (`stm32mp2xx_hal_pcd_drd.c`). As a host it runs MP1's
MIDI and USB drive class drivers on an xHCI driver (see Host mode, below). The MP2 parts:

- `src/pro/conf/fusb30x_conf.hh`: the FUSB302's pins. On the test carrier
  (`MP2_TEST_CARRIER`): INT_N on PD13, VBUS load switch on PB4. On the pro p1:
  INT_N on PE9, load switch on PD13.
- The FUSB302 is on I2C4, which the A35 also uses (the codec; on the pro, jack
  sense too). Both cores hold the `SharedI2CLock` hardware semaphore
  (`src/core_intercom/shared_i2c_lock.hh`) while using it: the A35 around the
  codec's `init()` (the only codec call that uses I2C, see
  `src/pro/conf/board_codec_conf.hh`), the M33 around constructing `UsbManager`
  (which resets and initializes I2C4) and each `UsbManager::process()`.
- Settings and status cross the cores as on MP1: the GUI sends the USB role
  and device mode with `DeviceSettingsProxy` (IPCC channel 4), and the M33
  publishes the connection status into a `UsbConnectionStatusBlock` that the
  GUI reads (`usb/usb_status_reader.hh`). Both live in the A35's `.sharedmem`,
  published in `SharedIndex`.
- USB MIDI to and from the patch: `PanelControls` (`src/core_m33/panel_controls.hh`)
  does what MP1's `Controls::parse_midi()` does, each audio frame, with the USB
  MIDI host or device (whichever is connected).
- DIN5 MIDI: the jack board's DIN5 jacks are on USART6 (`src/core_m33/din_midi.hh`),
  polled from the same frame interrupt. They're MP1's MIDI Expander's DIN5 port, always
  connected; the pro has no TRS MIDI port. The GUI's port dropdowns and the modules' MIDI
  port menus list the board's ports (`conf/midi_ports_conf.hh`).
- `src/core_m33/usb/usb_host_manager.hh`: MP2's version of MP1's
  `UsbHostManager`, found first in the M33's include path (see Host mode, below).

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
- The DWC3 HAL sends a control transfer's data stage as one transfer and reports
  it once, when the host moves to the status stage. MP1's USB device library
  expects one report per 64-byte packet, so the M33 builds it with
  `USBD_AVOID_PACKET_SPLIT_MPS` (without it, enumeration stops at the
  configuration descriptor). In this mode, a data stage that's a multiple of 64
  bytes and shorter than the host asked for doesn't end with a zero-length
  packet; nothing has needed one yet.
- It runs at high speed on the test carrier (verified), though the
  stm32mp2-baremetal `usb-drd` example had to use full speed there.
- The test carrier's USB-C jack had D+/D- swapped (the devboard's swap jumpers
  are after the split to the carrier). With the pair swapped, the host sees a
  low-speed device and resets it over and over.
- The M33 prints faults (`src/core_m33/fault_handlers.cc`) instead of hanging
  silently.

- **The console**, as on MP1: once the M33 is running, each core (A35 core 0, A35 core 1, M33)
  writes its console output to its `ConcurrentBuffer` in shared memory
  (`console/console_buffer_writer.hh`, `SharedIndex::console_buffers`). The M33 sends them to the
  UART (`src/core_m33/console_drain.hh`, which adds the `\r`s), or, while a computer is connected
  to the CDC console, MP1's `UsbSerialDevice` sends them there, and takes console commands. The
  A35 still reads the UART's RX (GUI navigation keys). M33 faults go back to direct UART writes.
- **The developer drive**, as on MP1: the A35 runs MP1's `DevDriveService` in its main loop (MP1
  runs it on core 1), and the M33 serves the drive in the composite device. Its 16MB comes from the
  top of the A35's heap region while Developer Mode is on (`src/core_a35/no_plugins.cc`,
  `system/sbrk_ca35.cc`), opened to the M33 in RISAF4 (region 12); the M33 doesn't cache the A35's
  heap (MPU regions 3 and 4). Installing a `.mm2plugin` and playing a `.yml` patch both work.
- **Host mode**: the DWC3 is an xHCI host, and ST's HAL has no host driver for it. `lib/xhci` is
  U-Boot's xHCI driver (GPL-2.0+) as ported in stm32mp2-baremetal, including its hub support, plus
  non-blocking bulk/interrupt transfers; see its README. It enumerates the devices (also behind
  hubs). MP1's class drivers (`MidiHost`, `MSCHost`) run on ST's USB host library as on MP1, with
  one library handle per driver: `src/core_m33/usb/usb_host_manager.hh` attaches a handle to an
  enumerated device the driver supports, and `usbh_conf.cc` (the `USBH_LL_*` functions) runs the
  library's transfers on `lib/xhci`. So a MIDI device and a USB drive can be connected at once,
  through a hub (but not two of either). The host is polled from the main loop, outside the I2C
  lock (`UsbHostManager::run()`). (stm32mp2-baremetal's device side is U-Boot's DWC3 gadget
  driver, GPL-2.0 only, which is why device mode uses ST's HAL instead.)

## Memory and the two A35 cores

- **The memory map** is in `system/linker/memory_mp2.ld` (MP1's is `memory.ld`): the one place
  MP2's addresses are set. Both cores' linker scripts include it, and `src/mp2-stubs/ld.h` brings
  it into C and C++ (as link-time values, so not usable in `constexpr`: checks on the addresses
  are `ASSERT`s in `memory_mp2.ld`).
- **DDR**: the devboard has 2GB (0x80000000-0xFFFFFFFF), but TF-A opens only 0x80000000-0x9FFFFFFF
  to secure masters in the DDR firewall (RISAF4). The A35 image, its RAM, the framebuffers, the
  M33's memory and the shared memory are in there. Accesses outside the regions opened in RISAF4 are silently
  blocked (reads return 0).
- **The A35's heap** is 1GB of DDR of its own, `_A35_HEAP` (0xA0000000-0xDFFFFFFF), which
  `system/sbrk_ca35.cc` opens to the A35 in RISAF4 (region 9) on the first allocation. It ends
  below 0xE0000000 because that's the M33's private peripheral bus, and the M33 reads and writes the
  top of the heap for the developer drive. If RISAF4 is locked, the heap is the rest of the A35's
  RAM instead (about 90MB, too little for big plugins), and the A35 says so on the console at boot.
- **Locks**: the toolchain's newlib has retargetable locks that do nothing. `system/lock_ca35.cc`
  is MP1's `system/lock.cc`, ported: spin locks owned by a process (a core's main loop, or one of
  its interrupts: `system/reent_ca35.cc`). Taking a lock disables the interrupts on the same core
  that take locks and could preempt the owner (so far, core 1's ReadPatchGuiElements SGI). Audio
  interrupts are never disabled, so as on MP1, audio code must not take locks (no malloc or stdio).
  As on MP1, FILEs have no locks.
- **Per-process state** (`system/reent_ca35.cc`): `errno`, and the C++ exception globals (the
  caught exceptions and the uncaught count). newlib's other state (`_impure_ptr`, stdio) is shared
  by both cores, and is protected by the locks.
- **Plugins** import the lock functions and the exception globals from the firmware (the SDK's
  `cmake/make_plugin_libc_mp2.cmake` removes the toolchain's from the plugin's libc). Each plugin
  keeps its own `_impure_ptr` and static locks, which the AArch64 toolchain's libc can't import.

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
- `system/linker/memory_mp2.ld`, `system/linker/stm32mp2xx_*.ld`, `system/mmu_ca35.cc`
- `system/sbrk_ca35.cc`: the A35's heap; `system/sbrk_mp2.cc`: the M33's. Temporary, until MP2 uses
  MP1's allocation (`system/sbrk.cc`)
- `system/lock_ca35.cc`, `system/reent_ca35.cc`: newlib's locks, and per-process runtime state
- `system/eh_frame_ca35.cc`: registers the unwind tables for C++ exceptions
  (the A35 links without `crtbegin.o`)
- `lib/cmsis-device/stm32mp257d/`: the patched MP2 CMSIS device files
- `lib/stm32-hal/stm32mp2/`: ST HAL. Note that ST's `POSITION_VAL` is broken on
  64-bit and the A35 device headers are not in the Cube release.

Shared sources are in `firmware/src/shared_sources.cmake`.
