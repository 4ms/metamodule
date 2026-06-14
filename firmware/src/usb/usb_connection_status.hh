#pragma once
#include "usb/usb_connection.hh"
#include "util/static_string.hh"
#include <atomic>
#include <cstdint>

namespace MetaModule
{

// Detailed USB connection snapshot, produced by the M4 USB stack and consumed by
// the A7 GUI and the plugin SDK.
//
// The device fields (vid/pid/manufacturer/product/jacks) are populated only when
// the MetaModule is acting as a USB *host* with a peripheral attached. In device
// mode (MetaModule plugged into a computer) there is no peripheral descriptor to
// report, so those fields stay zero/empty and only `connection` is meaningful.
//
// POD by construction (StaticString is a fixed char buffer), so it is safe to
// place in non-cacheable shared memory and to return by value across the plugin
// ABI boundary. Keep the layout in sync with the SDK mirror in
// metamodule-plugin-sdk/core-interface/system/usb.hh (enforced by static_asserts
// in coreproc_plugin/internal_interface/plugin_app_interface.cc).
struct UsbConnectionStatus {
	UsbConnection connection = UsbConnection::None;
	uint16_t vid = 0;
	uint16_t pid = 0;
	uint8_t num_midi_in_jacks = 0;
	uint8_t num_midi_out_jacks = 0;
	StaticString<63> manufacturer;
	StaticString<63> product;
};

// Seqlock for lock-free single-writer (M4) / multi-reader (A7 GUI + SDK) publish
// of UsbConnectionStatus across cores. Writes happen only on connect/disconnect
// events (rare and human-paced), so readers essentially never retry. `seq` is
// even when the data is stable and odd while a write is in progress; the fences
// keep the field writes/reads ordered with respect to the seq updates.
struct UsbConnectionStatusBlock {
	volatile uint32_t seq = 0;
	UsbConnectionStatus data;

	// Single writer: M4 main loop.
	void publish(UsbConnectionStatus const &src) {
		seq = seq + 1; // -> odd: write in progress
		std::atomic_thread_fence(std::memory_order_release);
		data = src;
		std::atomic_thread_fence(std::memory_order_release);
		seq = seq + 1; // -> even: complete
	}

	// Any reader (A7). Returns a consistent snapshot; bounded retries so a
	// pathological writer can never spin the reader forever.
	UsbConnectionStatus read() const {
		UsbConnectionStatus out{};
		for (int tries = 0; tries < 8; tries++) {
			uint32_t s1 = seq;
			std::atomic_thread_fence(std::memory_order_acquire);
			if (s1 & 1u)
				continue; // writer mid-update
			out = data;
			std::atomic_thread_fence(std::memory_order_acquire);
			uint32_t s2 = seq;
			if (s1 == s2)
				break; // snapshot was consistent
		}
		return out;
	}
};

} // namespace MetaModule
