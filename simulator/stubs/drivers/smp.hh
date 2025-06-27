#pragma once
#include <array>
#include <cstdint>

namespace mdrivlib
{

struct SMPControl {
	static constexpr uint32_t NumCores = 1;

	template<uint32_t channel>
	static void notify() {
		channel_bitset |= (1 << channel);
	}

	static void notify(uint32_t channel) {
		channel_bitset |= (1 << channel);
	}

	template<uint32_t reg_num = 0>
	static void write(uint32_t value) {
		registers[reg_num % registers.size()] = value;
	}

	static void write(uint32_t reg_num, uint32_t value) {
		registers[reg_num % registers.size()] = value;
	}

	template<uint32_t reg_num = 0>
	static uint32_t read() {
		return registers[reg_num % registers.size()];
	}

	static uint32_t read(uint32_t reg_num) {
		return registers[reg_num % registers.size()];
	}

	static bool is_notified(uint32_t channel) {
		return channel_bitset & (1 << channel);
	}

	static void clear_notification(uint32_t channel) {
		channel_bitset &= ~(1 << channel);
	}

	static inline uint32_t channel_bitset = 0;
	static inline std::array<uint32_t, 32> registers{};
};

struct SMPThread {
	// static void launch(std::function<void()> &&entry) {
	// }

	// Called by the aux core to respond to receiving an SGI3
	static void execute() {
	}

	template<uint32_t command_id>
	static void split_with_command() {
	}

	// Waits until thread completes
	static void join() {
	}

	// Aux Core must call this after processing a custom command
	static void signal_done() {
	}

	// Returns true if thread is completed
	static bool is_running() {
		return false;
	}

	static void init() {
	}
};
} // namespace mdrivlib
