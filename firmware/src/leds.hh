#pragma once
#include "drivers/frame_buffer_led.hh"
#include "drivers/pca9685_led_driver.hh"
#include "drivers/rgbled.hh"
#include "drivers/stm32xx.h"
using namespace mdrivlib;

// CM7
// Todo: consider making the driver type a template parameter:
// (in conf:) using MMLedDriver = PCA9685Driver;
// (in main:) LedFrame<MMLedDriver, UpdateRateHz>
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

	void update_animation()
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

