#include "api.hh"
#include "conf/debug.hh"
#include "conf/screen_buffer_conf.hh"
#include "sketch/sketch.hh"
#include "util/math.hh"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <span>
#include <stack>
#include <vector>

namespace Handheld
{
//
// Engine interface
//
static std::span<Color> buffer{};

static_assert(sizeof(Color) == 2);

void set_buffer(std::span<Color> buf) {
	buffer = buf;
}

static inline auto buf(unsigned x, unsigned y) {
	return buffer.data() + x * height + y;
}

//
// Internal State
//
struct Vertex {
	float x, y;
};

// 2D affine transformation matrix
// | a  c  tx |
// | b  d  ty |
struct Matrix2D {
	float a, b, c, d, tx, ty;

	// Identity matrix
	Matrix2D()
		: a(1)
		, b(0)
		, c(0)
		, d(1)
		, tx(0)
		, ty(0) {
	}

	// Transform a point
	void transform(float &x, float &y) const {
		float x_new = a * x + c * y + tx;
		float y_new = b * x + d * y + ty;
		x = x_new;
		y = y_new;
	}

	// Multiply this matrix by another (this = this * other)
	void multiply(const Matrix2D &other) {
		float new_a = a * other.a + c * other.b;
		float new_b = b * other.a + d * other.b;
		float new_c = a * other.c + c * other.d;
		float new_d = b * other.c + d * other.d;
		float new_tx = a * other.tx + c * other.ty + tx;
		float new_ty = b * other.tx + d * other.ty + ty;

		a = new_a;
		b = new_b;
		c = new_c;
		d = new_d;
		tx = new_tx;
		ty = new_ty;
	}

	// Apply translation
	void translate(float dx, float dy) {
		Matrix2D trans;
		trans.tx = dx;
		trans.ty = dy;
		multiply(trans);
	}

	// Apply rotation (angle in radians)
	void rotate(float angle) {
		Matrix2D rot;
		rot.a = std::cos(angle);
		rot.b = std::sin(angle);
		rot.c = -std::sin(angle);
		rot.d = std::cos(angle);
		multiply(rot);
	}
};

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

	std::vector<Vertex> vertices;

	Matrix2D transform_matrix;
	std::stack<Matrix2D> matrix_stack;
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

void background(float comp1, float comp2, float comp3) {
	float c1 = comp1 / state_.color_range_1;
	float c2 = comp2 / state_.color_range_2;
	float c3 = comp3 / state_.color_range_3;

	auto color = (state_.color_mode == RGB) ? Color{c1, c2, c3} : hsv_to_rgb(c1, c2, c3);

	std::fill_n(buf(0, 0), width * height, color);
}

void background(float grey) {
	if (grey == 0)
		std::memset(buffer.data(), 0, width * height * 2);
	else
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

void noFill() {
	state_.do_fill = false;
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
		default:
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

void beginShape() {
	state_.vertices.clear();
}

void vertex(float x, float y) {
	// Apply current transformation matrix
	state_.transform_matrix.transform(x, y);
	state_.vertices.push_back({x, y});
}

// Helper function to draw a line between two points (for stroke)
static void draw_line(int x0, int y0, int x1, int y1, Color color) {
	// Bresenham's line algorithm
	int dx = std::abs(x1 - x0);
	int dy = std::abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;

	while (true) {
		// Draw pixel if within bounds
		if (x0 >= 0 && x0 < (int)width && y0 >= 0 && y0 < (int)height) {
			*buf(x0, y0) = color;
		}

		if (x0 == x1 && y0 == y1)
			break;

		int e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}

void endShape(ShapeMode mode) {
	if (state_.vertices.size() < 2)
		return;

	bool closed = (mode == CLOSE);
	size_t num_vertices = state_.vertices.size();

	// Draw fill using scan-line algorithm
	if (state_.do_fill && num_vertices >= 3) {
		// Find bounding box
		float min_y = state_.vertices[0].y;
		float max_y = state_.vertices[0].y;
		for (const auto &v : state_.vertices) {
			min_y = std::min(min_y, v.y);
			max_y = std::max(max_y, v.y);
		}

		int y_start = std::max(0, (int)min_y);
		int y_end = std::min((int)height - 1, (int)max_y);

		// For each scan line
		for (int scan_y = y_start; scan_y <= y_end; scan_y++) {
			std::vector<float> intersections;

			// Find intersections with polygon edges
			for (size_t i = 0; i < num_vertices; i++) {
				size_t j = (i + 1) % num_vertices;
				if (!closed && j == 0)
					break; // Don't connect last to first if open

				const Vertex &v1 = state_.vertices[i];
				const Vertex &v2 = state_.vertices[j];

				// Check if edge crosses scan line
				if ((v1.y <= scan_y && v2.y > scan_y) || (v2.y <= scan_y && v1.y > scan_y)) {
					// Calculate intersection x coordinate
					float t = (scan_y - v1.y) / (v2.y - v1.y);
					float x_intersect = v1.x + t * (v2.x - v1.x);
					intersections.push_back(x_intersect);
				}
			}

			// Sort intersections
			std::sort(intersections.begin(), intersections.end());

			// Fill between pairs of intersections
			for (size_t i = 0; i + 1 < intersections.size(); i += 2) {
				int x_start = std::max(0, (int)intersections[i]);
				int x_end = std::min((int)width - 1, (int)intersections[i + 1]);

				for (int x = x_start; x <= x_end; x++) {
					*buf(x, scan_y) = state_.fill;
				}
			}
		}
	}

	// Draw stroke
	if (state_.stroke_width > 0) {
		// Draw lines between consecutive vertices
		for (size_t i = 0; i < num_vertices - 1; i++) {
			int x0 = (int)state_.vertices[i].x;
			int y0 = (int)state_.vertices[i].y;
			int x1 = (int)state_.vertices[i + 1].x;
			int y1 = (int)state_.vertices[i + 1].y;

			draw_line(x0, y0, x1, y1, state_.stroke);
		}

		// Close the shape if requested
		if (closed && num_vertices >= 2) {
			int x0 = (int)state_.vertices[num_vertices - 1].x;
			int y0 = (int)state_.vertices[num_vertices - 1].y;
			int x1 = (int)state_.vertices[0].x;
			int y1 = (int)state_.vertices[0].y;

			draw_line(x0, y0, x1, y1, state_.stroke);
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

void pushMatrix() {
	state_.matrix_stack.push(state_.transform_matrix);
}

void popMatrix() {
	if (!state_.matrix_stack.empty()) {
		state_.transform_matrix = state_.matrix_stack.top();
		state_.matrix_stack.pop();
	}
}

void translate(float x, float y) {
	state_.transform_matrix.translate(x, y);
}

void rotate(float angle) {
	state_.transform_matrix.rotate(angle);
}

} // namespace Handheld
