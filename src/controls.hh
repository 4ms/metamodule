#pragma once
#include "analog_in.hh"
#include "debounced_switch.hh"
#include "interrupt.hh"
#include "pin.hh"
#include "rotary.hh"
#include "stm32f7xx.h"
#include "stm32f7xx_ll_adc.h"
#include "stm32f7xx_ll_gpio.h"
#include <array>

using JackSense = DebouncedSwitch;

struct Controls {
	static inline AnalogIn<ADC_1, AdcChanNum::_10> freq_cv[2] = {{GPIO::A, 2}, {GPIO::A, 0}};
	static inline AnalogIn<ADC_1, AdcChanNum::_11> res_cv[2] = {{GPIO::A, 3}, {GPIO::A, 1}};

	static inline JackSense freq_sense[2] = {{GPIO::C, 4}, {GPIO::B, 1}};
	static inline JackSense res_sense[2] = {{GPIO::C, 5}, {GPIO::B, 0}};
	static inline JackSense in_sense[2] = {{GPIO::G, 12}, {GPIO::G, 11}};
	static inline JackSense out_sense[2] = {{GPIO::D, 7}, {GPIO::G, 10}};

	static inline RotaryEncoder<RotaryFullStep> rotary[2] = {{GPIO::A, 7, GPIO::A, 6}, {GPIO::C, 7, GPIO::C, 6}};
	static inline DebouncedSwitch rotary_button[2] = {{GPIO::A, 5}, {GPIO::B, 9}};
	static inline DebouncedSwitch mode_button[2] = {{GPIO::C, 14}, {GPIO::C, 15}};

	Controls();
	static void read();
	void begin();

private:
	void isr();
};
