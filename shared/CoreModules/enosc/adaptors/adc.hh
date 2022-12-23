#pragma once
#include "../easiglib/dsp.hh"

enum AdcInput {
	POT_WARP,
	POT_DETUNE,
	POT_MOD,
	POT_ROOT,
	POT_SCALE,
	POT_PITCH,
	POT_SPREAD,
	POT_BALANCE,
	POT_TWIST,
	CV_SPREAD,
	CV_WARP,
	CV_TWIST,
	CV_BALANCE,
	CV_SCALE,
	CV_MOD,
	ADC_INPUT_MAX
};

class Adc : Nocopy {
	static inline u0_16 values[ADC_INPUT_MAX];

public:
	Adc() {
	}
	// void Start() {
	// }
	// void Wait() {
	// }
	void set(AdcInput i, u0_16 v) {
		values[i] = v;
	}

	u0_16 get(AdcInput i) {
		return values[i];
	}
};
