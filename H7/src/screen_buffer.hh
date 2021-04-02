#pragma once
#include "Adafruit_GFX_Library/Adafruit_GFX.h"
#include "conf/screen_buffer_conf.hh"
#include "drivers/colors.hh"
#include "drivers/dma2d_transfer.hh"

using ScreenConfT = MMScreenBufferConf;
// template <typename ScreenConfT>
class ScreenFrameBuffer : public Adafruit_GFX {

	target::DMA2DTransfer dma2d;
	ScreenConfT::FrameBufferT &framebuf;

public:
	ScreenFrameBuffer(ScreenConfT::FrameBufferT &framebuf_)
		: Adafruit_GFX{ScreenConfT::width, ScreenConfT::height}
		, framebuf{framebuf_}
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

	virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override
	{
		if (x >= _width || y >= _height)
			return;
		if ((x + w) > _width)
			w = _width - x;

		if ((h + y) > _height)
			h = _height - y;

		// Todo: Measure and set this for optimal performance
		constexpr uint32_t MaxSizeForDirectWrite = 1000;
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
		auto starting_addr = reinterpret_cast<uint32_t>(&framebuf[x + y * _width]);
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
		blendFastVLine(x0, y0 - r, 2 * r + 1, color, alpha);
		blendCircleHelper(x0, y0, r, 0b11, 0, color, alpha);
	}

	//
	// Pixel
	//

	void draw_blended_pix(int16_t x, int16_t y, uint16_t color, uint8_t alpha)
	{
		auto cur_pixel = framebuf[x + y * _width];
		framebuf[x + y * _width] = Color::blend(color, cur_pixel, alpha);
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

	virtual void drawPixel(int16_t x, int16_t y, uint16_t color) override
	{
		framebuf[x + y * _width] = color;
	}

	//
	// Line
	//

	virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override
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
	virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override
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

	void blendFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color, float alpha)
	{
		if (x < 0 || x >= _width)
			return;
		if (y < 0) {
			h += y;
			y = 0;
		}
		int16_t max_y = (h + y) > _height ? _height : y + h;
		uint8_t int_alpha = alpha * 255.f;

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
					blendFastVLine(x0 + x, y0 - y, 2 * y + delta, color, alpha);
				if (corners & 2)
					blendFastVLine(x0 - x, y0 - y, 2 * y + delta, color, alpha);
			}
			if (y != py) {
				if (corners & 1)
					blendFastVLine(x0 + py, y0 - px, 2 * px + delta, color, alpha);
				if (corners & 2)
					blendFastVLine(x0 - py, y0 - px, 2 * px + delta, color, alpha);
				py = y;
			}
			px = x;
		}
	}

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

	//
	// Text
	//

	void setTextColor(Color color)
	{
		Adafruit_GFX::setTextColor(color.Rgb565());
	}

	void setTextColor(Color fgcolor, Color bgcolor)
	{
		Adafruit_GFX::setTextColor(fgcolor.Rgb565(), bgcolor.Rgb565());
	}

	size_t write(uint8_t c) override
	{
		if (!gfxFont) { // 'Classic' built-in font

			if (c == '\n') {								// Newline?
				cursor_x = 0;								// Reset x to zero,
				cursor_y += textsize_y * 8;					// advance y one line
			} else if (c != '\r') {							// Ignore carriage returns
				if ((cursor_x + textsize_x * 6) > _width) { // Off right?
					if (wrap) {
						cursor_x = 0;				// Reset x to zero,
						cursor_y += textsize_y * 8; // advance y one line
					} else {
						return 0;
					}
				}
				drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize_x, textsize_y);
				cursor_x += textsize_x * 6; // Advance x one char
			}

		} else { // Custom font

			if (c == '\n') {
				cursor_x = 0;
				cursor_y += (int16_t)textsize_y * gfxFont->yAdvance;
			} else if (c != '\r') {
				uint8_t first = gfxFont->first;
				if ((c >= first) && (c <= gfxFont->last)) {
					GFXglyph *glyph = gfxFont->glyph + (c - first);
					uint8_t w = glyph->width, h = glyph->height;
					if ((w > 0) && (h > 0)) {
						int16_t xo = (int8_t)glyph->xOffset; // sic
						if ((cursor_x + textsize_x * (xo + w)) > _width) {
							if (wrap) {
								cursor_x = 0;
								cursor_y += (int16_t)textsize_y * gfxFont->yAdvance;
							} else {
								return 0;
							}
						}
						drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize_x, textsize_y);
					}
					cursor_x += glyph->xAdvance * (int16_t)textsize_x;
				}
			}
		}
		return 1;
	}

	void flush_cache() {}

	virtual void startWrite() override {}
	virtual void endWrite() override {}

protected:
	int _rotation;
	int _width;
	int _height;
};
