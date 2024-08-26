#pragma once
#include <cstdint>

namespace SamplerKit
{

inline uint32_t detent_num(uint32_t adc_val) {
	if (adc_val <= 212)
		return 0;
	else if (adc_val <= 625)
		return 1;
	else if (adc_val <= 1131)
		return 2;
	else if (adc_val <= 1562)
		return 3;
	else if (adc_val <= 1995)
		return 4;
	else if (adc_val <= 2475)
		return 5;
	else if (adc_val <= 2825)
		return 6;
	else if (adc_val <= 3355)
		return 7;
	else if (adc_val <= 3840)
		return 8;
	else
		return 9;
}

// const uint16_t detent_tops[10] = {212, 625, 1131, 1562, 1995, 2475, 2825, 3355, 3840, 4095};

inline uint32_t detent_num_antihys(uint32_t adc_val, uint32_t cur_detent) {
	constexpr uint32_t DETENT_MIN_DEPTH = 40;
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
