#pragma once
#include "Adafruit_GFX_Library/Adafruit_GFX.h"
#include "conf/screen_conf.hh"
#include "drivers/colors.hh"

using ScreenConfT = MMScreenConf;
// template <typename ScreenConfT>
class ScreenFrameBuffer : public Adafruit_GFX {

	ScreenConfT::FrameBufferT &framebuf;

public:
	ScreenFrameBuffer(ScreenConfT::FrameBufferT &framebuf_)
		: Adafruit_GFX{ScreenConfT::width, ScreenConfT::height}
		, framebuf{framebuf_}
	{}

	void init()
	{
		set_rotation(ScreenConfT::rotation);
	}

	void set_rotation(ScreenConfT::Rotation rot)
	{
		_rotation = rot;
		if (_rotation == ScreenConfT::None || _rotation == ScreenConfT::Flip180) {
			_width = ScreenConfT::width;
			_height = ScreenConfT::height;
		} else {
			_width = ScreenConfT::height;
			_height = ScreenConfT::width;
		}
	}

	virtual void startWrite() override {}

	virtual void drawPixel(int16_t x, int16_t y, uint16_t color) override
	{
		framebuf[x + y * ScreenConfT::width] = color;
	}

	virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override
	{
		if ((x + w) > ScreenConfT::width)
			w = ScreenConfT::width - x;

		if ((h + y) > ScreenConfT::height)
			h = ScreenConfT::height - y;

		// Use DMA2D ?
		for (int xi = x; xi < (x + w); xi++) {
			for (int yi = y; yi < (y + h); yi++) {
				framebuf[xi + yi * ScreenConfT::width] = color;
			}
		}
	}

	virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override
	{
		if ((x + w) > ScreenConfT::width)
			w = ScreenConfT::width - x;

		const int16_t row_offset = x + y * ScreenConfT::width;
		for (int i = 0; i < w; i++) {
			framebuf[i + row_offset] = color;
		}
	}
	virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override
	{
		if ((h + y) > ScreenConfT::height)
			h = ScreenConfT::height - y;

		for (int i = y; i < (h + y); i++)
			framebuf[i * ScreenConfT::width + x] = color;
	}

	virtual void endWrite() override {}

	void fill(Color c)
	{
		fillRect(0, 0, ScreenConfT::width, ScreenConfT::height, c.Rgb565());
	}

	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, Color c)
	{
		fillRect(x, y, w, h, c.Rgb565());
	}

	void flush_cache()
	{
#if defined(CORE_CM7)
		SCB_CleanDCache_by_Addr((uint32_t *)(&framebuf), sizeof(ScreenConfT::FrameBufferT));
#endif
	}

protected:
	int _rotation;
	int _width;
	int _height;
};
