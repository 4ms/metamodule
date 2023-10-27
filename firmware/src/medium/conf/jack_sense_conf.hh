#pragma once
#include <cstdint>

constexpr inline unsigned jacksense_pin_order[16] = {14, 11, 15, 13, 10, 8, 12, 9, 4, 5, 6, 1, 2, 7, 3, 0};

constexpr inline bool jack_is_patched(uint32_t jack_sense_reading, unsigned panel_jack_idx) {
	return (jack_sense_reading >> jacksense_pin_order[panel_jack_idx]) & 1;
	// return jack_sense_reading & (1 << jacksense_pin_order[panel_jack_idx]);
}
