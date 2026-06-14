#pragma once
#include <cstdint>

namespace MetaModule
{

// The current USB connection, as determined by the M4 USB stack (UsbManager).
// It folds the OTG data role (host vs device) together with the active class,
// so the GUI can show a single human-readable status line and fire a
// notification when a new connection is established.
//
// Computed on the M4 by UsbManager::get_connection(), carried up to the GUI in
// MetaParams (the same path as midi_connected).
enum class UsbConnection : uint32_t {
	None,			   // Not attached (idle / FUSB302 role polling)
	HostSearching,	   // Host role: powering the port, no device class active yet
	HostMidiDevice,	   // Host role: a USB-MIDI device is attached
	HostUsbDrive,	   // Host role: a USB mass-storage drive is attached
	DeviceWaiting,	   // Device role: not yet enumerated by a host
	DeviceMidiHost,	   // Device role: enumerated as a USB-MIDI device by a host
	DeviceVideoHost,   // Device role: enumerated as a UVC video device by a host
	DeviceConsoleHost, // Device role: enumerated as a CDC serial console by a host
};

} // namespace MetaModule
