#pragma once

#include "util/lockfree_fifo_spsc.hh"
#include <cstdint>

class BufferedUSART2 {
public:
	static void init();
	static void deinit();

	// not used:
	// static bool setBaudrate(uint32_t);

	// static void transmit(uint8_t);
	static void transmit_intr(std::span<uint8_t> data);

	static std::optional<uint8_t> receive();

	static bool detectedOverrunSinceLastCall() {
		if (overrunDetected) {
			overrunDetected = false;
			return true;
		}
		return false;
	}

	static bool is_busy();

private:
	static void initPeripheral();

private:
	static LockFreeFifoSpsc<uint8_t, 256> queue;

	static std::atomic_bool overrunDetected;
};
