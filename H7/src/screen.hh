#pragma once
#include "Adafruit_GFX_Library/Adafruit_GFX.h"
#include "conf/screen_conf.hh"
#include "drivers/colors.hh"
#include "drivers/pin.hh"
#include "drivers/spi.hh"
#include "drivers/spi_screen_ST77XX.hh"
#include "drivers/spi_screen_driver.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"

using ScreenConfT = MMScreenConf;

// Todo: generalize this adaptor so we can include it in mdrivlib
// Why does making Screen a template class over <ScreenConT>, remove ability to access SpiScreenDriver base class?
// template<typename ScreenConfT>

class ScreenGFXAdaptor : public SpiScreenDriver<ScreenConfT>, public Adafruit_GFX {
public:
	ScreenGFXAdaptor()
		: Adafruit_GFX{ScreenConfT::width, ScreenConfT::height}
		, window_height{ScreenConfT::width}
		, window_width{ScreenConfT::height}
		, _rowstart{ScreenConfT::rowstart}
		, _colstart{ScreenConfT::colstart}
	{}

	void init()
	{
		init_display(generic_st7789);
		set_rotation(1);
	}

	void set_rotation(uint8_t m)
	{
		uint8_t madctl = 0;

		_rotation = m & 3;

		switch (_rotation) {
			case 0:
				madctl = ST77XX::MADCTL_MX | ST77XX::MADCTL_MY | ST77XX::MADCTL_RGB;
				_xstart = _colstart;
				_ystart = _rowstart;
				_width = window_width;
				_height = window_height;
				break;
			case 1:
				madctl = ST77XX::MADCTL_MY | ST77XX::MADCTL_MV | ST77XX::MADCTL_RGB;
				_xstart = _rowstart;
				_ystart = _colstart;
				_height = window_width;
				_width = window_height;
				break;
			case 2:
				madctl = ST77XX::MADCTL_RGB;
				_xstart = 0;
				_ystart = 0;
				_width = window_width;
				_height = window_height;
				break;
			case 3:
				madctl = ST77XX::MADCTL_MX | ST77XX::MADCTL_MV | ST77XX::MADCTL_RGB;
				_xstart = 0;
				_ystart = 0;
				_height = window_width;
				_width = window_height;
				break;
		}
		transmit<Cmd>(ST77XX::MADCTL);
		transmit<Data>(madctl);
	}

	virtual void startWrite() override
	{
		//
	}

	virtual void drawPixel(int16_t x, int16_t y, uint16_t color) override
	{
		set_pos(x, y, x, y);
		transmit_data_16(color);
	}

	// This tasks ~18ms
	virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override
	{
		set_pos(x, y, x + w - 1, y + h - 1);
		begin_open_data_transmission(4);
		uint32_t color32 = color << 16 | color;
		for (int i = 0; i < ((w + 1) * (h + 1)); i += 2) {
			transmit_open_data32(color32);
		}
		end_open_data_transmission();
	}

	// Note: this takes ~350ms!
	// void fillRect_slow(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
	// {
	// 	set_pos(x, y, x + w - 1, y + h - 1);
	// 	for (int i = 0; i <= ((w) * (h)); i += 1) {
	// 		transmit_data_32(color, color);
	// 	}
	// }
	virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override
	{
		set_pos(x, y, x + w - 1, y);
		for (int i = 0; i <= w; i++) {
			transmit_data_32(color, color);
		}
	}
	virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override
	{
		set_pos(x, y, x, y + h - 1);
		for (int i = 0; i <= h; i++) {
			transmit_data_32(color, color);
		}
	}

	virtual void endWrite() override
	{
		//
	}

	// Todo: print_in_box(x,y,w,h, char* txt, uint32_t len)
	// does what print() does (using draw_char()) but also draws the background with custom fonts
	// After drawing text, it will fillRect() all remaining pixels within the box

protected:
	const int window_width;
	const int window_height;
	const int _colstart;
	const int _rowstart;

	int _rotation;
	int _xstart;
	int _ystart;
	int _width;
	int _height;

public:
	void set_pos(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
	{
		Xstart += _xstart;
		Ystart += _ystart;
		Xend += _xstart;
		Yend += _ystart;
		transmit<Cmd>(ST77XX::CASET);
		transmit_data_32(Xstart, Xend);

		transmit<Cmd>(ST77XX::RASET);
		transmit_data_32(Ystart, Yend);

		transmit<Cmd>(ST77XX::RAMWR);
	}

	// Todo re-write as just a sequence of commands with delays
	void init_display(const uint8_t *addr)
	{
		uint8_t numCommands, cmd, numArgs;
		uint16_t ms;

		numCommands = *addr++;					 // Number of commands to follow
		while (numCommands--) {					 // For each command...
			cmd = *addr++;						 // Read command
			numArgs = *addr++;					 // Number of args to follow
			ms = numArgs & ST77XX::ST_CMD_DELAY; // If hibit set, delay follows args
			numArgs &= ~ST77XX::ST_CMD_DELAY;	 // Mask out delay bit
			transmit<Cmd>(cmd);
			while (numArgs--) {
				transmit<Data>(*addr++);
			}

			if (ms) {
				ms = *addr++; // Read post-command delay time (ms)
				if (ms == 255)
					ms = 500; // If 255, delay for 500 ms
				HAL_Delay(ms);
			}
		}
	}
};

// template <typename ScreenConfT>
struct Screen : public ScreenGFXAdaptor {

	Screen() {}

