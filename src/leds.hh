#pragma once
#include "colors.hh"
#include "pin.hh"
#include "rgbled.hh"
#include "stm32f7xx.h"
#include "tim_pwm.hh"

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
		PinL<GPIO::C, 9> freq1_red_pin{PinMode::Alt, LL_GPIO_AF_3};
		PinL<GPIO::C, 8> freq1_green_pin{PinMode::Alt, LL_GPIO_AF_3};
		PinL<GPIO::B, 3> freq1_blue_pin{PinMode::Alt, LL_GPIO_AF_1};
		PinL<GPIO::A, 11> res1_red_pin{PinMode::Alt, LL_GPIO_AF_1};
		PinL<GPIO::A, 10> res1_green_pin{PinMode::Alt, LL_GPIO_AF_1};
		PinL<GPIO::B, 5> res1_blue_pin{PinMode::Alt, LL_GPIO_AF_2};
		PinL<GPIO::A, 6> freq2_blue_pin{PinMode::Alt, LL_GPIO_AF_2};
		PinL<GPIO::A, 7> freq2_green_pin{PinMode::Alt, LL_GPIO_AF_3};
		PinL<GPIO::B, 0> res2_green_pin{PinMode::Alt, LL_GPIO_AF_2};
		PinL<GPIO::B, 1> res2_blue_pin{PinMode::Alt, LL_GPIO_AF_2};
		PinL<GPIO::A, 2> mode1_red_pin{PinMode::Alt, LL_GPIO_AF_1};
		PinL<GPIO::A, 3> mode1_blue_pin{PinMode::Alt, LL_GPIO_AF_1};
		PinL<GPIO::A, 0> mode2_red_pin{PinMode::Alt, LL_GPIO_AF_1};
		PinL<GPIO::A, 1> mode2_blue_pin{PinMode::Alt, LL_GPIO_AF_2};
		PinL<GPIO::B, 8> mode3_red_pin{PinMode::Alt, LL_GPIO_AF_2};
		PinL<GPIO::B, 9> mode3_blue_pin{PinMode::Alt, LL_GPIO_AF_2};
		PinL<GPIO::B, 6> mode4_red_pin{PinMode::Alt, LL_GPIO_AF_2};
		PinL<GPIO::B, 7> mode4_blue_pin{PinMode::Alt, LL_GPIO_AF_2};
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

