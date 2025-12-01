#include "../api.hh"
#include "coords.hh"
#include "draw_state.hh"
#include "framebuffer.hh"

namespace Handheld
{

extern DrawState state_;

void ellipse(int x, int y, int w, int h) {
	if (!state_.do_fill && state_.stroke_width == 0)
		return;

	convert_coords(state_.ellipse_mode, x, y, w, h);

	int x2 = x + w;
	int y2 = y + h;

	if (state_.transform_matrix.is_rotated()) {
		// Convert ellipse to polygon for rotation support
		float cx = x + w / 2.f;
		float cy = y + h / 2.f;
		float rx = w / 2.f;
		float ry = h / 2.f;

		unsigned num_segments = state_.transform_resolution;
		float angle_step = TWO_PI / num_segments;

		auto restore_shape_mode = state_.shape_mode;
		shapeMode(CoordMode::CORNER);
		beginShape();

		for (unsigned i = 0; i < num_segments; i++) {
			float angle = i * angle_step;
			float px = cx + rx * std::cos(angle);
			float py = cy + ry * std::sin(angle);
			vertex(px, py);
		}

		endShape(CLOSE);
		shapeMode(restore_shape_mode);
		return;
	}

	if (x >= (int)Handheld::width || y >= (int)Handheld::height || x2 < 0 || y2 < 0)
		return;

	if (state_.transform_matrix.is_transformed()) {
		state_.transform_matrix.transform(x, y);
		state_.transform_matrix.transform(x2, y2);
	}

	float cx = (x + x2) / 2.f;
	float cy = (y + y2) / 2.f;

	float sw = (state_.stroke_width > 0) ? std::max<int>(1, state_.stroke_width) : 0;

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

	float inner_rx = (stroke_right_start - stroke_left_end) / 2.f;
	float inner_ry = (stroke_bottom_start - stroke_top_end) / 2.f;
	float outer_rx = sw + inner_rx;
	float outer_ry = sw + inner_ry;

	int unclamped_bounds_x = stroke_left_start;
	int unclamped_bounds_x2 = stroke_right_end;

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

	// Calculate the top and bottom y coordinates for an x coordinate of an ellipse with radii rx, ry
	auto ellipse_column = [&cx, &cy](int scan_x, float rx, float ry) {
		float dx = float(scan_x) - cx;

		// Calculate y offset using ellipse equation: (y/yx)^2 + (x/rx)^2 = 1
		// dy = ry * sqrt(1 - (x/rx)^2)
		// cy - dy < y < cy + dy
		float x_ratio = dx / rx;
		float discriminant = 1.0f - x_ratio * x_ratio;

		if (discriminant < 0) {
			return std::make_pair(-1, -1);
		}

		float dy = ry * std::sqrt(discriminant);

		// Calculate start and end y coordinates for this vert line
		int y_start = std::clamp<int>(cy - dy + 0.5f, 0, Handheld::height - 1);
		int y_end = std::clamp<int>(cy + dy + 0.5f, 0, Handheld::height) - 1;
		if (y_end < y_start)
			return std::make_pair(y_end, y_start);
		else
			return std::make_pair(y_start, y_end);
	};

	// printf("cx:%g cy:%g\n", cx, cy);
	// printf("inner_r: %g,%g, outer_r: %g,%g\n", inner_rx, inner_ry, outer_rx, outer_ry);
	// printf("stroke_left:%d->%d, stroke_right:%d->%d\n",
	// 	   stroke_left_start,
	// 	   stroke_left_end,
	// 	   stroke_right_start,
	// 	   stroke_right_end);

	auto center_x = std::clamp<int>(cx + 0.5f, 0, Handheld::width);

	for (int scan_x = unclamped_bounds_x; scan_x < center_x; scan_x++) {
		int mirror_x = unclamped_bounds_x2 - (scan_x - unclamped_bounds_x) - 1;
		bool draw_mirror = mirror_x != scan_x;

		auto [y_outer_start, y_outer_end] = ellipse_column(scan_x, outer_rx, outer_ry);
		if (y_outer_start < 0)
			continue;

		if (scan_x >= stroke_left_end && scan_x <= stroke_right_start) {
			//TODO: if inner_rx == outer_rx and inner_ry== outer_ry, then y_inner_* = y_outer_*
			auto [y_inner_start, y_inner_end] = ellipse_column(scan_x, inner_rx, inner_ry);
			bool inner_valid = y_inner_start >= 0;

			// printf("x: %d and %d: outer_y:%d->%d inner_y:%d->%d\n",
			// 	   scan_x,
			// 	   mirror_x,
			// 	   y_outer_start,
			// 	   y_outer_end,
			// 	   y_inner_start,
			// 	   y_inner_end);

			if (inner_valid) {
				// Middle of ellipse: bottom and top stroke, and fill
				if (state_.do_fill) {
					draw_vert_line(scan_x, y_inner_start, y_inner_end, state_.fill);
					if (draw_mirror)
						draw_vert_line(mirror_x, y_inner_start, y_inner_end, state_.fill);
				}

				if (state_.stroke_width != 0) {
					draw_vert_line(scan_x, y_outer_start, y_inner_start - 1, state_.stroke);
					if (draw_mirror)
						draw_vert_line(mirror_x, y_outer_start, y_inner_start - 1, state_.stroke);
					draw_vert_line(scan_x, y_inner_end + 1, y_outer_end, state_.stroke);
					if (draw_mirror)
						draw_vert_line(mirror_x, y_inner_end + 1, y_outer_end, state_.stroke);
				}

				continue;
			}
		}
		// printf("x: %d and %d: outer_y:%d->%d\n", scan_x, mirror_x, y_outer_start, y_outer_end);

		// Left and right ends of ellipse: stroke only
		if (state_.stroke_width != 0) {
			draw_vert_line(scan_x, y_outer_start, y_outer_end, state_.stroke);
			if (draw_mirror)
				draw_vert_line(mirror_x, y_outer_start, y_outer_end, state_.stroke);
		}
	}
}
} // namespace Handheld
