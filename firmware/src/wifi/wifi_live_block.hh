#pragma once
#include "conf/patch_conf.hh"
#include "patch/module_type_slug.hh"
#include <array>
#include <atomic>
#include <cstdint>
#include <optional>

namespace MetaModule
{

// What the Wi-Fi interface reports about the playing patch
struct WifiLiveData {
	PatchName patch_name{""};
	bool playing = false;
	bool modules_valid = false; // per-module loads are being measured
	uint16_t overhead = 0;		// tenths of a percent
	uint16_t num_modules = 0;
	std::array<uint16_t, MAX_MODULES_IN_PATCH> modules{}; // tenths of a percent, index = module id in patch
};

// Shared between A7 (GUI) and M4 (Wi-Fi). Each field has a single writer:
// - A7 publishes the live data (seqlock, like UsbConnectionStatusBlock)
// - M4 counts requests for per-module measurements
struct WifiLiveBlock {
	volatile uint32_t data_seq = 0;
	WifiLiveData data;

	volatile uint32_t detail_request_count = 0;

	// The block lives in a NOLOAD section, and DDR survives a warm reboot: zero it before use
	void reset() {
		data_seq = 0;
		data = WifiLiveData{};
		detail_request_count = 0;
	}

	// A7 GUI
	void publish(WifiLiveData const &src) {
		data_seq = data_seq + 1; // -> odd: write in progress
		std::atomic_thread_fence(std::memory_order_release);
		data = src;
		std::atomic_thread_fence(std::memory_order_release);
		data_seq = data_seq + 1; // -> even: complete
	}

	// M4. nullopt if no consistent snapshot could be read
	std::optional<WifiLiveData> read() const {
		for (int tries = 0; tries < 8; tries++) {
			uint32_t s1 = data_seq;
			std::atomic_thread_fence(std::memory_order_acquire);
			if (s1 & 1u)
				continue; // writer mid-update

			WifiLiveData out = data;
			std::atomic_thread_fence(std::memory_order_acquire);
			if (s1 == data_seq)
				return out;
		}
		return std::nullopt;
	}

	// M4
	void request_detail() {
		detail_request_count = detail_request_count + 1;
	}

	// A7 GUI
	uint32_t detail_requests() const {
		return detail_request_count;
	}
};

} // namespace MetaModule
