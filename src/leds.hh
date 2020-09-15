#pragma once
#include "colors.hh"
#include "defs/led_defs.hh"
#include "i2c.hh"
#include "pca9685_led_driver.hh"
#include "pin.hh"
#include "rgbled.hh"
#include "stm32f7xx.h"
#include "tim_pwm.hh"

using PwmRgbLed = RgbLed<TimPwmChannel>;
using NoPwmLed = NoPwmChannel;

class LedCtl {
public:
	LedCtl(I2CPeriph &i2c)
		: led_driver_{i2c, kNumLedDriverChips}
	{
		led_driver_.start();
		led_driver_.start_dma_mode(led_frame_buf, LedDriverDmaDef);
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

private:
	PCA9685Driver led_driver_;
	uint16_t led_frame_buf[kNumLedDriverChips * 16];

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

