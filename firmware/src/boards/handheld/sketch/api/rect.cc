#include "../api.hh"
#include "coords.hh"
#include "draw_state.hh"
#include "framebuffer.hh"

namespace Handheld
{

extern DrawState state_;

void rect(int x, int y, int w, int h) {
	convert_coords(state_.rect_mode, x, y, w, h);

	int x2 = x + w;
	int y2 = y + h;

	if (state_.transform_matrix.is_rotated()) {
		auto restore_shape_mode = state_.shape_mode;
		shapeMode(CoordMode::CORNER);
		beginShape();
		vertex(x, y);
		vertex(x2, y);
		vertex(x2, y2);
		vertex(x, y2);
		endShape(CLOSE);
		shapeMode(restore_shape_mode);
		return;
	}

	if (x >= (int)Handheld::width || y >= (int)Handheld::height || x2 < 0 || y2 < 0)
		return;

	if (state_.transform_matrix.is_transformed()) {
		float x1f = x;
		float y1f = y;
		float x2f = x2;
		float y2f = y2;
		state_.transform_matrix.transform(x1f, y1f);
		state_.transform_matrix.transform(x2f, y2f);
		x = std::round(x1f);
		y = std::round(y1f);
		x2 = std::round(x2f);
		y2 = std::round(y2f);
	}

	int sw = (state_.stroke_width > 0) ? std::max<int>(1, state_.stroke_width) : 0;

	// Calculate the start/stop for the stroke boundaries.
	// The fill portion is inside this.

	// Top and bottom edges:
	// For odd stroke width: draw more inner than outer on top
	//                       draw more outer than inner on bottom
	int stroke_top_start = y - sw / 2;
	int stroke_top_end = stroke_top_start + state_.stroke_width;
	int stroke_bottom_start = y2 - sw / 2;
	int stroke_bottom_end = stroke_bottom_start + state_.stroke_width;

	// Left edge: draw TL and BL corners, too
	// For odd stroke width, draw more inner than outer
	int stroke_left_start = x - sw / 2;
	int stroke_left_end = stroke_left_start + sw;

	// Right edge: draw TR and BR corners, too
	// For odd stroke width, draw more outer than inner
	int stroke_right_start = x2 - sw / 2;
	int stroke_right_end = stroke_right_start + sw;

	// Clamp after doing start/end calculations
	// or else height and width are not clipped properly
	auto clamp = [](int &a, int max) {
		a = std::clamp<int>(a, 0, max - 1);
	};
	clamp(stroke_top_start, Handheld::height);
	clamp(stroke_top_end, Handheld::height);
	clamp(stroke_bottom_start, Handheld::height);
	clamp(stroke_bottom_end, Handheld::height);

	clamp(stroke_left_start, Handheld::width);
	clamp(stroke_left_end, Handheld::width);
	clamp(stroke_right_start, Handheld::width);
	clamp(stroke_right_end, Handheld::width);

	// Draw fill
	if (state_.do_fill) {
		for (int col = stroke_left_end; col < stroke_right_start; col++) {
			draw_vert_line(col, stroke_top_end, stroke_bottom_start - 1, state_.fill);
		}
	}

	// Draw stroke
	if (state_.stroke_width > 0) {
		for (int sx = stroke_left_end; sx < stroke_right_start; sx++) {
			draw_vert_line(sx, stroke_top_start, stroke_top_end - 1, state_.stroke);
			draw_vert_line(sx, stroke_bottom_start, stroke_bottom_end - 1, state_.stroke);
		}

		for (int sx = stroke_left_start; sx < stroke_left_end; sx++) {
			draw_vert_line(sx, stroke_top_start, stroke_bottom_end - 1, state_.stroke);
		}

		for (int sx = stroke_right_start; sx < stroke_right_end; sx++) {
			draw_vert_line(sx, stroke_top_start, stroke_bottom_end - 1, state_.stroke);
		}
	}
}

} // namespace Handheld
