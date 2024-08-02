#pragma once
#include <cstdint>

namespace SamplerKit
{

inline uint32_t detent_num(uint32_t adc_val) {
	//0..4095 => 0..9
	return adc_val / 409.6f;
}

inline uint32_t detent_num_antihys(uint32_t adc_val, uint32_t cur_detent) {
	constexpr uint32_t DETENT_MIN_DEPTH = 10;
	uint8_t raw_detent;
	int16_t lower_adc_bound, upper_adc_bound;

	raw_detent = detent_num(adc_val);

	if (raw_detent > cur_detent) {
		lower_adc_bound = (int16_t)adc_val - DETENT_MIN_DEPTH;
		if (detent_num(lower_adc_bound) > cur_detent)
			return (raw_detent);
	} else if (cur_detent > raw_detent) {
		upper_adc_bound = (int16_t)adc_val + DETENT_MIN_DEPTH;

		if (detent_num(upper_adc_bound) < cur_detent)
			return (raw_detent);
	}

	return cur_detent;
}

} // namespace SamplerKit
