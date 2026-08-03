#pragma once
#include "usb/usb_connection_status_block.hh"

namespace MetaModule
{

// A7-side reader for the cross-core USB connection status. The GUI core points
// this at SharedMemoryS::ptrs.usb_connection_status once at startup; it stays
// null in builds with no M4 USB stack (e.g. the simulator), so readers get a
// default (None / empty) snapshot. This keeps the GUI and plugin SDK decoupled
// from the shared-memory wiring and keeps the simulator build clean.
inline UsbConnectionStatusBlock const *usb_status_block = nullptr;

inline UsbConnectionStatus get_usb_connection_status_snapshot() {
	return usb_status_block ? usb_status_block->read_status() : UsbConnectionStatus{};
}

inline UsbDeviceName get_usb_device_name_snapshot() {
	return usb_status_block ? usb_status_block->read_name() : UsbDeviceName{};
}

inline UsbDeviceState get_usb_device_state_snapshot() {
	return usb_status_block ? usb_status_block->read() : UsbDeviceState{};
}

inline UsbMidiJackInfo get_usb_midi_in_jack_snapshot(unsigned num) {
	return usb_status_block ? usb_status_block->read_in_jack(num) : UsbMidiJackInfo{};
}

inline UsbMidiJackInfo get_usb_midi_out_jack_snapshot(unsigned num) {
	return usb_status_block ? usb_status_block->read_out_jack(num) : UsbMidiJackInfo{};
}

inline UsbMidiCableInfo get_usb_midi_rx_cable_snapshot(unsigned cable_num) {
	return usb_status_block ? usb_status_block->read_rx_cable(cable_num) : UsbMidiCableInfo{};
}

inline UsbMidiCableInfo get_usb_midi_tx_cable_snapshot(unsigned cable_num) {
	return usb_status_block ? usb_status_block->read_tx_cable(cable_num) : UsbMidiCableInfo{};
}

} // namespace MetaModule
