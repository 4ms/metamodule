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
	return usb_status_block ? usb_status_block->read() : UsbConnectionStatus{};
}

} // namespace MetaModule
