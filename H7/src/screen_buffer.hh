#pragma once
#include "Adafruit_GFX_Library/Adafruit_GFX.h"
#include "conf/screen_conf.hh"
#include "drivers/colors.hh"
#include "drivers/rcc.hh"
#include "drivers/stm32xx.h"

using ScreenConfT = MMScreenConf;
// template <typename ScreenConfT>
class ScreenFrameBuffer : public Adafruit_GFX {

	ScreenConfT::FrameBufferT &framebuf;
	static volatile inline bool is_dma2d_done;

public:
	ScreenFrameBuffer(ScreenConfT::FrameBufferT &framebuf_)
		: Adafruit_GFX{ScreenConfT::width, ScreenConfT::height}
		, framebuf{framebuf_}
	{
		target::RCC_Control::DMA2D_::set();

		NVIC_DisableIRQ(DMA2D_IRQn);
		InterruptManager::registerISR(DMA2D_IRQn, [&]() {
			DMA2D->IFCR = DMA2D->IFCR | DMA2D_IFCR_CTCIF;
			is_dma2d_done = true;
			NVIC_DisableIRQ(DMA2D_IRQn);
		});
		auto pri = System::encode_nvic_priority(0, 0);
		NVIC_SetPriority(DMA2D_IRQn, pri);
		is_dma2d_done = true;
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
		DMA2D->NLR = h | (w << DMA2D_NLR_PL_Pos);
		DMA2D->OOR = _width - w;
		DMA2D->OMAR = reinterpret_cast<uint32_t>(&framebuf[x + y * _width]);
		DMA2D->OCOLR = color;
		DMA2D->OPFCCR = (0 << DMA2D_OPFCCR_RBS_Pos) | (0 << DMA2D_OPFCCR_AI_Pos) | (0 << DMA2D_OPFCCR_SB_Pos) |
						(0b010 << DMA2D_OPFCCR_CM_Pos);

		DMA2D->AMTCR = 0;
		DMA2D->IFCR = DMA2D_IFCR_CTCIF;
		DMA2D->CR = (0b011 << DMA2D_CR_MODE_Pos) | DMA2D_CR_TCIE; // clear everything else

		is_dma2d_done = false;
		NVIC_EnableIRQ(DMA2D_IRQn);
		DMA2D->CR |= DMA2D_CR_START;

		while (!is_dma2d_done) {
		}
		NVIC_DisableIRQ(DMA2D_IRQn);
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

	void flush_cache()
	{
#if defined(CORE_CM7)
		SCB_CleanDCache_by_Addr((uint32_t *)(&framebuf[0]), sizeof(ScreenConfT::FrameBufferT));
#endif
	}

	virtual void startWrite() override {}
	virtual void endWrite() override {}

protected:
	int _rotation;
	int _width;
	int _height;
};
