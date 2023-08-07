#pragma once
#include <cstdint>

namespace mdrivlib
{

struct SMPControl {

	template<uint32_t channel>
	static void notify() {
	}

	static void notify(uint32_t channel) {
	}

	template<uint32_t reg_num = 0>
	static void write(uint32_t value) {
	}

	static void write(uint32_t reg_num, uint32_t value) {
	}

	template<uint32_t reg_num = 0>
	static uint32_t read() {
		return 0;
	}

	static uint32_t read(uint32_t reg_num) {
		return 0;
	}
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
