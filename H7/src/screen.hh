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
	void fillRect_slow(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
	{
		set_pos(x, y, x + w - 1, y + h - 1);
		for (int i = 0; i <= ((w) * (h)); i += 1) {
			transmit_data_32(color, color);
		}
	}
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

private:
	const int window_width;
	const int window_height;
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

struct Screen : public ScreenGFXAdaptor {

	Screen() {}

	void fill(Color c)
	{
		fillRect(0, 0, ScreenConfT::width, ScreenConfT::height, c.Rgb565());
	}
};
