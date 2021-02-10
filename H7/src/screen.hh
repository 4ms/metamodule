#pragma once
// #include "Adafruit_ST7789.h"
#include "conf/screen_conf.hh"
#include "drivers/pin.hh"
#include "drivers/spi.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"

class mmooo {};

class Screen : MMScreenDriverT {
public:
	Screen(const MMScreenConf &conf)
		: MMScreenDriverT{conf.screen_SPI_conf}
		, window_height{MMScreenConf::width}
		, window_width{MMScreenConf::height}
	{}

	void init();
	void demo();
	void set_rotation(uint8_t m);

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
};

