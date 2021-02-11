#define PROGMEM
#include "screen.hh"
#include "Fonts/FreeSans12pt7b.h"
#include "Fonts/FreeSansBold12pt7b.h"
#include "Fonts/FreeSansBold18pt7b.h"
#include "drivers/spi_screen_ST77XX.hh"

void Screen::init()
{
	if ((window_width == 240) && (window_height == 240)) { // 1.3" and 1.54" displays
		_colstart = 0;
		_rowstart = 80;
	} else if ((window_width == 135) && (window_height == 240)) { // 1.13" display
		_colstart = 53;
		_rowstart = 40;
	} else {
		_colstart = 0;
		_rowstart = 0;
	}

	init_display(generic_st7789);
	set_rotation(1);
}

void Screen::demo()
{
	fillRect(0, 0, 240, 240, ST77XX::BLACK);
	setFont(&FreeSansBold18pt7b);
	setTextColor(ST77XX::WHITE);
	setTextSize(1);
	setCursor(2, 200);
	print("MetaModule");

	drawMockupBase();
}

class Rgb {
	uint16_t col;

public:
	Rgb(uint8_t r, uint8_t g, uint8_t b)
		: col(((r & 0b011111) << 11) | ((g & 0b111111) << 5) | ((b & 0b011111)))
	{}
	uint16_t operator()()
	{
		return col;
	}
};

static uint16_t bar_x[4], bar_y[4];
static uint16_t col[4] = {
	Rgb{20, 56, 12}(),
	Rgb{12, 40, 28}(),
	Rgb{30, 12, 12}(),
	Rgb{12, 12, 31}(),
};

void Screen::draw_bar(uint16_t level, uint16_t x, uint16_t y, uint16_t col)
{
	fillRect(x + level, y, width() / 2 - 10 - level, 12, ST77XX::BLACK);
	fillRect(x, y, level, 12, col);
}

void Screen::drawMockupBase()
{
	setTextWrap(false);

	uint16_t cur_y = 0;

	int16_t x, y;
	uint16_t w, h;

	setFont(&FreeSansBold18pt7b);
	setTextColor(ST77XX::WHITE);
	getTextBounds("Resonator", 0, 0, &x, &y, &w, &h);
	setCursor((width() - w) / 2, h);
	print("Resonator");

	cur_y += h + 15;
	uint16_t line1 = cur_y;

	setFont(&FreeSansBold12pt7b);
	setTextColor(col[0]);
	getTextBounds("Freq 1", 0, 0, &x, &y, &w, &h);
	setCursor(5, h + cur_y);
	print("Freq 1");
	bar_x[0] = 5;
	bar_y[0] = cur_y + h + 5;
	draw_bar(75, bar_x[0], bar_y[0], col[0]);

	cur_y += h + 25;

	setFont(&FreeSansBold12pt7b);
	setTextColor(col[1]);
	getTextBounds("Res (Q)", 0, 0, &x, &y, &w, &h);
	setCursor(5, h + cur_y);
	print("Res (Q)");
	bar_x[1] = 5;
	bar_y[1] = cur_y + h + 5;
	draw_bar(75, 5, cur_y + h + 5, col[1]);

	cur_y = line1;

	setFont(&FreeSansBold12pt7b);
	setTextColor(col[2]);
	getTextBounds("Morph", 0, 0, &x, &y, &w, &h);
	setCursor(width() - 5 - w, h + cur_y);
	print("Morph");
	bar_x[2] = width() / 2 + 5;
	bar_y[2] = cur_y + h + 5;
	draw_bar(60, width() / 2 + 5, cur_y + h + 5, col[2]);

	cur_y += h + 25;

	setFont(&FreeSansBold12pt7b);
	setTextColor(col[3]);
	getTextBounds("Level", 0, 0, &x, &y, &w, &h);
	setCursor(width() - 5 - w, h + cur_y);
	print("Level");
	bar_x[3] = width() / 2 + 5;
	bar_y[3] = cur_y + h + 5;
	draw_bar(95, width() / 2 + 5, cur_y + h + 5, col[3]);
}

// Todo re-write as just a sequence of commands with delays, seriously...
void Screen::init_display(const uint8_t *addr)
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
void Screen::set_rotation(uint8_t m)
{
	uint8_t madctl = 0;

	rotation = m & 3;

	switch (rotation) {
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

void Screen::set_pos(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
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

