#pragma once
#include <algorithm>
#include <cstdint>

namespace SamplerKit
{

namespace TuningCalcs
{
//
// Applies tracking comp for a bi-polar adc
// Assumes 2048 is the center value
// TODO: use floats for more accuracy
inline uint32_t apply_tracking_compensation(int32_t cv_adcval, float cal_amt) {
	float float_val;

	if (cv_adcval > 2048) {
		cv_adcval -= 2048;
		float_val = (float)cv_adcval * cal_amt;

		// round float_val to nearest integer
		cv_adcval = (uint32_t)float_val;
		if ((float_val - cv_adcval) >= 0.5f)
			cv_adcval++;

		cv_adcval += 2048;
	} else {
		cv_adcval = 2048 - cv_adcval;
		float_val = (float)cv_adcval * cal_amt;

		// round float_val to nearest integer
		cv_adcval = (uint32_t)float_val;
		if ((float_val - cv_adcval) >= 0.5f)
			cv_adcval++;

		cv_adcval = 2048 - cv_adcval;
	}
	return std::clamp<int32_t>(cv_adcval, 0, 4095);
}

//
// Returns a semitone-quantized tuning amount, given an ADC value
//
inline float quantized_semitone_voct(uint32_t adcval) {
	constexpr float TWELFTH_ROOT_TWO = 1.059463094f;
	constexpr float SEMITONE_ADC_WIDTH = 34.0f;
	constexpr float OCTAVE_ADC_WIDTH = SEMITONE_ADC_WIDTH * 12.f;

	// every 405 adc values ocs an octave
	// 2048-(405*oct) ---> 2^oct, oct: 0..5 ---> 1..32
	// 2048+(405*oct) ---> 1/(2^oct), oct: 0..5 --> 1..1/32

	if (adcval == 2048)
		return (1.0);

	// First, set oct_mult
	// oct_mult should be 32, 16, 8, 4, 2, 1, 0.5, 0.25, 0.125, 0.0625, 0.03125
	// to indicate the root note of the octave we're in
	int32_t root_adc;
	float octave_mult = 32.0;
	for (int oct = 5; oct >= -5; oct--) {
		root_adc = 2048 - (OCTAVE_ADC_WIDTH * oct);
		if ((int32_t)adcval <= root_adc)
			break;
		octave_mult = octave_mult / 2;
	}

	int32_t root_adc_midpt = root_adc - (SEMITONE_ADC_WIDTH / 2.f);
	float semitone_mult = 1.0;
	for (int semitone = 0; semitone < 12; semitone++) {
		if ((int32_t)adcval > (root_adc_midpt - (int32_t)(SEMITONE_ADC_WIDTH * (float)semitone)))
			break; // exit for loop
		semitone_mult *= TWELFTH_ROOT_TWO;
	}

	return (octave_mult * semitone_mult);
}

} // namespace TuningCalcs
} // namespace SamplerKit
