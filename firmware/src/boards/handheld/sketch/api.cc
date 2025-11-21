#include "api.hh"
#include "conf/debug.hh"
#include "conf/screen_buffer_conf.hh"
#include "sketch/sketch.hh"
#include <cstring>
#include <span>

namespace Handheld
{
//
// Engine interface
//
static std::span<Color> buffer{};

void set_buffer(std::span<Color> buf) {
	buffer = buf;
}

//
// Internal State
//
struct DrawState {
	ColorMode color_mode = RGB;
	float color_range_1 = 255;
	float color_range_2 = 255;
	float color_range_3 = 255;

	Color fill = Colors565::White;

	Color stroke = Colors565::White;
	float stroke_width = 0.f;

	Color bg = Colors565::Black;

	CoordMode rect_mode = CORNER;
	CoordMode ellipse_mode = CORNER;
};

DrawState state_{};

//
// Globals
//

unsigned width = MetaModule::ScreenBufferConf::viewWidth;
unsigned height = MetaModule::ScreenBufferConf::viewHeight;

int mouseX = 0;
int mouseY = 0;
float accelX = 0;
float accelY = 0;
float accelZ = 0;

//
// API
//

void size(unsigned w, unsigned h) {
	//? Scale to fit?
}

void colorMode(ColorMode mode, float comp1, float comp2, float comp3) {
	state_.color_mode = mode;
	state_.color_range_1 = comp1;
	state_.color_range_2 = comp2;
	state_.color_range_3 = comp3;
}

void rectMode(CoordMode mode) {
	state_.rect_mode = mode;
}

void ellipseMode(CoordMode mode) {
	state_.ellipse_mode = mode;
}

void shapeMode(CoordMode mode) {
	state_.rect_mode = mode;
	state_.ellipse_mode = mode;
}

void noStroke() {
	state_.stroke_width = 0;
}

void background(float color) {
	state_.bg = color;
}

static Color hsv_to_rgb(float h01, float s01, float v01);

void fill(float comp1, float comp2, float comp3) {
	float c1 = comp1 / state_.color_range_1;
	float c2 = comp2 / state_.color_range_2;
	float c3 = comp3 / state_.color_range_3;

	if (state_.color_mode == RGB) {
		state_.fill = Color{c1, c2, c3};
	} else {
		state_.fill = hsv_to_rgb(c1, c2, c3);
	}
}

static inline auto buf(unsigned x, unsigned y) {
	return buffer.data() + x * height + y;
}

void rect(int x, int y, unsigned w, unsigned h) {
	if (x >= (int)width || y >= (int)height)
		return;

	// clamp right side
	auto x2 = std::min<int>(x + w, width);

	// clamp bottom side
	h = std::min(y + h, height - 1) - y;

	// clamp left side
	if (x < 0)
		x = 0;

	// clamp top side
	if (y < 0) {
		h += y;
		y = 0;
	}

	for (int col = x; col < x2; col++) {
		// Fill a column (buffer is rotated 90 degrees so columns of pixels are consectutive in memory)
		// std::fill_n(buffer.data() + col * height + y, h, state_.fill);
		std::fill_n(buf(col, y), h, state_.fill);
	}
}

Color hsv_to_rgb(float h01, float s01, float v01) {
	// Convert to 8-bit normalized values
	uint16_t h = h01 * 255;
	uint8_t s = s01 * 255;
	uint8_t v = v01 * 255;

	// greyscale
	if (s == 0) {
		return {v, v, v};
	}

	uint8_t region = h / 43;
	uint8_t remainder = (h - (region * 43)) * 6;

	uint8_t p = (v * (255 - s)) >> 8;
	uint8_t q = (v * (255 - ((s * remainder) >> 8))) >> 8;
	uint8_t t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

	uint8_t r, g, b;
	switch (region) {
		case 0:
			r = v;
			g = t;
			b = p;
			break;
		case 1:
			r = q;
			g = v;
			b = p;
			break;
		case 2:
			r = p;
			g = v;
			b = t;
			break;
		case 3:
			r = p;
			g = q;
			b = v;
			break;
		case 4:
			r = t;
			g = p;
			b = v;
			break;
		default:
			r = v;
			g = p;
			b = q;
			break;
	}

	return {r, g, b};
}

} // namespace Handheld
