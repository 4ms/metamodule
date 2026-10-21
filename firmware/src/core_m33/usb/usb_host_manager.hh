#pragma once
#include "drivers/pin.hh"
#include "fat_file_io.hh"
#include "midi_host.hh"
#include "pr_dbg.hh"
#include "usb/usb_connection.hh"

// MP2 stand-in for MP1's src/usb/usb_host_manager.hh (found first in the M33's include path), so
// MP1's UsbManager runs unchanged. The USB3DR's host side is an xHCI controller, which ST's HAL
// doesn't support and which isn't ported yet, so this only sources VBUS: in the host role the
// partner gets power but is never enumerated.
//
// Not ported yet: get_midi_host() and get_msc_fileio() are declared but not defined, so code that
// uses the host's MIDI or USB drive fails to link rather than silently getting nothing.

// UsbManager's interrupt handler names MP1's OTG host handle. There's no host controller driver
// to give interrupts to: the controller only runs as a device for now.
struct HCD_HandleTypeDef {};
inline void HAL_HCD_IRQHandler(HCD_HandleTypeDef *) {
}

class UsbHostManager {
	mdrivlib::Pin src_enable;
	MetaModule::UsbDeviceState connected_device{};

public:
	static inline HCD_HandleTypeDef hhcd;

	UsbHostManager(mdrivlib::PinDef enable_5v)
		: src_enable{enable_5v.gpio, enable_5v.pin, mdrivlib::PinMode::Output} {
		src_enable.low();
	}

	void init() {
	}

	void start(bool source_vbus = true) {
		if (source_vbus) {
			src_enable.high();
			pr_info("USB host: VBUS on (host mode isn't supported yet)\n");
		}
	}

	void stop() {
	}

	void vbus_off() {
		src_enable.low();
		HAL_Delay(250);
	}

	void process() {
	}

	bool is_device_attached() {
		return false;
	}

	uint32_t read_port_status() {
		return 0;
	}

	void print_state_debug() {
	}

	MetaModule::UsbDeviceState const &get_connected_device() const {
		return connected_device;
	}

	uint32_t get_device_info_seq() const {
		return 0;
	}

	MidiHost &get_midi_host();
	FatFileIO &get_msc_fileio();

	bool is_msc_connected() {
		return false;
	}

	bool is_msc_mounted() {
		return false;
	}
};
