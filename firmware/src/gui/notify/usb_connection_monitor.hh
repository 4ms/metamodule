#pragma once
#include "gui/notify/queue.hh"
#include "usb/usb_connection.hh"

namespace MetaModule
{

// Watches the M4-reported USB connection status (carried in MetaParams) and
// posts a notification when a new connection is established. Edge-triggered:
// fires only on a transition, and only into one of the four "connected" states.
//
// `prev` starts at None, so if something is already attached at boot the
// notification fires on the first frame the M4 reports it -- intended, it
// confirms detection.
class UsbConnectionMonitor {
	UsbConnection prev = UsbConnection::None;

public:
	void update(UsbConnection cur, NotificationQueue &notify_queue) {
		if (cur == prev)
			return;
		prev = cur;

		const char *msg = nullptr;
		switch (cur) {
			case UsbConnection::HostMidiDevice:
				msg = "Connected to MIDI Device";
				break;
			case UsbConnection::HostUsbDrive:
				msg = "Connected to USB Drive";
				break;
			case UsbConnection::DeviceMidiHost:
				msg = "Connected to MIDI Host";
				break;
			case UsbConnection::DeviceVideoHost:
				msg = "Connected to USB Video Host";
				break;
			// No notification for None/disconnect, the in-between role states,
			// or the CDC serial console (used for debugging).
			case UsbConnection::None:
			case UsbConnection::HostSearching:
			case UsbConnection::DeviceWaiting:
			case UsbConnection::DeviceConsoleHost:
				break;
		}

		if (msg)
			notify_queue.put({msg, Notification::Priority::Info, 2000});
	}
};

} // namespace MetaModule
