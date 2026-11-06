#pragma once
#include "conf/patch_conf.hh"
#include "patch/module_type_slug.hh"
#include "patch_file/patch_location.hh"
#include <array>
#include <atomic>
#include <cstdint>
#include <optional>

namespace MetaModule
{

// What the Wi-Fi interface reports about the playing patch
struct WifiLiveData {
	PatchName patch_name{""};
	uint32_t fingerprint = 0; // patch_fingerprint() of the playing patch
	bool playing = false;
	bool modules_valid = false; // per-module loads are being measured
	uint16_t overhead = 0;		// tenths of a percent
	uint16_t num_modules = 0;
	std::array<uint16_t, MAX_MODULES_IN_PATCH> modules{}; // tenths of a percent, index = module id in patch
	uint16_t num_module_cores = 0; // 0 if the patch has no load balancing info
	std::array<uint8_t, MAX_MODULES_IN_PATCH> module_cores{}; // core each module runs on
	std::array<uint16_t, 2> core_loads{}; // each core's modules + cables, tenths of a percent
};

// Shared between A7 (GUI) and M4 (Wi-Fi). Each field has a single writer:
// - A7 publishes the live data (seqlock, like UsbConnectionStatusBlock)
// - M4 counts requests for per-module measurements
struct WifiLiveBlock {
	volatile uint32_t data_seq = 0;
	WifiLiveData data;

	volatile uint32_t detail_request_count = 0;

	// M4 -> A7: load and play a patch file (seqlock, single writer: M4)
	volatile uint32_t load_seq = 0;
	uint32_t load_id = 0; // increases with each request
	PatchLocation load_loc{};

	// The block lives in a NOLOAD section, and DDR survives a warm reboot: zero it before use
	void reset() {
		data_seq = 0;
		data = WifiLiveData{};
		detail_request_count = 0;
		load_seq = 0;
		load_id = 0;
		load_loc = PatchLocation{};
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

	// M4
	void request_load(PatchLocation const &loc) {
		load_seq = load_seq + 1;
		std::atomic_thread_fence(std::memory_order_release);
		load_id = load_id + 1;
		load_loc = loc;
		std::atomic_thread_fence(std::memory_order_release);
		load_seq = load_seq + 1;
	}

	// A7 GUI: a request newer than last_handled_id, or nullopt (none, or M4 is mid-write: try again later)
	std::optional<PatchLocation> take_load_request(uint32_t &last_handled_id) const {
		uint32_t s1 = load_seq;
		std::atomic_thread_fence(std::memory_order_acquire);
		if (s1 & 1u)
			return std::nullopt;

		uint32_t id = load_id;
		PatchLocation loc = load_loc;
		std::atomic_thread_fence(std::memory_order_acquire);
		if (s1 != load_seq || id == last_handled_id)
			return std::nullopt;

		last_handled_id = id;
		return loc;
	}
};

// A patch sent over Wi-Fi with "load after save" only needs loading if it's not the
// one playing: the playing patch is reloaded by the file change checker anyway.
inline bool needs_wifi_load(PatchLocation const &requested, std::optional<PatchLocation> const &playing) {
	return !playing || !(*playing == requested);
}

} // namespace MetaModule
