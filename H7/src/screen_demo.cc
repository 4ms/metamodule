#include "screen_demo.hh"
#include "Fonts/FreeSans12pt7b.h"
#include "Fonts/FreeSansBold12pt7b.h"
#include "Fonts/FreeSansBold18pt7b.h"
#include "drivers/spi_screen_ST77XX.hh"

void ScreenDemo::demo()
{
	fillRect(0, 0, 240, 240, ST77XX::BLACK);
	setFont(&FreeSansBold18pt7b);
	setTextColor(ST77XX::WHITE);
	setTextSize(1);
	setCursor(2, 200);
	print("MetaModule");

	drawMockupBase();
}

void ScreenDemo::draw_bar(uint16_t level, uint16_t x, uint16_t y, uint16_t col)
{
	fillRect(x + level, y, width() / 2 - 10 - level, 12, ST77XX::BLACK);
	fillRect(x, y, level, 12, col);
}

void ScreenDemo::drawMockupBase()
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
	setTextColor(bar_colors[0]);
	getTextBounds("Freq 1", 0, 0, &x, &y, &w, &h);
	setCursor(5, h + cur_y);
	print("Freq 1");
	bar_x[0] = 5;
	bar_y[0] = cur_y + h + 5;
	draw_bar(75, bar_x[0], bar_y[0], bar_colors[0]);

	cur_y += h + 25;

	setFont(&FreeSansBold12pt7b);
	setTextColor(bar_colors[1]);
	getTextBounds("Res (Q)", 0, 0, &x, &y, &w, &h);
	setCursor(5, h + cur_y);
	print("Res (Q)");
	bar_x[1] = 5;
	bar_y[1] = cur_y + h + 5;
	draw_bar(75, 5, cur_y + h + 5, bar_colors[1]);

	cur_y = line1;

	setFont(&FreeSansBold12pt7b);
	setTextColor(bar_colors[2]);
	getTextBounds("Morph", 0, 0, &x, &y, &w, &h);
	setCursor(width() - 5 - w, h + cur_y);
	print("Morph");
	bar_x[2] = width() / 2 + 5;
	bar_y[2] = cur_y + h + 5;
	draw_bar(60, width() / 2 + 5, cur_y + h + 5, bar_colors[2]);

	cur_y += h + 25;

	setFont(&FreeSansBold12pt7b);
	setTextColor(bar_colors[3]);
	getTextBounds("Level", 0, 0, &x, &y, &w, &h);
	setCursor(width() - 5 - w, h + cur_y);
	print("Level");
	bar_x[3] = width() / 2 + 5;
	bar_y[3] = cur_y + h + 5;
	draw_bar(95, width() / 2 + 5, cur_y + h + 5, bar_colors[3]);
}

