#include "api.hh"
#include "conf/screen_buffer_conf.hh"
#include "sketch/sketch.hh"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <span>

#include "api/color_convert.hh"
#include "api/draw_state.hh"
#include "api/framebuffer.hh"

namespace Handheld
{

using namespace ProcessingAPI;

//
// Globals (requried for Processing API)
//

unsigned width = MetaModule::ScreenBufferConf::viewWidth;
unsigned height = MetaModule::ScreenBufferConf::viewHeight;

int mouseX = 0;
int mouseY = 0;

//
// Private internal state
//

DrawState state_{};

//
// API
//

void size(unsigned w, unsigned h) {
	//? Scale to fit?
}

void rectMode(CoordMode mode) {
	state_.rect_mode = mode;
}

void ellipseMode(CoordMode mode) {
	state_.ellipse_mode = mode;
}

void shapeMode(CoordMode mode) {
	state_.shape_mode = mode;
}

void noStroke() {
	state_.stroke_width = 0;
}

void stroke(float comp1, float comp2, float comp3) {
	float c1 = comp1 / state_.color_range_1;
	float c2 = comp2 / state_.color_range_2;
	float c3 = comp3 / state_.color_range_3;

	if (state_.color_mode == RGB) {
		state_.stroke = Color{c1, c2, c3};
	} else {
		state_.stroke = hsv_to_rgb(c1, c2, c3);
	}
	// Setting stroke color also enables stroking (default to 1px if not set)
	if (state_.stroke_width == 0)
		state_.stroke_width = 1.0f;
}

void stroke(float grey) {
	if (state_.color_mode == RGB) {
		stroke(grey, grey, grey);
	} else {
		stroke(0, 0, grey);
	}
}

void strokeWeight(float weight) {
	state_.stroke_width = weight;
}

void background(float comp1, float comp2, float comp3) {
	float c1 = comp1 / state_.color_range_1;
	float c2 = comp2 / state_.color_range_2;
	float c3 = comp3 / state_.color_range_3;

	auto color = (state_.color_mode == RGB) ? Color{c1, c2, c3} : hsv_to_rgb(c1, c2, c3);

	std::fill_n(buf(0, 0), width * height, color);
}

void background(float grey) {
	if (grey == 0) {
		std::memset(buffer.data(), 0, width * height * 2); //0.5ms

		// std::ranges::fill(buffer, 0); //2.9ms
	} else
		// FIXME: for HSV mode, should be 0, grey, 0?
		background(grey, grey, grey);
}

void fill(float comp1, float comp2, float comp3) {
	state_.do_fill = true;

	float c1 = comp1 / state_.color_range_1;
	float c2 = comp2 / state_.color_range_2;
	float c3 = comp3 / state_.color_range_3;

	if (state_.color_mode == RGB) {
		state_.fill = Color{c1, c2, c3};
	} else {
		state_.fill = hsv_to_rgb(c1, c2, c3);
	}
}

void fill(float grey) {
	if (state_.color_mode == RGB) {
		fill(grey, grey, grey);
	} else {
		fill(0, 0, grey);
	}
}

void noFill() {
	state_.do_fill = false;
}

} // namespace Handheld
