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

	static inline JackSense freq_sense[2] = {{GPIO::G, 4}, {GPIO::G, 3}}; // chan A_VOCT, B_VOCT
	static inline JackSense res_sense[2] = {{GPIO::G, 2}, {GPIO::E, 9}};  // chan C_VOCT, D_VOCT
	static inline JackSense in_sense[2] = {{GPIO::F, 12}, {GPIO::F, 11}}; // chan E_VOCT, F_VOCT
	static inline JackSense out_sense[2] = {{GPIO::F, 1}, {GPIO::F, 1}};  // Transpose CV for both

	static inline RotaryEncoder<RotaryHalfStep> rotary[2] = {
		{GPIO::D, 10, GPIO::C, 6}, // Browse, LFO Shape
		{GPIO::B, 5, GPIO::B, 6}};
	static inline DebouncedSwitch rotary_button[2] = {{GPIO::D, 9}, {GPIO::B, 4}};
	static inline DebouncedSwitch mode_button[2] = {{GPIO::C, 9}, {GPIO::D, 0}}; // Chan A, Chan B

	Controls();
	void read();
	void begin();

private:
	Timekeeper read_controls_task;
};
