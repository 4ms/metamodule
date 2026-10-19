#pragma once
#include "console/pr_dbg.hh"
#include "drivers/stm32xx.h"
#include <atomic>
#include <cstdint>

namespace MetaModule
{

// Ticks per second of the ARM generic timer (PL1_GetCurrentPhysicalValue(), mdrivlib::CycleCounter):
// 24MHz on MP1's A7, 64MHz on MP2's A35
#if defined(CORE_CA35)
constexpr uint32_t GenericTimerHz = 64'000'000;
#else
constexpr uint32_t GenericTimerHz = 24'000'000;
#endif

struct AudioOverrunHandler {
	void start_retrying() {
		retrying = true;
	}

	bool is_retrying() const {
		return retrying;
	}

	void reset() {
		retrying = false;
	}

	void set_max_retry(uint32_t max_times) {
		max_retries = max_times;
	}

	bool handle() {
		// if we've gone 0.1 sec without overrunning, then consider this a new overrun
		uint64_t tm = PL1_GetCurrentPhysicalValue();
		if (tm - last_overrun < GenericTimerHz / 10) {
			overrun_count++;
		} else {
			last_overrun = tm;
			// pr_dbg("New group of overruns: last group counted up to %u\n", overrun_count);
			overrun_count = 0;
		}

		return (overrun_count < max_retries);
	}

private:
	uint32_t overrun_count = 0;
	uint64_t last_overrun = 0;
	unsigned max_retries = 0;

	// bool retrying = false;
	std::atomic<bool> retrying = false;
};
} // namespace MetaModule
