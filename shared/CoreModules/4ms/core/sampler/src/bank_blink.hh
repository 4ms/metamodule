#pragma once

#include "elements.hh"
#include <cstdint>

inline bool blink_bank(unsigned bank, uint32_t tmr) {

	constexpr uint32_t bitsize = 11;
	constexpr uint32_t max = (1U << bitsize);
	constexpr uint32_t mask = max - 1U;
	constexpr uint32_t off_time = max / 16;
	constexpr uint32_t on_time = max / 8;

	tmr &= mask;
	unsigned threshold = 0;

	// Non-blinking banks:
	if (bank < 10)
		return true;

	// Space blinks out evenly:
	for (unsigned bank_threshold = 10; bank_threshold < SamplerKit::MaxNumBanks; bank_threshold += 10) {
		threshold += off_time;
		if (tmr < threshold && (bank >= bank_threshold))
			return false;

		threshold += on_time;
		if (tmr < threshold && (bank >= bank_threshold))
			return true;
	}
	return true;
}
