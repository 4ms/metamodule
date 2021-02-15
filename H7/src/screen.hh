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
// Todo: why does making Screen a template class over <ScreenConT>, remove ability to access SpiScreenDriver base class?
// template<typename ScreenConfT>

class Screen : public SpiScreenDriver<ScreenConfT>, public Adafruit_GFX {
public:
	Screen()
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
				if ((window_width == 135) && (window_height == 240)) {
					_xstart = _colstart - 1;
					_ystart = _rowstart;
				} else {
					_xstart = 0;
					_ystart = 0;
				}
				_width = window_width;
				_height = window_height;
				break;
			case 3:
				madctl = ST77XX::MADCTL_MX | ST77XX::MADCTL_MV | ST77XX::MADCTL_RGB;
				if ((window_width == 135) && (window_height == 240)) {
					_xstart = _rowstart;
					_ystart = _colstart;
				} else {
					_xstart = 0;
					_ystart = 0;
				}
				_height = window_width;
				_width = window_height;
				break;
		}
		transmit<Cmd>(ST77XX::MADCTL);
		transmit<Data>(madctl);
	}

	virtual void drawPixel(int16_t x, int16_t y, uint16_t color) override
	{
		set_pos(x, y, 1, 1);
		transmit<Data>(color >> 8);
		transmit<Data>(color & 0xFF);
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
		transmit<Data>(Xstart >> 8);
		transmit<Data>(Xstart);
		transmit<Data>(Xend >> 8);
		transmit<Data>(Xend);

		transmit<Cmd>(ST77XX::RASET);
		transmit<Data>(Ystart >> 8);
		transmit<Data>(Ystart);
		transmit<Data>(Yend >> 8);
		transmit<Data>(Yend);

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

struct ScreenDemo : public Screen {
	ScreenDemo() {}

	uint16_t bar_x[4], bar_y[4];
	static constexpr uint16_t bar_colors[4] = {
		Colors::orange.Rgb565(),
		Colors::pink.Rgb565(),
		Colors::purple.Rgb565(),
		Colors::green.Rgb565(),
	};
	// Color{160, 224, 96}.Rgb565(),
	// Color{96, 160, 224}.Rgb565(),
	// Color{240, 48, 96}.Rgb565(),
	// Color{96, 48, 255}.Rgb565(),

	void demo();
	void drawMockupBase();
	void draw_bar(uint16_t level, uint16_t x, uint16_t y, uint16_t col);
};
