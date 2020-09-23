#pragma once
#include "colors.hh"
#include "frame_buffer_led.hh"
#include "i2c.hh"
#include "pca9685_led_driver.hh"
#include "pin.hh"
#include "rgbled.hh"
#include "stm32f7xx.h"

using DriverRgbLed = RgbLed<FrameBufferLED>;

class LedCtl {
public:
	LedCtl(I2CPeriph &i2c)
		: led_driver_{i2c}
		, led_frame_buf{led_driver_.get_frame_buffer()}
	{}

	void start_dma_mode()
	{
		led_driver_.start();
		led_driver_.start_dma_mode();
	}

	//Todo: only update if glowing or fading
	void update()
	{
		freq[0].refresh();
		res[0].refresh();
		but[0].refresh();

		freq[1].refresh();
		res[1].refresh();
		but[1].refresh();

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

	DriverRgbLed res[2] = {
		{
			{&led_frame_buf[led(Chip1, 5)]},
			{&led_frame_buf[led(Chip1, 6)]},
			{&led_frame_buf[led(Chip1, 7)]},
		},
		{
			{&led_frame_buf[led(Chip1, 8)]},
			NoLED, // was this: {&led_frame_buf[led(Chip1, 9)]},
			{&led_frame_buf[led(Chip1, 10)]},
		},
	};

	DriverRgbLed but[2] = {
		{
			{&led_frame_buf[led(Chip1, 0)]},
			{&led_frame_buf[led(Chip1, 9)]},
			{&led_frame_buf[led(Chip0, 15)]},
		},
		{
			{&led_frame_buf[led(Chip1, 1)]},
			{&led_frame_buf[led(Chip1, 14)]},
			{&led_frame_buf[led(Chip1, 15)]},
		},
	};

	DriverRgbLed mode[5]{
		{
			{&led_frame_buf[led(Chip0, 8)]},
			{&led_frame_buf[led(Chip0, 9)]},
			{&led_frame_buf[led(Chip0, 10)]},
		},
		{
			{&led_frame_buf[led(Chip0, 11)]},
			{&led_frame_buf[led(Chip0, 12)]},
			{&led_frame_buf[led(Chip0, 13)]},
		},
		{
			{&led_frame_buf[led(Chip0, 14)]},
			{&led_frame_buf[led(Chip0, 7)]},
			{&led_frame_buf[led(Chip0, 6)]},
		},
		{
			{&led_frame_buf[led(Chip0, 5)]},
			{&led_frame_buf[led(Chip0, 4)]},
			{&led_frame_buf[led(Chip0, 3)]},
		},
		{
			{&led_frame_buf[led(Chip0, 2)]},
			{&led_frame_buf[led(Chip0, 1)]},
			{&led_frame_buf[led(Chip0, 0)]},
		},
	};

private:
	NoFrameBufferLED NoLED;
};

