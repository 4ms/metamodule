#pragma once
#include "colors.hh"
#include "frame_buffer_led.hh"
#include "i2c.hh"
#include "pca9685_led_driver.hh"
#include "pin.hh"
#include "rgbled.hh"
#include "stm32f7xx.h"
#include "tim_pwm.hh"

using PwmRgbLed = RgbLed<TimPwmChannel>;
using NoPwmLed = NoPwmChannel;
using DriverRgbLed = RgbLed<FrameBufferLED>;

class LedCtl {
public:
	LedCtl(I2CPeriph &i2c)
		: led_driver_{i2c}
		, led_frame_buf{led_driver_.get_frame_buffer()}
	{
		led_driver_.start();
	}

	void start_dma_mode()
	{
		led_driver_.start_dma_mode();
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
	uint32_t *const led_frame_buf;
	constexpr int led(int chipnum, int lednum)
	{
		return (chipnum * PCA9685Driver::kNumLedsPerChip) + lednum;
	}
	enum { Chip0 = 0,
		   Chip1 = 1 };

public:
	DriverRgbLed freq[2] = {
		{
			{&led_frame_buf[led(Chip1, 3)]},
			{&led_frame_buf[led(Chip1, 2)]},
			{&led_frame_buf[led(Chip1, 4)]},
		},
		{
			{&led_frame_buf[led(Chip1, 11)]},
			{&led_frame_buf[led(Chip1, 12)]},
			{&led_frame_buf[led(Chip1, 13)]},
		},
	};

	PwmRgbLed res[2] = {
		{{TIM1, TimChannelNum::_4},
		 {TIM1, TimChannelNum::_3},
		 {TIM3, TimChannelNum::_2}},

		{NoLedElement,
		 {TIM3, TimChannelNum::_3},
		 {TIM3, TimChannelNum::_4}}};

	PwmRgbLed mode[5]{
		{NoLedElement,
		 NoLedElement,
		 NoLedElement},

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

