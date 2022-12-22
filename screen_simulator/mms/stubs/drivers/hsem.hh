#pragma once
#include <cstdint>

namespace mdrivlib
{

enum class HWSemaphoreFlag { LockFailed = 0, LockedOk = 1 };

template<uint32_t SemaphoreID>
struct HWSemaphore {
	HWSemaphore() = delete;

	static HWSemaphoreFlag lock() {
		return HWSemaphoreFlag::LockedOk;
	}

	static HWSemaphoreFlag lock(uint32_t processID) {
		return HWSemaphoreFlag::LockedOk;
	}

	static void unlock() {
	}

	static void unlock(uint32_t processID) {
	}
};

} // namespace mdrivlib