	void fill(Color c)
	{
		fillRect(0, 0, ScreenConfT::width, ScreenConfT::height, c.Rgb565());
	}
};

/////////////////////////////////////////
//////////////////////////////////////////

// template <typename ScreenConfT>
class ScreenFrameWriter : public DmaSpiScreenDriver<ScreenConfT> {
	ScreenConfT::FrameBufferT *framebuf;

public:
	ScreenFrameWriter(ScreenConfT::FrameBufferT *framebuf_)
		: framebuf{framebuf_}
		, _rowstart{ScreenConfT::rowstart}
		, _colstart{ScreenConfT::colstart}
	{
		DmaSpiScreenDriver<ScreenConfT>::init();
	}

	void init()
	{
		init_display(generic_st7789);
		set_rotation(1); // ScreenConfT::rotation
	}

	void set_rotation(uint8_t m)
	{
		uint8_t madctl = 0;

		_rotation = m & 3;

		switch (_rotation) {
			case 0:
				madctl = ST77XX::MADCTL_MX | ST77XX::MADCTL_MY | ST77XX::MADCTL_RGB;
				_xstart = _colstart;
				_ystart = _rowstart;
				_width = ScreenConfT::width;
				_height = ScreenConfT::height;
				break;
			case 1:
				madctl = ST77XX::MADCTL_MY | ST77XX::MADCTL_MV | ST77XX::MADCTL_RGB;
				_xstart = _rowstart;
				_ystart = _colstart;
				_height = ScreenConfT::width;
				_width = ScreenConfT::height;
				break;
			case 2:
				madctl = ST77XX::MADCTL_RGB;
				_xstart = 0;
				_ystart = 0;
				_width = ScreenConfT::width;
				_height = ScreenConfT::height;
				break;
			case 3:
				madctl = ST77XX::MADCTL_MX | ST77XX::MADCTL_MV | ST77XX::MADCTL_RGB;
				_xstart = 0;
				_ystart = 0;
				_height = ScreenConfT::width;
				_width = ScreenConfT::height;
				break;
		}
		transmit_blocking<Cmd>(ST77XX::MADCTL);
		transmit_blocking<Data>(madctl);
	}

	// void transfer_buffer_to_screen_blocking()
	// {
	// 	SCB_CleanDCache_by_Addr((uint32_t *)framebuf, sizeof(ScreenConfT::FrameBufferT));
	// 	set_pos(0, 0, _width, _height);
	// 	begin_open_data_transmission(4);
	// 	for (int i = 0; i < (_width * _height); i += 2) {
	// 		transmit_open_data32((*framebuf)[i], (*framebuf)[i + 1]);
	// 	}
	// 	end_open_data_transmission();
	// }

	void transfer_buffer_to_screen()
	{
		set_pos(0, 0, 239, 239);
		// SCB_CleanDCache_by_Addr((uint32_t *)0x24000000 /*(uint32_t *)framebuf*/, sizeof(ScreenConfT::FrameBufferT));
		Debug::Pin1::high();

		// init_mdma([&]() {
		// 	Debug::Pin1::low();
		// 	// set_pos(0, 120, 240, 240);
		// 	// Debug::Pin2::high();
		// 	// init_mdma([&]() { Debug::Pin2::low(); });
		// 	// start_dma_transfer(0x24000000 + sizeof(ScreenConfT::FrameBufferT) / 2,
		// 	// 				   sizeof(ScreenConfT::FrameBufferT) / 2);
		// });

		// uint16_t *addr = (uint16_t *)(0x24000000);
		for (int i = 0; i < (_width * _height / 1); i += 2) {
			// uint16_t val1 = *addr++;
			// uint16_t val2 = *addr++;
			// transmit_blocking<Data>(val1, val2);
			transmit_blocking<Data>(0xD900, 0xD900);
		}
		// start_dma_transfer(0x24000000, sizeof(ScreenConfT::FrameBufferT) / 2);
	}

protected:
	const int _colstart;
	const int _rowstart;
	int _rotation;
	int _xstart;
	int _ystart;
	int _width;
	int _height;

	void set_pos(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
	{
		Xstart += _xstart;
		Ystart += _ystart;
		Xend += _xstart;
		Yend += _ystart;
		transmit_blocking<Cmd>(ST77XX::CASET);
		transmit_blocking<Data>(Xstart, Xend);

		transmit_blocking<Cmd>(ST77XX::RASET);
		transmit_blocking<Data>(Ystart, Yend);

		transmit_blocking<Cmd>(ST77XX::RAMWR);
	}

	// Todo re-write as just a sequence of commands with delays
	// Make a fake transmit_blocking<>(uint8_t) and fake HAL_Delay() to record results
	void init_display(const uint8_t *addr)
	{
		uint8_t numCommands, cmd, numArgs;
		uint16_t ms;

		numCommands = *addr++;					 // Number of commands to follow
		while (numCommands--) {					 // For each command...
			cmd = *addr++;						 // Read command
			numArgs = *addr++;					 // Number of args to follow
			ms = numArgs & ST77XX::ST_CMD_DELAY; // If hibit set, delay follows args
			numArgs &= ~ST77XX::ST_CMD_DELAY;	 // Mask out delay bit
			transmit_blocking<Cmd>(cmd);
			while (numArgs--) {
				transmit_blocking<Data>(*addr++);
			}

			if (ms) {
				ms = *addr++; // Read post-command delay time (ms)
				if (ms == 255)
					ms = 500; // If 255, delay for 500 ms
				HAL_Delay(ms);
			}
		}
	}
};

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
		set_rotation(1); // ScreenConfT::rotation
	}

	void set_rotation(uint8_t m)
	{
		_rotation = m & 0b11;
		if (_rotation & 0b01) {
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

protected:
	int _rotation;
	int _width;
	int _height;
};
