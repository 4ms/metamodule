# MetaModule Firmware - Session Memory

## Project Overview
- STM32MP1 dual-core (A7 + M4) embedded firmware for the MetaModule
- Branch: `dg/rotocontrol6`
- Build: `make` (cmake preset "full", builds both M4 and A7)

## USB Composite Host Refactor (Completed 2026-03-04)
See [usb_composite_refactor.md](usb_composite_refactor.md) for full details.

**Status**: All code changes complete. Build passes. Needs hardware testing.

### What was done
Replaced stop/start class-switching USB host with a single composite class driver that handles MIDI+CDC simultaneously.

### Key new files
- `src/usb/midi_cdc_composite_host.hh/.cc` — composite USBH_ClassTypeDef
- `src/usb/rotocontrol_host.hh` — Rotocontrol CDC config wrapper

### Key modified files
- `src/usb/usbh_midi.cc/.hh` — added `_Direct` handle-based variants
- `src/usb/usb_host_manager.hh` — removed class-switching, uses composite host
- `src/usb/usb_manager.hh` — returns `MidiCdcCompositeHost&`
- `src/core_m4/controls.hh/.cc` — uses `MidiCdcCompositeHost&` instead of `MidiHost&`
- `lib/stm32-usb-host-lib/Class/CDC/Src/usbh_cdc.c` — reverted hardcoded interface numbers
- `src/core_m4/CMakeLists.txt` — added new .cc file

## Architecture Notes
- USB host runs on M4 core
- A7 writes CDC data to `ConcurrentBuffer` (shared memory), M4 polls and transmits
- `RotoControl` class (A7 side, `src/core_a7/rotocontrol.hh`) builds binary command packets
- `Controls` class (M4) handles MIDI RX/TX, knobs, buttons, gates
- `UsbManager` wraps host+device, handles FUSB302 DRP role switching
