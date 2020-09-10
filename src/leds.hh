#pragma once
#include "colors.hh"
#include "pin.hh"
#include "rgbled.hh"
#include "stm32f7xx.h"
#include "tim_pwm.hh"
#include "defs/led_defs.hh"

class NoPwmLed : public TimPwmChannel {
public:
	NoPwmLed() {}
	void set_output_level(uint32_t val) const {}
};

class DACLed : public TimPwmChannel {
public:
	DACLed(uint8_t dac_chan)
		: dac_chan_(dac_chan)
	{
	}
	void set_output_level(uint32_t val) const {}

private:
	uint8_t dac_chan_;
};

using PwmRgbLed = RgbLed<TimPwmChannel>;

class LedCtl {
public:
	LedCtl()
	{
	}

	//Todo: only update if glowing or fading
	void update()
	{
		freq[0].refresh();
		res[0].refresh();
		freq[1].refresh();
		res[1].refresh();
		mode[0].refresh();
		mode[1].refresh();
		mode[2].refresh();
		mode[3].refresh();
		mode[4].refresh();
	}

public:
	PwmRgbLed freq[2] = {
		{{TIM8, TimChannelNum::_4},
		 {TIM8, TimChannelNum::_3},
		 {TIM2, TimChannelNum::_2}},
		{NoLedElement,
		 {TIM3, TimChannelNum::_1},
		 {TIM8, TimChannelNum::_1N}}};

	PwmRgbLed res[2] = {
		{{TIM1, TimChannelNum::_4},
		 {TIM1, TimChannelNum::_3},
		 {TIM3, TimChannelNum::_2}},

		{NoLedElement,
		 {TIM3, TimChannelNum::_3},
		 {TIM3, TimChannelNum::_4}}};

	PwmRgbLed mode[5]{
		{NoLedElement, //DAC0 PA4
		 NoLedElement,
		 NoLedElement}, //DAC1 PA5

		{{TIM2, TimChannelNum::_3},
		 NoLedElement,
		 {TIM2, TimChannelNum::_4}},

		{{TIM2, TimChannelNum::_1},
		 NoLedElement,
		 {TIM5, TimChannelNum::_2}},

		{{TIM4, TimChannelNum::_3},
		 NoLedElement,
		 {TIM4, TimChannelNum::_4}},

		{{TIM4, TimChannelNum::_1},
		 NoLedElement,
		 {TIM4, TimChannelNum::_2}},
	};

private:
	NoPwmLed NoLedElement;
};

