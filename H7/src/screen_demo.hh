#pragma once
#include "screen.hh"

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
