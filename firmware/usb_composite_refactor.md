# USB Composite Host Refactor

## Problem
The Rotocontrol is a USB composite device with both MIDI and CDC interfaces. The old implementation stopped the USB host stack, switched `PreferredClass` between MIDI/CDC, and restarted — causing `HAL_Delay()` calls, MIDI interruptions, and fragile timing. Root cause: STM32 USB host library only supports a single `pActiveClass`.

## Solution
A single composite class driver (`USBH_ClassTypeDef`) registered as "MIDI" with `AudioClassCode` (0x01). From the USB core's perspective there's one active class, but internally it manages both MIDI and CDC protocols.

## Implementation Details

### Step 1: _Direct functions in usbh_midi
Added handle-based variants that accept `MidiStreamingHandle*` directly:
- `USBH_MIDI_InterfaceInit_Direct`, `USBH_MIDI_InterfaceDeInit_Direct`
- `USBH_MIDI_Transmit_Direct`, `USBH_MIDI_Receive_Direct`
- `MIDI_ProcessTransmission_Direct`, `MIDI_ProcessReception_Direct`

Original functions became thin wrappers that extract handle from `pActiveClass->pData`.

### Step 2: MidiCdcCompositeHost
- `MidiCdcCompositeHandle` struct: contains `MidiStreamingHandle midi`, `CDC_HandleTypeDef cdc`, `bool cdc_available`
- Composite class driver: `InterfaceInit` always inits MIDI, then opportunistically discovers CDC via `USBH_FindInterface`
- `Process`: runs both MIDI and CDC state machines
- `ClassRequest`: calls `HOST_USER_CLASS_ACTIVE` immediately (skips GetLineCoding)
- CDC TX/RX callbacks go through `MidiCdcCompositeHost::instance` static pointer
- Has `DoubleBufferStream` for both MIDI TX (64 bytes) and CDC TX (256 bytes)
- Provides matching method names to old `MidiHost` for drop-in replacement

### Step 3: RotocontrolHost
Simple wrapper that configures CDC: 115200 8N1, DTR/RTS, starts receive.

### Step 4: UsbHostManager simplification
Removed: `PreferredClass`, `MidiHost`, `CDCHost`, class-switching in `process()`, `transmit_cdc_buffer()` with stop/start cycling, `inflight_cdc_tx_count`, `process_iteration_count`, `ActiveInterface`, `HubPortInfo`, CDC callback overrides.

Added: `MidiCdcCompositeHost composite_host`, `RotocontrolHost roto_host`.

`process()` now just: `USBH_Process()` + `poll_and_transmit_cdc_buffer()` (simple buffer read + `cdc_transmit()`).

### Step 5: Wiring updates
- `Controls` uses `MidiCdcCompositeHost&` (same method names: `is_connected()`, `transmit()`, `set_rx_callback()`, `receive()`)
- `UsbManager::get_midi_host()` returns `MidiCdcCompositeHost&`

### Step 6: CDC library fix
Reverted hardcoded interface numbers in `usbh_cdc.c` back to using `USBH_FindInterface()`.

## Testing Checklist
- [ ] MIDI-only device: standard USB MIDI keyboard works
- [ ] Rotocontrol: MIDI connects immediately (no delay), CDC detected, 115200 8N1 configured, commands transmit without MIDI interruption
- [ ] MSC (USB drive) detection still works
- [ ] USB device mode still works
- [ ] No HAL_Delay in hot path
