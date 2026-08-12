#pragma once
#include <atomic>
#include <cstdint>
#include <span>

namespace MetaModule
{

// Handoff of the developer-mode USB drive between the cores.
//
// The A7 owns the memory (it claims it from the plugin arena and puts a
// filesystem on it); the M4 owns the USB side (it serves the sectors to a host
// as an MSC interface). Neither touches the drive while the other has it:
//
//   A7: allocate -> format -> flush caches -> publish base/size -> serve = true
//   M4: sees serve, includes MSC in the composite at the next enumeration
//   host: writes files, ejects
//   M4: sets ejected, reports medium-not-present to the host
//   A7: sees ejected, invalidates caches, mounts, installs plugins, remounts
//
// Small enough that each field is a single aligned word, so plain relaxed
// atomics are enough -- but `serve` must be stored last (release) because it is
// what tells the M4 that base/size are valid.
struct DevDriveBlock {
	// A7 -> M4
	std::atomic<uint32_t> base{0}; // start of the drive memory, 0 if none
	std::atomic<uint32_t> size{0}; // bytes
	std::atomic<uint32_t> serve{0};	 // include the MSC interface
	std::atomic<uint32_t> present{0}; // medium is present (0 after an eject, until the A7 is done)

	// M4 -> A7
	std::atomic<uint32_t> ejected{0};  // host ejected; the A7 should scan the drive
	std::atomic<uint32_t> host_wrote{0}; // host has written at least one sector this session

	void publish(uint32_t drive_base, uint32_t drive_size) {
		base.store(drive_base, std::memory_order_relaxed);
		size.store(drive_size, std::memory_order_relaxed);
		ejected.store(0, std::memory_order_relaxed);
		host_wrote.store(0, std::memory_order_relaxed);
		present.store(1, std::memory_order_relaxed);
		serve.store(1, std::memory_order_release); // last: validates the rest
	}

	void withdraw() {
		serve.store(0, std::memory_order_release);
		present.store(0, std::memory_order_relaxed);
		base.store(0, std::memory_order_relaxed);
		size.store(0, std::memory_order_relaxed);
	}

	bool is_served() const {
		return serve.load(std::memory_order_acquire) != 0;
	}

	bool is_present() const {
		return present.load(std::memory_order_relaxed) != 0;
	}

	// The drive memory, or an empty span if the A7 has not published one. Only
	// valid to call after is_served().
	std::span<uint8_t> memory() const {
		auto b = base.load(std::memory_order_relaxed);
		auto n = size.load(std::memory_order_relaxed);
		if (b == 0 || n == 0)
			return {};
		return {reinterpret_cast<uint8_t *>(b), n};
	}
};

} // namespace MetaModule
