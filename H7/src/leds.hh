#pragma once
#include "drivers/colors.hh"
#include "drivers/frame_buffer_led.hh"
#include "drivers/i2c.hh"
#include "drivers/led_driver.hh"
#include "drivers/pca9685_led_driver.hh"
#include "drivers/pin.hh"
#include "drivers/rgbled.hh"
#include "drivers/stm32xx.h"

using DriverRgbLed = RgbLed<FrameBufferLED>;

class LedCtl {
public:
	LedCtl(ILedDmaDriver &led_driver)
		: led_driver_{led_driver}
	{}

	void start_it_mode()
	{
		led_driver_.start_it_mode();
	}

	void start_dma_mode()
	{
		led_driver_.start_dma_mode();
	}

	// Todo: only update if glowing or fading
	void update()
	{
		but[0].update_animation();
		but[1].update_animation();
		clockLED.update_animation();
		rotaryLED.update_animation();
	}

	void refresh()
	{
		led_driver_.write_once();
	}

private:
	ILedDmaDriver &led_driver_;

	enum { Chip0 = 0 };

public:
	DriverRgbLed rotaryLED = {
		{led_driver_.get_buf_addr(Chip0, 3)},
		{led_driver_.get_buf_addr(Chip0, 4)},
		{led_driver_.get_buf_addr(Chip0, 5)},
	};

	DriverRgbLed clockLED = {
		{led_driver_.get_buf_addr(Chip0, 9)},
		{led_driver_.get_buf_addr(Chip0, 10)},
		{led_driver_.get_buf_addr(Chip0, 11)},
	};

	DriverRgbLed but[2] = {
		{
			{led_driver_.get_buf_addr(Chip0, 0)},
			{led_driver_.get_buf_addr(Chip0, 1)},
			{led_driver_.get_buf_addr(Chip0, 2)},
		},
		{
			{led_driver_.get_buf_addr(Chip0, 6)},
			{led_driver_.get_buf_addr(Chip0, 7)},
			{led_driver_.get_buf_addr(Chip0, 8)},
		},
	};

private:
	NoFrameBufferLED NoLED;
};

