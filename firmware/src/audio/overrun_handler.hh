#pragma once
#include "console/pr_dbg.hh"
#include "drivers/stm32xx.h"
#include <atomic>
#include <cstdint>

namespace MetaModule
{

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

	bool can_retry() const {
		return (overrun_count < max_retries);
	}

	void mark_overrun() {
		// if we've gone a bit of time without overrunning, then consider this a new overrun
		uint64_t tm = PL1_GetCurrentPhysicalValue();
		if (tm - last_overrun < 2'400'000) {
			overrun_count++;
		} else {
			last_overrun = tm;
			// pr_dbg("Reset count from %u\n", overrun_count);
			overrun_count = 0;
		}
	}

private:
	uint32_t overrun_count = 0;
	uint64_t last_overrun = 0;
	unsigned max_retries = 0;

	// bool retrying = false;
	std::atomic<bool> retrying = false;
};
} // namespace MetaModule
