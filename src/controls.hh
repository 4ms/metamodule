#pragma once
#include "conf/control_conf.hh"
#include "drivers/analog_in.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/pin.hh"
#include "drivers/rotary.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"
#include "util/filter.hh"

using JackSense = DebouncedSwitch;

struct Controls {
	AnalogIn<AdcPeriphNum::_1, AdcChanNum::_2, Oversampler<16>> cv0 = {GPIO::A, 2};
	AnalogIn<AdcPeriphNum::_1, AdcChanNum::_3, Oversampler<16>> cv1 = {GPIO::A, 3};
	AnalogIn<AdcPeriphNum::_1, AdcChanNum::_0, Oversampler<16>> cv2 = {GPIO::A, 0};
	AnalogIn<AdcPeriphNum::_1, AdcChanNum::_1, Oversampler<16>> cv3 = {GPIO::A, 1};

	std::array<JackSense, 4> cv_sense = {{
		{GPIO::C, 4, PinPolarity::Normal},
		{GPIO::B, 1, PinPolarity::Normal},
		{GPIO::C, 5, PinPolarity::Normal},
		{GPIO::B, 0, PinPolarity::Normal},
	}};
	JackSense in_sense[2] = {{GPIO::G, 12, PinPolarity::Normal}, {GPIO::G, 11, PinPolarity::Normal}};
	JackSense out_sense[2] = {{GPIO::D, 7, PinPolarity::Normal}, {GPIO::G, 10, PinPolarity::Normal}};

	RotaryEncoder<RotaryFullStep> rotary[2] = {{GPIO::A, 7, GPIO::A, 6}, {GPIO::C, 7, GPIO::C, 6}};
	DebouncedSwitch rotary_button[2] = {{GPIO::A, 5}, {GPIO::B, 9}};
	DebouncedSwitch mode_button[2] = {{GPIO::C, 14}, {GPIO::C, 15}};

	Controls();
	void read();
	void start();

private:
	Timekeeper read_controls_task;
	__attribute__((section(".dtcm"))) static inline uint16_t adc_buffer[4];
};
