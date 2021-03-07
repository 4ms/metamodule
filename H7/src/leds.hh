#pragma once
#include "drivers/colors.hh"
#include "drivers/frame_buffer_led.hh"
#include "drivers/i2c.hh"
#include "drivers/led_driver.hh"
#include "drivers/pca9685_led_driver.hh"
#include "drivers/pin.hh"
#include "drivers/rgbled.hh"
#include "drivers/stm32xx.h"
using namespace mdrivlib;

// template<typename LedDriverT>
// class LedController {
// 	LedDriverT &led_driver_;

// public:
// 	LedController(LedDriverT &led_driver)
// 		: led_driver_{led_driver}
// 	{}

// 	void start()
// 	{
// 		led_driver_.start();
// 	}

// 	void start_it_mode()
// 	{
// 		led_driver_.start_it_mode();
// 	}

// 	void start_dma_mode()
// 	{
// 		led_driver_.start_dma_mode();
// 	}

// 	void refresh()
// 	{
// 		led_driver_.write_once(0);
// 	}
// };

// CM7
template<unsigned UpdateRateHz>
class LedFrame {
	enum { Chip0 = 0 };

public:
	LedFrame(uint32_t *frame_buf)
		: rotaryLED  {
			{PCA9685Driver::get_buf_addr(frame_buf, Chip0, 3)},
			{PCA9685Driver::get_buf_addr(frame_buf, Chip0, 4)},
			{PCA9685Driver::get_buf_addr(frame_buf, Chip0, 5)},
		}
		, clockLED  {
			{PCA9685Driver::get_buf_addr(frame_buf, Chip0, 9)},
			{PCA9685Driver::get_buf_addr(frame_buf, Chip0, 10)},
			{PCA9685Driver::get_buf_addr(frame_buf, Chip0, 11)},
		}
		, but {{
				{PCA9685Driver::get_buf_addr(frame_buf, Chip0, 0)},
				{PCA9685Driver::get_buf_addr(frame_buf, Chip0, 1)},
				{PCA9685Driver::get_buf_addr(frame_buf, Chip0, 2)},
			},{
				{PCA9685Driver::get_buf_addr(frame_buf, Chip0, 6)},
				{PCA9685Driver::get_buf_addr(frame_buf, Chip0, 7)},
				{PCA9685Driver::get_buf_addr(frame_buf, Chip0, 8)},
			}}
	{}

	void update()
	{
		but[0].update_animation();
		but[1].update_animation();
		clockLED.update_animation();
		rotaryLED.update_animation();
	}

	RgbLed<FrameBufferLED, UpdateRateHz> clockLED;
	RgbLed<FrameBufferLED, UpdateRateHz> rotaryLED;
	RgbLed<FrameBufferLED, UpdateRateHz> but[2];
};

