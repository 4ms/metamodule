#pragma once
#include <atomic>
#include <cstdint>
#include <span>

namespace MetaModule
{

// Commands the console (M4) asks the aux core to carry out. Installing means
// taking the drive back from the host for the duration, so it cannot be done
// on the M4 side.
enum class DevDriveCommand : uint32_t {
	None = 0,
	Install, // scan the drive, install what is on it, then give it back
	Eject,	 // remove the medium, as if the host had ejected it
	Mount,	 // put the medium back
	Status,  // report to the console
};

// Handoff of the developer-mode USB drive between the cores.
//
// The A7 owns the drive memory and puts the filesystem there.
// The M4 owns the USB side and serves it as a MSC device
//
//   A7: allocate -> format -> flush caches -> publish base/size -> serve = true
//   M4: sees serve, includes MSC in the composite at the next enumeration
//   host: writes files, ejects
//   M4: sets ejected, reports medium-not-present to the host
//   A7: sees ejected, invalidates caches, mounts, installs plugins, remounts
struct DevDriveBlock {
	// A7 -> M4
	std::atomic<uint32_t> base{0};	  // start of the drive memory, 0 if none
	std::atomic<uint32_t> size{0};	  // bytes
	std::atomic<uint32_t> serve{0};	  // include the MSC interface
	std::atomic<uint32_t> present{0}; // medium is present (0 after an eject, until the A7 is done)

	// M4 -> A7 counters with one writer and one reader
	std::atomic<uint32_t> eject_count{0}; // bumped once per host eject
	std::atomic<uint32_t> host_wrote{0};  // host has written at least one sector this session

	// Console commands, M4 -> A7. The command is stored first and the counter
	// last, so a reader that sees a new count also sees the command.
	std::atomic<uint32_t> command{0};
	std::atomic<uint32_t> command_count{0};

	// The block lives in a NOLOAD section, so needs to be manually zeroed
	void reset() {
		base.store(0, std::memory_order_relaxed);
		size.store(0, std::memory_order_relaxed);
		serve.store(0, std::memory_order_relaxed);
		present.store(0, std::memory_order_relaxed);
		eject_count.store(0, std::memory_order_relaxed);
		host_wrote.store(0, std::memory_order_relaxed);
		command.store(0, std::memory_order_relaxed);
		command_count.store(0, std::memory_order_release);
	}

	void note_eject() {
		present.store(0, std::memory_order_relaxed);
		eject_count.store(eject_count.load(std::memory_order_relaxed) + 1, std::memory_order_release);
	}

	// Single writer (the M4's console parser)
	void send_command(DevDriveCommand cmd) {
		command.store(static_cast<uint32_t>(cmd), std::memory_order_relaxed);
		command_count.store(command_count.load(std::memory_order_relaxed) + 1, std::memory_order_release);
	}

	void publish(uint32_t drive_base, uint32_t drive_size) {
		base.store(drive_base, std::memory_order_relaxed);
		size.store(drive_size, std::memory_order_relaxed);
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
