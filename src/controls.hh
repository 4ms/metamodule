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
	static inline AnalogIn<ADC_1, AdcChanNum::_10> freq_cv[2] = {{GPIO::C, 0}, {GPIO::C, 2}};
	static inline AnalogIn<ADC_1, AdcChanNum::_11> res_cv[2] = {{GPIO::C, 1}, {GPIO::C, 3}};

	static inline JackSense freq_sense[2] = {{GPIO::C, 14}, {GPIO::C, 14}}; //FixMe: only channel 2 is on p1
	static inline JackSense res_sense[2] = {{GPIO::C, 4}, {GPIO::C, 4}};
	static inline JackSense in_sense[2] = {{GPIO::C, 13}, {GPIO::C, 15}};

	static inline RotaryEncoder<RotaryFullStep> rotary[2] = {{GPIO::C, 12, GPIO::C, 11}, {GPIO::A, 12, GPIO::B, 4}};
	static inline DebouncedSwitch rotary_button[2] = {{GPIO::D, 2}, {GPIO::B, 14}};

	Controls();
	static void read();

	void begin();

	struct UpdateISR : InterruptManager::ISRBase {
		virtual void isr();
	};
	UpdateISR updater;
};
