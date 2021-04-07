#pragma once
#include "conf/screen_buffer_conf.hh"
#include "drivers/dma2d_transfer.hh"
#include "mf_font.h"
#include "printf.h"
#include "util/colors.hh"

using ScreenConfT = MMScreenBufferConf;
// template <typename ScreenConfT>
class ScreenFrameBuffer {

#ifdef SIMULATOR
	ScreenSimulator::DMA2DTransfer dma2d;
#else
	target::DMA2DTransfer dma2d;
#endif
	ScreenConfT::FrameBufferT &framebuf;

public:
	ScreenFrameBuffer(ScreenConfT::FrameBufferT &framebuf_)
		: framebuf{framebuf_}
	{
		dma2d.init();
	}

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

	//
	// Rect
	//

	void fill(Color c)
	{
		fastFillRect(0, 0, ScreenConfT::width, ScreenConfT::height, c.Rgb565());
	}

	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, Color c)
	{
		fillRect(x, y, w, h, c.Rgb565());
	}

	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
	{
		if (x >= _width || y >= _height)
			return;
		if ((x + w) > _width)
			w = _width - x;

		if ((h + y) > _height)
			h = _height - y;

		// Todo: Measure and set this for optimal performance
		constexpr int MaxSizeForDirectWrite = 1000;
		if ((w * h) > MaxSizeForDirectWrite)
			fastFillRect(x, y, w, h, color);
		else {
			for (int xi = x; xi < (x + w); xi++) {
				for (int yi = y; yi < (y + h); yi++) {
					framebuf[xi + yi * _width] = color;
				}
			}
		}
	}

	void fastFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
	{
		uintptr_t starting_addr = reinterpret_cast<uintptr_t>(&framebuf[x + y * _width]);
		dma2d.fillrect_rgb565(starting_addr, w, h, _width, color);
	}

	void blendRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color, float f_alpha)
	{
		// Todo with DMA2D
		if (x >= _width || y >= _height)
			return;

		uint8_t alpha = f_alpha * 255.f;
		if (alpha < 4)
			return;
		if (alpha > 252) {
			fillRect(x, y, w, h, color);
			return;
		}

		int16_t max_x = (x + w) > _width ? _width : x + w;
		int16_t max_y = (h + y) > _height ? _height : y + h;

		for (int xi = x; xi < max_x; xi++) {
			for (int yi = y; yi < max_y; yi++) {
				draw_blended_pix(xi, yi, color, alpha);
			}
		}
	}

	//
	// Circle
	//

	void blendCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color, float alpha)
	{
		// 3.9ms:
		// blend64FillCircle(x0, y0, r, color, alpha);
		// 4.0ms
		blendVLine(x0, y0 - r, 2 * r + 1, color, alpha);
		blendCircleHelper(x0, y0, r, 0b11, 0, color, alpha);
	}

	//
	// Pixel
	//

	// Blends a pixel into the framebuffer. Not bounds-checked!
	void draw_blended_pix(int16_t x, int16_t y, uint16_t color, uint8_t alpha)
	{
		auto cur_pixel = framebuf[x + y * _width];
		framebuf[x + y * _width] = Color::blend(color, cur_pixel, alpha);
	}

	// Blends a Pixel into the framebuffer, using the current text fg color. Not bounds checked!
	void draw_blended_text_pixel(int16_t x, int16_t y, uint8_t alpha)
	{
		auto cur_pixel = framebuf[x + y * _width];
		framebuf[x + y * _width] = Color::blend(textcolor, cur_pixel, alpha);
	}

	// Blends a pixel into the framebuffer, using current text fg color. Clips at screen bounds.
	void draw_blended_text_pixel_clipped(int16_t x, int16_t y, uint8_t alpha)
	{
		if (x < 0 || x >= _width || y < 0 || y >= _height)
			return;
		auto cur_pixel = framebuf[x + y * _width];
		framebuf[x + y * _width] = Color::blend(textcolor, cur_pixel, alpha);
	}

	void blendPixel(int16_t x, int16_t y, uint16_t color, float f_alpha)
	{
		uint8_t alpha = f_alpha * 255.f;
		if (alpha < (1.f / 64.f))
			return;
		else if (alpha > (63.f / 64.f))
			drawPixel(x, y, color);
		else
			draw_blended_pix(x, y, color, alpha);
	}

	void drawPixel(int16_t x, int16_t y, uint16_t color)
	{
		framebuf[x + y * _width] = color;
	}

	//
	// Line
	//

	void drawHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
	{
		if (y < 0 || y >= _height)
			return;
		if (x < 0) {
			w += x;
			x = 0;
		}
		if ((x + w) >= _width)
			w = _width - x;

		const int16_t row_offset = x + y * _width;
		for (int i = 0; i < w; i++) {
			framebuf[i + row_offset] = color;
		}
	}

	void blendHLine(int16_t x, int16_t y, int16_t w, uint16_t color, float alpha)
	{
		if (y < 0 || y >= _height)
			return;
		if (x < 0) {
			w += x;
			x = 0;
		}
		int16_t max_x = (w + x) > _width ? _width : x + w;

		for (int xi = x; xi < max_x; xi++)
			draw_blended_pix(xi, y, color, alpha);
	}

	// Uses current text color
	void blendHLineText(int16_t x, int16_t y, int16_t w, float alpha)
	{
		if (y < 0 || y >= _height)
			return;
		if (x < 0) {
			w += x;
			x = 0;
		}
		int16_t max_x = (w + x) > _width ? _width : x + w;

		for (int xi = x; xi < max_x; xi++)
			draw_blended_pix(xi, y, textcolor, alpha);
	}

	void drawVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
	{
		if (x < 0 || x >= _width)
			return;
		if (y < 0) {
			h += y;
			y = 0;
		}
		if ((h + y) >= _height)
			h = _height - y;

		for (int i = y; i < (h + y); i++)
			framebuf[i * _width + x] = color;
	}

	void blendVLine(int16_t x, int16_t y, int16_t h, uint16_t color, float alpha)
	{
		if (x < 0 || x >= _width)
			return;
		if (y < 0) {
			h += y;
			y = 0;
		}
		int16_t max_y = (h + y) > _height ? _height : y + h;

		for (int yi = y; yi < max_y; yi++)
			draw_blended_pix(x, yi, color, alpha);

		// Slightly improved algorithm: Todo test if it's worth it
		//#4: 4.0ms
		// uint8_t _alpha = (int_alpha + 4) >> 3;
		// uint32_t fg = (color | (color << 16)) & 0b00000111111000001111100000011111;
		// for (int32_t pos = x + y * _width; pos < (x + max_y * _width); pos += _width) {
		// 	uint32_t bg = framebuf[pos];
		// 	bg = (bg | (bg << 16)) & 0b00000111111000001111100000011111;
		// 	uint32_t result = ((((fg - bg) * _alpha) >> 5) + bg) & 0b00000111111000001111100000011111;
		// 	framebuf[pos] = (uint16_t)((result >> 16) | result);
		// }
	}

	//
	// Blending helpers
	//

	void
	blendCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t corners, int16_t delta, uint16_t color, float alpha)
	{
		int16_t f = 1 - r;
		int16_t ddF_x = 1;
		int16_t ddF_y = -2 * r;
		int16_t x = 0;
		int16_t y = r;
		int16_t px = x;
		int16_t py = y;

		delta++; // Avoid some +1's in the loop

		while (x < y) {
			if (f >= 0) {
				y--;
				ddF_y += 2;
				f += ddF_y;
			}
			x++;
			ddF_x += 2;
			f += ddF_x;
			// These checks avoid double-drawing certain lines, important
			// for the SSD1306 library which has an INVERT drawing mode.
			if (x < (y + 1)) {
				if (corners & 1)
					blendVLine(x0 + x, y0 - y, 2 * y + delta, color, alpha);
				if (corners & 2)
					blendVLine(x0 - x, y0 - y, 2 * y + delta, color, alpha);
			}
			if (y != py) {
				if (corners & 1)
					blendVLine(x0 + py, y0 - px, 2 * px + delta, color, alpha);
				if (corners & 2)
					blendVLine(x0 - py, y0 - px, 2 * px + delta, color, alpha);
				py = y;
			}
			px = x;
		}
	}

	void blend64FillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color, float alpha)
	{
		int16_t f = 1 - r;
		int16_t ddF_x = 1;
		int16_t ddF_y = -2 * r;
		int16_t x = 0;
		int16_t y = r;
		int16_t px = x;
		int16_t py = y;
		uint8_t int_alpha = alpha * 255.f;
		uint8_t _alpha = (int_alpha + 4) >> 3;
		uint32_t fg = (color | (color << 16)) & 0b00000111111000001111100000011111;

		_blend64_vline(x0, y0 - r, y0 + r, fg, _alpha);

		while (x < y) {
			if (f >= 0) {
				y--;
				ddF_y += 2;
				f += ddF_y;
			}
			x++;
			ddF_x += 2;
			f += ddF_x;
			if (x < (y + 1)) {
				_blend64_two_vline(x0 + x, x0 - x, y0 - y, y0 + y, fg, _alpha);
			}
			if (y != py) {
				_blend64_two_vline(x0 + py, x0 - py, y0 - px, y0 + px, fg, _alpha);
				py = y;
			}
			px = x;
		}
	}

