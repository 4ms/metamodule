#pragma once
#include "conf/control_conf.hh"
#include "drivers/analog_in.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/pin.hh"
#include "drivers/rotary.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"

using JackSense = DebouncedSwitch;

struct Controls {
	static inline AnalogIn<AdcPeriphNum::_1, AdcChanNum::_2> freq_cv0 = {GPIO::A, 2};
	static inline AnalogIn<AdcPeriphNum::_1, AdcChanNum::_3> res_cv0 = {GPIO::A, 3};
	static inline AnalogIn<AdcPeriphNum::_1, AdcChanNum::_0> freq_cv1 = {GPIO::A, 0};
	static inline AnalogIn<AdcPeriphNum::_1, AdcChanNum::_1> res_cv1 = {GPIO::A, 1};

	static inline JackSense freq_sense[2] = {{GPIO::C, 4, PinPolarity::Normal}, {GPIO::B, 1, PinPolarity::Normal}};
	static inline JackSense res_sense[2] = {{GPIO::C, 5, PinPolarity::Normal}, {GPIO::B, 0, PinPolarity::Normal}};
	static inline JackSense in_sense[2] = {{GPIO::G, 12, PinPolarity::Normal}, {GPIO::G, 11, PinPolarity::Normal}};
	static inline JackSense out_sense[2] = {{GPIO::D, 7, PinPolarity::Normal}, {GPIO::G, 10, PinPolarity::Normal}};

	static inline RotaryEncoder<RotaryFullStep> rotary[2] = {{GPIO::A, 7, GPIO::A, 6}, {GPIO::C, 7, GPIO::C, 6}};
	static inline DebouncedSwitch rotary_button[2] = {{GPIO::A, 5}, {GPIO::B, 9}};
	static inline DebouncedSwitch mode_button[2] = {{GPIO::C, 14}, {GPIO::C, 15}};

	Controls();
	void read();
	void start();

private:
	Timekeeper read_controls_task;
};
