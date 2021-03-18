#pragma once
#include "Adafruit_GFX_Library/Adafruit_GFX.h"
#include "conf/screen_conf.hh"
#include "drivers/colors.hh"

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
			DMA2D->IFCR |= DMA2D_IFCR_CTCIF;
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

	virtual void startWrite() override {}

	virtual void drawPixel(int16_t x, int16_t y, uint16_t color) override
	{
		framebuf[x + y * _width] = color;
	}

	virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override
	{
		if (x >= _width || y >= _height)
			return;
		if ((x + w) > _width)
			w = _width - x;

		if ((h + y) > _height)
			h = _height - y;

		// FixMe: it's actually faster to directly draw small areas than use DMA2D. Figure out what the break-point is
		// and choose the fastest algorithm
		// if (w*h > MaxSizeForDirectWrite)
		//     fastFillRect(x, y, w, h, color);
		// else {

		for (int xi = x; xi < (x + w); xi++) {
			for (int yi = y; yi < (y + h); yi++) {
				framebuf[xi + yi * _width] = color;
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

		// DMA2D->AMTCR = (255 << DMA2D_AMTCR_DT_Pos) | DMA2D_AMTCR_EN;
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

	void blendRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color, float alpha)
	{
		// Todo with DMA2D
	}
	void blendPixel(int16_t x, int16_t y, uint16_t color, float alpha)
	{
		// Todo
	}

	virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override
	{
		if (y < 0)
			return;
		if (y >= _height)
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
		if (x < 0)
			return;
		if (x >= _width)
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

	virtual void endWrite() override {}

	void fill(Color c)
	{
		fastFillRect(0, 0, ScreenConfT::width, ScreenConfT::height, c.Rgb565());
	}

	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, Color c)
	{
		fillRect(x, y, w, h, c.Rgb565());
	}

	void flush_cache()
	{
#if defined(CORE_CM7)
		SCB_CleanDCache_by_Addr((uint32_t *)(&framebuf[0]), sizeof(ScreenConfT::FrameBufferT));
#endif
	}

protected:
	int _rotation;
	int _width;
	int _height;
};