private:
	// Blend helpers:
	uint16_t _blend64_helper(uint32_t fg32, uint32_t bg_color, uint8_t alpha64)
	{
		uint32_t bg32 = (bg_color | (bg_color << 16)) & 0b00000111111000001111100000011111;
		uint32_t result = ((((fg32 - bg32) * alpha64) >> 5) + bg32) & 0b00000111111000001111100000011111;
		return (uint16_t)((result >> 16) | result);
	}

	void _blend64_vline(int16_t x, int16_t y_top, int16_t y_bot, uint32_t fg32, uint8_t alpha64)
	{
		if (y_top < 0)
			y_top = 0;
		if (y_bot >= _height)
			y_bot = _height - 1;
		if (x < 0 || x >= _width)
			return;
		for (int32_t pos = y_top * _width; pos <= y_bot * _width; pos += _width) {
			framebuf[x + pos] = _blend64_helper(fg32, framebuf[x + pos], alpha64);
		}
	}

	void _blend64_two_vline(int16_t x1, int16_t x2, int16_t y_top, int16_t y_bot, uint32_t fg32, uint8_t alpha64)
	{
		// Todo: do we need to bounds check here, or can we do that in top-level?
		if (y_top < 0)
			y_top = 0;
		if (y_bot >= _height)
			y_bot = _height - 1;
		// bool do_x1 = true;
		// if (x1 < 0 || x1 >= _width)
		// 	do_x1 = false;
		// bool do_x2 = true;
		// if (x2 < 0 || x2 >= _width)
		// 	do_x2 = false;
		// if (!do_x1 && !do_x2)
		// 	return;
		// if (!do_x1) ...
		for (int32_t pos = y_top * _width; pos <= y_bot * _width; pos += _width) {
			framebuf[x1 + pos] = _blend64_helper(fg32, framebuf[x1 + pos], alpha64);
			framebuf[x2 + pos] = _blend64_helper(fg32, framebuf[x2 + pos], alpha64);
		}
	}

