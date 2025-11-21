#include "api.hh"
#include "conf/debug.hh"
#include "conf/screen_buffer_conf.hh"
#include "sketch/sketch.hh"
#include <cmath>
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
	bool do_fill = true;

	Color stroke = Colors565::White;
	float stroke_width = 0.f;

	Color bg = Colors565::Black;

	CoordMode rect_mode = CORNER;
	CoordMode shape_mode = CORNER;
	CoordMode ellipse_mode = CORNER;
};

DrawState state_{};

static Color hsv_to_rgb(float h01, float s01, float v01);

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

void strokeWeight(float weight) {
	state_.stroke_width = weight;
}

void background(float color) {
	state_.bg = color;
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

void noFill() {
	state_.do_fill = false;
}

static inline auto buf(unsigned x, unsigned y) {
	return buffer.data() + x * height + y;
}

void rect(int x, int y, unsigned w, unsigned h) {
	if (x >= (int)width || y >= (int)height)
		return;

	// Store original bounds for stroke
	int orig_x = x;
	int orig_y = y;
	int orig_w = w;
	int orig_h = h;

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

	// Draw fill
	if (state_.do_fill) {
		for (int col = x; col < x2; col++) {
			// Fill a column (buffer is rotated 90 degrees so columns of pixels are consectutive in memory)
			std::fill_n(buf(col, y), h, state_.fill);
		}
	}

	// Draw stroke
	if (state_.stroke_width > 0) {
		int sw = std::max(1, (int)state_.stroke_width);

		// Top edge
		for (int i = 0; i < sw && orig_y + i < (int)height; i++) {
			int sy = orig_y + i;
			if (sy >= 0) {
				int sx_start = std::max(0, orig_x);
				int sx_end = std::min((int)width, orig_x + (int)orig_w);
				for (int sx = sx_start; sx < sx_end; sx++) {
					*buf(sx, sy) = state_.stroke;
				}
			}
		}

		// Bottom edge
		for (int i = 0; i < sw && orig_y + (int)orig_h - sw + i < (int)height; i++) {
			int sy = orig_y + orig_h - sw + i;
			if (sy >= 0 && sy < (int)height) {
				int sx_start = std::max(0, orig_x);
				int sx_end = std::min((int)width, orig_x + (int)orig_w);
				for (int sx = sx_start; sx < sx_end; sx++) {
					*buf(sx, sy) = state_.stroke;
				}
			}
		}

		// Left edge
		for (int i = 0; i < sw && orig_x + i < (int)width; i++) {
			int sx = orig_x + i;
			if (sx >= 0) {
				int sy_start = std::max(0, orig_y);
				int sy_end = std::min((int)height, orig_y + (int)orig_h);
				for (int sy = sy_start; sy < sy_end; sy++) {
					*buf(sx, sy) = state_.stroke;
				}
			}
		}

		// Right edge
		for (int i = 0; i < sw && orig_x + (int)orig_w - sw + i < (int)width; i++) {
			int sx = orig_x + orig_w - sw + i;
			if (sx >= 0 && sx < (int)width) {
				int sy_start = std::max(0, orig_y);
				int sy_end = std::min((int)height, orig_y + (int)orig_h);
				for (int sy = sy_start; sy < sy_end; sy++) {
					*buf(sx, sy) = state_.stroke;
				}
			}
		}
	}
}

void ellipse(int x, int y, unsigned w, unsigned h) {
	// Convert parameters based on ellipse mode
	int cx, cy;
	float rx, ry;

	switch (state_.ellipse_mode) {
		case CORNER:
			// (x, y) is top-left corner, w and h are width and height
			cx = x + w / 2;
			cy = y + h / 2;
			rx = w / 2.0f;
			ry = h / 2.0f;
			break;
		case CENTER:
			// (x, y) is center, w and h are width and height
			cx = x;
			cy = y;
			rx = w / 2.0f;
			ry = h / 2.0f;
			break;
		case RADIUS:
			// (x, y) is center, w and h are radii
			cx = x;
			cy = y;
			rx = w;
			ry = h;
			break;
		case CORNERS:
			// (x, y) is one corner, w and h are opposite corner coordinates
			cx = (x + (int)w) / 2;
			cy = (y + (int)h) / 2;
			rx = std::abs((int)w - x) / 2.0f;
			ry = std::abs((int)h - y) / 2.0f;
			break;
	}

	// Skip if ellipse is outside screen bounds
	if (cx + rx < 0 || cx - rx >= (int)width || cy + ry < 0 || cy - ry >= (int)height)
		return;

	// Skip if ellipse is too small
	if (rx < 0.5f || ry < 0.5f)
		return;

	// For each y coordinate, calculate the x coordinates where the ellipse intersects
	int y_start = std::max(0, (int)(cy - ry));
	int y_end = std::min((int)height - 1, (int)(cy + ry));

	// Scan-line fill algorithm
	if (state_.do_fill) {
		for (int scan_y = y_start; scan_y <= y_end; scan_y++) {
			// Calculate distance from center
			float dy = scan_y - cy;

			// Calculate x offset using ellipse equation: (x/rx)^2 + (y/ry)^2 = 1
			// Solving for x: x = rx * sqrt(1 - (y/ry)^2)
			float y_ratio = dy / ry;
			float discriminant = 1.0f - y_ratio * y_ratio;

			if (discriminant < 0)
				continue;

			float dx = rx * std::sqrt(discriminant);

			// Calculate start and end x coordinates for this scan line
			int x_start = std::max(0, (int)(cx - dx));
			int x_end = std::min((int)width - 1, (int)(cx + dx));

			// Fill the horizontal line
			for (int scan_x = x_start; scan_x <= x_end; scan_x++) {
				*buf(scan_x, scan_y) = state_.fill;
			}
		}
	}

	// Draw stroke
	if (state_.stroke_width > 0) {
		float sw = state_.stroke_width;

		// Draw stroke using inner and outer ellipse
		// Outer ellipse has the original radii, inner has radii reduced by stroke width
		float rx_inner = std::max(0.0f, rx - sw);
		float ry_inner = std::max(0.0f, ry - sw);

		for (int scan_y = y_start; scan_y <= y_end; scan_y++) {
			float dy = scan_y - cy;

			// Outer ellipse
			float y_ratio_outer = dy / ry;
			float discriminant_outer = 1.0f - y_ratio_outer * y_ratio_outer;

			if (discriminant_outer < 0)
				continue;

			float dx_outer = rx * std::sqrt(discriminant_outer);

			// Inner ellipse (if it exists)
			float dx_inner = 0;
			if (rx_inner > 0 && ry_inner > 0) {
				float y_ratio_inner = dy / ry_inner;
				float discriminant_inner = 1.0f - y_ratio_inner * y_ratio_inner;

				if (discriminant_inner > 0) {
					dx_inner = rx_inner * std::sqrt(discriminant_inner);
				}
			}

			// Draw left stroke edge
			int x_outer_left = std::max(0, (int)(cx - dx_outer));
			int x_inner_left = std::max(0, (int)(cx - dx_inner));
			for (int scan_x = x_outer_left; scan_x < x_inner_left && scan_x < (int)width; scan_x++) {
				*buf(scan_x, scan_y) = state_.stroke;
			}

			// Draw right stroke edge
			int x_inner_right = std::min((int)width - 1, (int)(cx + dx_inner));
			int x_outer_right = std::min((int)width - 1, (int)(cx + dx_outer));
			for (int scan_x = x_inner_right + 1; scan_x <= x_outer_right; scan_x++) {
				*buf(scan_x, scan_y) = state_.stroke;
			}
		}
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
