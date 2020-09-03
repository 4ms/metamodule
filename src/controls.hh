#pragma once
#include "analog_in.hh"
#include "debounced_switch.hh"
#include "filter.hh"
#include "pin.hh"
#include "stm32f7xx_ll_adc.h"
#include "stm32f7xx_ll_gpio.h"
#include "touch.hh"
#include <array>
#include <stm32f7xx.h>

using JackSense = DebouncedSwitch;

//Controls class
//Reads raw user input hardware,
//Performs fast conditioning (oversampling/debouncing),
//and stores conditioned values
struct Controls {
	static inline AnalogIn<ADC_1, AdcChanNum::_10> freq1_cv{GPIO::C, 0};
	static inline AnalogIn<ADC_1, AdcChanNum::_11> res1_cv{GPIO::C, 1};
	static inline AnalogIn<ADC_1, AdcChanNum::_12> freq2_cv{GPIO::C, 2};
	static inline AnalogIn<ADC_1, AdcChanNum::_13> res2_cv{GPIO::C, 3};

	static inline JackSense freq2_sense{GPIO::C, 14};
	static inline JackSense res2_sense{GPIO::C, 4};
	static inline JackSense in1_sense{GPIO::C, 13};
	static inline JackSense in2_sense{GPIO::C, 15};

	static inline TouchCtl pads;
	static inline int32_t rotary_turn[2];
	static inline DebouncedSwitch rotary_button[2] = {
		{GPIO::D, 2},
		{GPIO::B, 14}};

	Controls();
	static void read();

	void begin();
};