public:
	//
	// Text
	//

	void setTextColor(Color color)
	{
		textcolor = textbgcolor = color.Rgb565();
	}

	void setTextColor(Color fgcolor, Color bgcolor)
	{
		textcolor = fgcolor.Rgb565();
		textbgcolor = bgcolor.Rgb565();
	}

	void setTextSize(uint8_t s)
	{
		textsize_x = textsize_y = s;
	}
	void setTextSize(uint8_t s_x, uint8_t s_y)
	{
		textsize_x = s_x;
		textsize_y = s_y;
	}

	void setCursor(int16_t x, int16_t y)
	{
		cursor_x = x;
		cursor_y = y;
	}

	void setTextWrap(bool w)
	{
		wrap = w;
	}

	void setFont(const mf_font_s *newfont)
	{
		font = newfont;
	}

	// printf() calls this
	int write(char c)
	{
		// in adafruit, this called drawChar() using current cursor, textColor, and textSize
		return 0;
	}

	void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size)
	{
		drawChar(x, y, c, color, bg, size, size);
	}

	void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y)
	{
		//
	}

	// clang-format off
	int print(const char s[]) 	{ return printf("%s", s); }
	int print(const char c) 	{ return printf("%c", c); }
	int print(int n) 			{ return printf("%d", n); }
	int print(unsigned n) 		{ return printf("%d", n); }
	int print(long n) 			{ return printf("%d", n); }
	int print(unsigned long n) 	{ return printf("%d", n); }
	// int print(float f) 			{ return printf("%f", f); }
	// clang-format on

	void flush_cache() {}

protected:
	int _rotation;
	int _width;
	int _height;

	int16_t cursor_x;
	int16_t cursor_y;
	uint16_t textcolor;
	uint16_t textbgcolor;
	uint8_t textsize_x;
	uint8_t textsize_y;
	uint8_t rotation;
	bool wrap;
	const mf_font_s *font;
};

void register_printf_destination(ScreenFrameBuffer &screen);
