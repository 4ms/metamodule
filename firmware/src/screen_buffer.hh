#pragma once
#include "conf/screen_buffer_conf.hh"
#include "drivers/arch.hh"
#include "drivers/cache.hh"
#include "drivers/dma2d_transfer.hh"
#include "mcufont.h"
#include "pages/fonts.hh"
#include "printf.h"
#include "util/colors.hh"
#include "util/geometry.hh"

extern "C" void _draw_text_pixel_callback(int16_t x, int16_t y, uint8_t count, uint8_t alpha, void *state);
extern "C" uint8_t _char_cursor_callback(int16_t x0, int16_t y0, mf_char character, void *state);

using ScreenConfT = MMScreenBufferConf;
// template <typename ScreenConfT>

class ScreenFrameBuffer {
	mdrivlib::DMA2DTransfer dma2d;
	ScreenConfT::FrameBufferT &framebuf;

public:
	enum Alignment { Left, Right, Center };

	ScreenFrameBuffer(ScreenConfT::FrameBufferT &framebuf_)
		: framebuf{framebuf_}
	{
		dma2d.init();
		_font = &mf_rlefont_fixed_10x20.font;
		setAlignment(Left);
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
		// Fixme: fix fastFillRect for A7
		// fastFillRect(0, 0, ScreenConfT::width, ScreenConfT::height, c.Rgb565());
		// fillRect(0, 0, ScreenConfT::width, ScreenConfT::height, c.Rgb565());

		fillRect(0, 0, _width, _height, c.Rgb565());
	}

	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, Color c)
	{
		fillRect(x, y, w, h, c.Rgb565());
	}

	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
	{
		if (x >= clip_rect.width() || y >= clip_rect.height())
			return;
		if ((x + w) > clip_rect.width())
			w = clip_rect.width() - x;

		if ((h + y) > clip_rect.height())
			h = clip_rect.height() - y;

		// Fixme: fix fastFillRect for A7
		// Todo: Measure and set this for optimal performance
		// constexpr int MaxSizeForDirectWrite = 1000;
		// if ((w * h) > MaxSizeForDirectWrite)
		// 	fastFillRect(x, y, w, h, color);
		// else {
		for (int yi = y; yi < (y + h); yi++) {
			for (int xi = x; xi < (x + w); xi++) {
				framebuf[xi + yi * clip_rect.width()] = color;
			}
		}
		// }
	}

	void fastFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
	{
		auto starting_addr = reinterpret_cast<uintptr_t>(&framebuf[x + y * _width]);
		dma2d.fillrect_rgb565(starting_addr, w, h, _width, color);
	}

	void blendRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color, float f_alpha)
	{
		// Todo with DMA2D
		if (x >= clip_rect.right || y >= clip_rect.bottom)
			return;

		uint8_t alpha = f_alpha * 255.f;
		if (alpha < 4)
			return;
		if (alpha > 252) {
			fillRect(x, y, w, h, color);
			return;
		}

		int16_t max_x = (x + w) > clip_rect.right ? clip_rect.right : x + w;
		int16_t max_y = (h + y) > clip_rect.bottom ? clip_rect.bottom : y + h;

		if (max_x < clip_rect.left || max_y < clip_rect.top)
			return;

		if (x < clip_rect.left)
			x = clip_rect.left;

		if (y < clip_rect.top)
			y = clip_rect.top;

		for (int yi = y; yi < max_y; yi++) {
			for (int xi = x; xi < max_x; xi++) {
				draw_blended_pix(xi, yi, color, alpha);
			}
		}
	}

	void blendRect(Rect r, uint16_t color, float f_alpha)
	{
		blendRect(r.left, r.top, r.width, r.height, color, f_alpha);
	}
	void blendRect(RectC r, uint16_t color, float f_alpha)
	{
		blendRect(r.left, r.top, r.width(), r.height(), color, f_alpha);
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
		framebuf[x + y * _width] = Color::blend(cur_pixel, color, alpha);
	}

	// Blends a Pixel into the framebuffer, using the current text fg color. Not bounds checked!
	void draw_blended_text_pixel(int16_t x, int16_t y, uint8_t alpha)
	{
		draw_blended_pix(x, y, textcolor, alpha);
	}

	// Blends a pixel into the framebuffer. Clips at screen bounds.
	void draw_blended_pixel_clipped(int16_t x, int16_t y, uint16_t color, uint8_t alpha)
	{
		if (x < 0 || x >= _width || y < 0 || y >= _height)
			return;
		auto cur_pixel = framebuf[x + y * _width];
		framebuf[x + y * _width] = Color::blend(cur_pixel, color, alpha);
	}

	// Blends a pixel into the framebuffer, using current text fg color. Clips at screen bounds.
	void draw_blended_text_pixel_clipped(int16_t x, int16_t y, uint8_t alpha)
	{
		draw_blended_pixel_clipped(x, y, textcolor, alpha);
	}

	// Blends a pixel into the framebuffer. Optimized if alpha is near min or max.
	// Not bounds checked!
	// alpha: 0 => no change to framebuffer, 255 => color replaces pixel in framebuffer
	void blendPixel(int16_t x, int16_t y, uint16_t color, uint8_t alpha)
	{
		if (alpha < 4)
			return;
		else if (alpha > 252)
			drawPixel(x, y, color);
		else
			draw_blended_pix(x, y, color, alpha);
	}

	// Blends a pixel into the framebuffer. Optimized if alpha is near min or max
	// f_alpha: 0 => no change to framebuffer, 1=>color replaces pixel in framebuffer
	void blendPixel(int16_t x, int16_t y, uint16_t color, float f_alpha)
	{
		blendPixel(x, y, color, (uint8_t)(f_alpha * 255.f));
	}

	// Sets a pixel in the framebuffer. Not bounds checked, and does not respect clipping rect!
	void drawPixel(int16_t x, int16_t y, uint16_t color)
	{
		framebuf[x + y * _width] = color;
	}

	//
	// Line
	//

	//Draws a solid horizontal line onto the buffer, respecting the clipping rect
	void drawHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
	{
		if (y < clip_rect.top || y >= clip_rect.bottom)
			return;
		if (x < clip_rect.left) {
			w += x;
			x = clip_rect.left;
		}
		int16_t max_x = (w + x) >= clip_rect.right ? clip_rect.right : x + w;

		for (int16_t xi = x; xi < max_x; xi++) {
			drawPixel(xi, y, color);
		}
	}

	// Blends a horizontal line on the buffer, respecting the clipping rect
	void blendHLine(int16_t x, int16_t y, int16_t w, uint16_t color, uint8_t alpha)
	{
		if (alpha > 252) {
			drawHLine(x, y, w, color);
			return;
		}
		if (alpha < 4 || y < clip_rect.top || y >= clip_rect.bottom)
			return;
		if (x < clip_rect.left) {
			w += x;
			x = clip_rect.left;
		}
		int16_t max_x = (w + x) >= clip_rect.right ? clip_rect.right : x + w;

		// Todo: try reading all pixels onto stack, then blend and write all at once
		// Might give a performance boost, due to caching
		for (int16_t xi = x; xi < max_x; xi++)
			draw_blended_pix(xi, y, color, alpha);
	}

	void blendHLineText(int16_t x, int16_t y, int16_t w, uint8_t alpha)
	{
		blendHLine(x, y, w, textcolor, alpha);
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
		textcolor = color.Rgb565();
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
		_font = newfont;
	}

	void setAlignment(Alignment align)
	{
		_alignment = align == Center ? MF_ALIGN_CENTER : align == Right ? MF_ALIGN_RIGHT : MF_ALIGN_LEFT;
	}

	void printf_at(int16_t x, int16_t y, const char *format, ...)
	{
		va_list args;
		va_start(args, format);
		int res = vsnprintf(_textbuf, 255, format, args);
		if (res)
			mf_render_aligned(_font, x, y, _alignment, _textbuf, 0, &_char_cursor_callback, nullptr);
		va_end(args);
	}

	void printf(const char *format, ...)
	{
		va_list args;
		va_start(args, format);
		int res = vsnprintf(_textbuf, 255, format, args);
		if (res)
			mf_render_aligned(_font, cursor_x, cursor_y, _alignment, _textbuf, 0, &_char_cursor_callback, nullptr);
		va_end(args);
	}

	void _render_textbuf()
	{
		mf_render_aligned(_font, cursor_x, cursor_y, _alignment, _textbuf, 0, &_char_cursor_callback, nullptr);
	}

	// Quick print shortcuts
	// clang-format off
	void print(const char s[]) 	{ if (snprintf(_textbuf, 255, "%s", s)) _render_textbuf(); }
	void print(const char c) 	{ if (snprintf(_textbuf, 255, "%c", c)) _render_textbuf(); }
	void print(int n) 			{ if (snprintf(_textbuf, 255, "%d", n)) _render_textbuf(); }
	void print(unsigned n) 		{ if (snprintf(_textbuf, 255, "%d", n)) _render_textbuf(); }
	void print(long n) 			{ if (snprintf(_textbuf, 255, "%d", n)) _render_textbuf(); }
	void print(unsigned long n)	{ if (snprintf(_textbuf, 255, "%d", n)) _render_textbuf(); }
	// void print(float n)			{ if (snprintf(_textbuf, 255, "%f", n)) _render_textbuf(); }
	// clang-format on

	void flush_cache()
	{
		if constexpr (mdrivlib::TargetName == mdrivlib::Targets::stm32mp1_ca7) {
			mdrivlib::SystemCache::clean_dcache_by_range(&framebuf, sizeof(ScreenConfT::FrameBufferT));
			__DSB();
			// do mem2mem xfer
		}
	}

	void set_clip_rect(RectC rect)
	{
		clip_rect = rect;
	}

	void set_clip_rect(Rect rect)
	{
		clip_rect = RectC{rect.left, rect.top, rect.right(), rect.bottom()};
	}

	void clear_clip_rect()
	{
		clip_rect = RectC{0, 0, ScreenConfT::viewWidth, ScreenConfT::viewHeight};
	}

	const mf_font_s *_font;
	mf_align_t _alignment;
	uint16_t textcolor;
	int16_t cursor_x;
	int16_t cursor_y;

protected:
	int _rotation;
	int _width;
	int _height;

	uint8_t rotation;
	bool wrap;

private:
	char _textbuf[255];
	RectC clip_rect{0, 0, ScreenConfT::viewWidth, ScreenConfT::viewHeight};
};

void register_printf_destination(ScreenFrameBuffer &screen);
