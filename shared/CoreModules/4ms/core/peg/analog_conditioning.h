/*
 * analog_conditioning.h
 */

#pragma once

#include <stdint.h>

enum AdcChannels {
	CV_SHAPE,
	CV_DIVMULT,
	POT_SCALE,
	POT_OFFSET,
	POT_SHAPE,
	POT_DIVMULT,

	NUM_ADCS
};

enum AdcCVChannels {
	ADC_CV_SHAPE,
	ADC_CV_DIVMULT,
	NUM_CV_ADCS,
};

enum AdcPotChannels {
	ADC_POT_SCALE,
	ADC_POT_OFFSET,
	ADC_POT_SHAPE,
	ADC_POT_DIVMULT,

	NUM_POT_ADCS
};

enum AnalogPolarity { AP_UNIPOLAR, AP_BIPOLAR };

#define MAX_LPF_SIZE 16

typedef struct AnalogConditioned {
	// uint8_t lpf_size;
	// uint8_t lpf_size_shift;
	// uint8_t lpf_i;
	uint32_t lpf_sum;
	//uint16_t lpf[MAX_LPF_SIZE];

	// uint8_t bracket_size;

	enum AnalogPolarity polarity;

	uint16_t raw_val;
	int16_t lpf_val;
	// uint16_t bracketed_val;

} analog_t;

void condition_analog(void);
void init_analog_conditioning(void);
