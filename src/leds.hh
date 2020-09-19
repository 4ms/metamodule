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

	// Todo: only update if glowing or fading
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
	enum { Chip0 = 0, Chip1 = 1 };

public:
	DriverRgbLed freq[2] = {
		{
			{&led_frame_buf[led(Chip1, 12)]}, // Lock1
			{&led_frame_buf[led(Chip1, 13)]},
			{&led_frame_buf[led(Chip1, 14)]},
		},
		{
			{&led_frame_buf[led(Chip1, 0)]}, // Lock2
			{&led_frame_buf[led(Chip1, 1)]},
			{&led_frame_buf[led(Chip1, 2)]},
		},
	};

	DriverRgbLed res[2] = {
		{
			{&led_frame_buf[led(Chip1, 3)]}, // Lock3
			{&led_frame_buf[led(Chip1, 4)]},
			{&led_frame_buf[led(Chip1, 5)]},
		},
		{
			{&led_frame_buf[led(Chip1, 6)]}, // LFO Gate(CV?)
			{&led_frame_buf[led(Chip1, 7)]},
			{&led_frame_buf[led(Chip1, 8)]},
		},
	};

	DriverRgbLed but[2] = {
		{
			NoLED,
			NoLED,
			NoLED,
		},
		{
			NoLED,
			NoLED,
			NoLED,
		},
	};

	DriverRgbLed mode[5]{
		{
			{&led_frame_buf[led(Chip0, 0)]},
			{&led_frame_buf[led(Chip0, 1)]},
			{&led_frame_buf[led(Chip0, 2)]},
		},
		{
			{&led_frame_buf[led(Chip0, 9)]},
			{&led_frame_buf[led(Chip0, 10)]},
			{&led_frame_buf[led(Chip0, 11)]},
		},
		{
			{&led_frame_buf[led(Chip0, 11)]},
			{&led_frame_buf[led(Chip0, 13)]},
			{&led_frame_buf[led(Chip0, 14)]},
		},
		{
			NoLED,
			NoLED,
			NoLED,
		},
		{
			NoLED,
			NoLED,
			NoLED,
		},
	};

private:
	NoFrameBufferLED NoLED;
};

