#pragma once
#include "Adafruit_GFX_Library/Adafruit_GFX.h"
#include "conf/screen_conf.hh"
#include "drivers/pin.hh"
#include "drivers/spi.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"

class mmooo {};

class Screen : public MMScreenDriverT, Adafruit_GFX {
public:
	Screen(const MMScreenConf &conf)
		: Adafruit_GFX{240, 240}
		, MMScreenDriverT{conf.screen_SPI_conf}
		, window_height{MMScreenConf::width}
		, window_width{MMScreenConf::height}
	{}

	void init();
	void set_rotation(uint8_t m);

	virtual void drawPixel(int16_t x, int16_t y, uint16_t color) override
	{
		set_pos(x, y, 1, 1);
		transmit<Data>(color >> 8);
		transmit<Data>(color & 0xFF);
	}

	void demo();

private:
	int window_width;
	int window_height;
	int rotation;
	int _xstart;
	int _ystart;
	int _colstart;
	int _rowstart;
	int _width;
	int _height;

	void set_pos(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend);
	void init_display(const uint8_t *addr);

	void drawMockupBase();
	void draw_bar(uint16_t level, uint16_t x, uint16_t y, uint16_t col);
};

