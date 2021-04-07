#pragma once
#include "Adafruit_GFX_Library/gfxfont.h"
#include "Adafruit_GFX_Library/glcdfont.c" //yep: .c, that's how arduino does it
#include "conf/screen_buffer_conf.hh"
#include "drivers/dma2d_transfer.hh"
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

	void drawPixel(int16_t x, int16_t y, uint16_t color)
	{
		framebuf[x + y * _width] = color;
	}

	//
	// Line
	//

	void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
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

	void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
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

	void setFont(const GFXfont *newfont)
	{
		if (newfont != nullptr) {
			if (gfxFont == nullptr) {
				// Switching from classic to new font behavior.
				// Move cursor pos down 6 pixels so it's on baseline.
				cursor_y += 6;
			}
		} else if (gfxFont != nullptr) {
			// Switching from new to classic font behavior.
			// Move cursor pos up 6 pixels so it's at top-left of char.
			cursor_y -= 6;
		}
		gfxFont = newfont;
	}

	size_t write(char c)
	{
		if (!gfxFont) {										// 'Classic' built-in font
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
					uint8_t w = glyph->width;
					uint8_t h = glyph->height;
					if ((w > 0) && (h > 0)) {
						int16_t xo = (int8_t)glyph->xOffset; // sic... what?
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

	void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size)
	{
		drawChar(x, y, c, color, bg, size, size);
	}

	void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y)
	{
		if (!gfxFont) {						  // 'Classic' built-in font
			if ((x >= _width) ||			  // Clip right
				(y >= _height) ||			  // Clip bottom
				((x + 6 * size_x - 1) < 0) || // Clip left
				((y + 8 * size_y - 1) < 0))	  // Clip top
				return;

			if (!_cp437 && (c >= 176))
				c++; // Handle 'classic' charset behavior

			for (int8_t i = 0; i < 5; i++) { // Char bitmap = 5 columns
				uint8_t line = font[c * 5 + i];
				for (int8_t j = 0; j < 8; j++, line >>= 1) {
					if (line & 1) {
						if (size_x == 1 && size_y == 1)
							drawPixel(x + i, y + j, color);
						else
							fillRect(x + i * size_x, y + j * size_y, size_x, size_y, color);
					} else if (bg != color) {
						if (size_x == 1 && size_y == 1)
							drawPixel(x + i, y + j, bg);
						else
							fillRect(x + i * size_x, y + j * size_y, size_x, size_y, bg);
					}
				}
			}
			if (bg != color) { // If opaque, draw vertical line for last column
				if (size_x == 1 && size_y == 1)
					drawFastVLine(x + 5, y, 8, bg);
				else
					fillRect(x + 5 * size_x, y, size_x, 8 * size_y, bg);
			}

		} else { // Custom font

			// Character is assumed previously filtered by write() to eliminate
			// newlines, returns, non-printable characters, etc.  Calling
			// drawChar() directly with 'bad' characters of font may cause mayhem!

			c -= (uint8_t)gfxFont->first;
			GFXglyph *glyph = gfxFont->glyph + c;
			uint8_t *bitmap = gfxFont->bitmap;

			uint16_t bo = glyph->bitmapOffset;
			uint8_t w = glyph->width;
			uint8_t h = glyph->height;
			int8_t xo = glyph->xOffset;
			int8_t yo = glyph->yOffset;
			uint8_t xx, yy, bits = 0, bit = 0;
			int16_t xo16 = 0, yo16 = 0;

			if (size_x > 1 || size_y > 1) {
				xo16 = xo;
				yo16 = yo;
			}

			if ((x >= _width) ||			  // Clip right
				(y >= _height) ||			  // Clip bottom
				((x + w * size_x - 1) < 0) || // Clip left
				((y + h * size_y - 1) < 0))	  // Clip top
				return;

			for (yy = 0; yy < h; yy++) {
				for (xx = 0; xx < w; xx++) {
					if (!(bit++ & 7)) {
						bits = bitmap[bo++];
					}
					if (bits & 0x80) {
						if (size_x == 1 && size_y == 1) {
							if ((x + xo + xx < _width) && (y + yo + yy < _height))
								drawPixel(x + xo + xx, y + yo + yy, color);
						} else {
							fillRect(x + (xo16 + xx) * size_x, y + (yo16 + yy) * size_y, size_x, size_y, color);
						}
					}
					bits <<= 1;
				}
			}
		} // End classic vs custom font
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

	int16_t cursor_x;		///< x location to start print()ing text
	int16_t cursor_y;		///< y location to start print()ing text
	uint16_t textcolor;		///< 16-bit background color for print()
	uint16_t textbgcolor;	///< 16-bit text color for print()
	uint8_t textsize_x;		///< Desired magnification in X-axis of text to print()
	uint8_t textsize_y;		///< Desired magnification in Y-axis of text to print()
	uint8_t rotation;		///< Display rotation (0 thru 3)
	bool wrap;				///< If set, 'wrap' text at right edge of display
	bool _cp437;			///< If set, use correct CP437 charset (default is off)
	const GFXfont *gfxFont; ///< Pointer to special font
};

void register_printf_destination(ScreenFrameBuffer &screen);
