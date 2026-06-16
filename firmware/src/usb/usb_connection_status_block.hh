#pragma once
#include "usb/usb_connection.hh"
#include <atomic>
#include <cstdint>

namespace MetaModule
{

// Seqlock for lock-free single-writer (M4) / multi-reader (A7 GUI + SDK) publish
// of UsbConnectionStatus across cores. Writes happen only on connect/disconnect
// events
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

	// Any reader:A7 GUI or modules via the SDK
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
