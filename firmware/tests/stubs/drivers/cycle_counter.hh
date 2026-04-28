#pragma once
#include <cstdint>

namespace mdrivlib
{
class CycleCounter {
public:
	CycleCounter() {
	}

	void init() {
	}

	void start_simple_measurement() {
	}

	uint32_t stop_simple_measurement() {
		return 1;
	}

	void start_measurement() {
	}

	void end_measurement() {
	}

	uint32_t get_last_measurement_raw() {
		return 1;
	}

	uint32_t get_last_period_raw() {
		return 2;
	}

	float get_last_measurement_load_float() {
		return 0.5f;
	}

	uint32_t get_last_measurement_load_percent() {
		return 50;
	}
};
} // namespace mdrivlib
