#pragma once
#include "analog_in.hh"
#include "debounced_switch.hh"
#include "pin.hh"
#include "rotary.hh"
#include "stm32xx.h"
#include "timekeeper.hh"
#include <array>

using JackSense = DebouncedSwitch;

struct Controls {
	static inline AnalogIn<ADC_1, AdcChanNum::_11> freq_cv0 = {GPIO::C, 1}; // LFO CV
	static inline AnalogIn<ADC_1, AdcChanNum::_13> res_cv0 = {GPIO::C, 3};	// Depth CV ok
	static inline AnalogIn<ADC_1, AdcChanNum::_10> freq_cv1 = {GPIO::C, 0}; // Lat CV ok
	static inline AnalogIn<ADC_1, AdcChanNum::_15> res_cv1 = {GPIO::C, 5};	// WTSpread CV ok

	static inline JackSense freq_sense[2] = {{GPIO::C, 4}, {GPIO::B, 1}};
	static inline JackSense res_sense[2] = {{GPIO::C, 5}, {GPIO::B, 0}};
	static inline JackSense in_sense[2] = {{GPIO::G, 12}, {GPIO::G, 11}};
	static inline JackSense out_sense[2] = {{GPIO::D, 7}, {GPIO::G, 10}};

	static inline RotaryEncoder<RotaryFullStep> rotary[2] = {{GPIO::A, 7, GPIO::A, 6}, {GPIO::C, 7, GPIO::C, 6}};
	static inline DebouncedSwitch rotary_button[2] = {{GPIO::A, 5}, {GPIO::B, 9}};
	static inline DebouncedSwitch mode_button[2] = {{GPIO::C, 14}, {GPIO::C, 15}};

	Controls();
	void read();
	void begin();

private:
	Timekeeper read_controls_task;
};
