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
		// Not supported. FIXME... calculate a poly shape?
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

	float cx = (x + x2) / 2.f;
	float cy = (y + y2) / 2.f;

	// Calculate the top and bottom y coordinates for the x column of an ellipse with radii rx, ry
	auto ellipse_col = [&cx, &cy](int scan_x, float rx, float ry) {
		float dx = scan_x - cx;

		// Calculate y offset using ellipse equation: (y/yx)^2 + (x/rx)^2 = 1
		// dy = ry * sqrt(1 - (x/rx)^2)
		// cy - dy < y < cy + dy
		float x_ratio = dx / rx;
		float discriminant = 1.0f - x_ratio * x_ratio;

		if (discriminant < 0)
			return std::make_pair(0, 0);

		float dy = ry * std::sqrt(discriminant);

		// Calculate start and end y coordinates for this vert line
		int y_start = std::clamp<int>(cy - dy, 0, Handheld::height - 1);
		int y_end = std::clamp<int>(cy + dy, 0, Handheld::height - 1);
		return std::make_pair(y_start, y_end);
	};

	for (int scan_x = stroke_left_start; scan_x < stroke_right_end; scan_x++) {
		auto [y_inner_start, y_inner_end] = ellipse_col(scan_x, inner_rx, inner_ry);
		auto [y_outer_start, y_outer_end] = ellipse_col(scan_x, outer_rx, outer_ry);

		if (state_.do_fill && scan_x >= stroke_left_end && scan_x < stroke_right_start) {
			// do fill
			draw_vert_line(scan_x, y_inner_start, y_inner_end, state_.fill);

			if (state_.stroke_width >= 1) {
				draw_vert_line(scan_x, y_outer_start, y_inner_start, state_.stroke);
				draw_vert_line(scan_x, y_inner_end, y_outer_end, state_.stroke);
			}
		}
	}

	// Draw stroke (centered on edge)
	if (state_.stroke_width > 0) {

		// 	// Expand scan range to cover the outer ellipse
		// 	int stroke_y_start = std::max(0, (int)(cy - ry_outer));
		// 	int stroke_y_end = std::min((int)height - 1, (int)(cy + ry_outer));

		// 	for (int scan_y = stroke_y_start; scan_y <= stroke_y_end; scan_y++) {
		// 		float dy = scan_y - cy;

		// 		// Outer ellipse
		// 		float y_ratio_outer = dy / ry_outer;
		// 		float discriminant_outer = 1.0f - y_ratio_outer * y_ratio_outer;

		// 		if (discriminant_outer < 0)
		// 			continue;

		// 		float dx_outer = rx_outer * std::sqrt(discriminant_outer);

		// 		// Inner ellipse (if it exists)
		// 		float dx_inner = 0;
		// 		if (rx_inner > 0 && ry_inner > 0) {
		// 			float y_ratio_inner = dy / ry_inner;
		// 			float discriminant_inner = 1.0f - y_ratio_inner * y_ratio_inner;

		// 			if (discriminant_inner > 0) {
		// 				dx_inner = rx_inner * std::sqrt(discriminant_inner);
		// 			}
		// 		}

		// 		// Draw left stroke edge
		// 		int x_outer_left = std::max(0, (int)(cx - dx_outer));
		// 		int x_inner_left = std::max(0, (int)(cx - dx_inner));
		// 		for (int scan_x = x_outer_left; scan_x <= x_inner_left && scan_x < (int)width; scan_x++) {
		// 			*buf(scan_x, scan_y) = state_.stroke;
		// 		}

		// 		// Draw right stroke edge
		// 		int x_inner_right = std::min((int)width - 1, (int)(cx + dx_inner));
		// 		int x_outer_right = std::min((int)width - 1, (int)(cx + dx_outer));
		// 		for (int scan_x = x_inner_right + 1; scan_x <= x_outer_right; scan_x++) {
		// 			*buf(scan_x, scan_y) = state_.stroke;
		// 		}
		// 	}
	}
}
} // namespace Handheld
