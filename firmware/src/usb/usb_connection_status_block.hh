#pragma once
#include "usb/usb_connection.hh"
#include <atomic>
#include <cstdint>

namespace MetaModule
{

// Seqlock for lock-free single-writer (M4) / multi-reader (A7 GUI + SDK) publish
// of the USB device state across cores. Writes happen only on connect/disconnect
// events. The seqlock lets a reader copy just the subset it needs and still get
// a tear-free snapshot. Any concurrent write bumps `seq`, which the post-copy
// re-check catches.
struct UsbConnectionStatusBlock {
	volatile uint32_t seq = 0;
	UsbDeviceState data;

	// Single writer: M4 main loop.
	void publish(UsbDeviceState const &src) {
		seq = seq + 1; // -> odd: write in progress
		std::atomic_thread_fence(std::memory_order_release);
		data = src;
		std::atomic_thread_fence(std::memory_order_release);
		seq = seq + 1; // -> even: complete
	}

	// Copy `selector(data)` under the seqlock, retrying until it's consistent.
	template<typename Selector>
	auto read_field(Selector selector) const {
		using Result = decltype(selector(data));
		Result out{};
		for (int tries = 0; tries < 8; tries++) {
			uint32_t s1 = seq;
			std::atomic_thread_fence(std::memory_order_acquire);
			if (s1 & 1u)
				continue; // writer mid-update
			out = selector(data);
			std::atomic_thread_fence(std::memory_order_acquire);
			uint32_t s2 = seq;
			if (s1 == s2)
				break; // snapshot was consistent
		}
		return out;
	}

	// Full state (status + all jacks)
	UsbDeviceState read() const {
		return read_field([](UsbDeviceState const &d) { return d; });
	}

	// Status only
	UsbConnectionStatus read_status() const {
		return read_field([](UsbDeviceState const &d) { return d.status; });
	}

	// A single jack. Out-of-range returns a default (valid == false) entry.
	UsbMidiJackInfo read_in_jack(unsigned num) const {
		if (num >= System::MaxMidiJacks)
			return {};
		return read_field([num](UsbDeviceState const &d) { return d.midi_in_jacks[num]; });
	}

	// A single jack. Out-of-range returns a default (valid == false) entry.
	UsbMidiJackInfo read_out_jack(unsigned num) const {
		if (num >= System::MaxMidiJacks)
			return {};
		return read_field([num](UsbDeviceState const &d) { return d.midi_out_jacks[num]; });
	}
};

} // namespace MetaModule
