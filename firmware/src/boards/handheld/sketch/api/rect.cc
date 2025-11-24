#include "../api.hh"
#include "draw_state.hh"
#include "framebuffer.hh"

namespace Handheld
{

extern DrawState state_;

void rect(int x, int y, int w, int h) {
	// Convert parameters based on rect mode
	int rect_x, rect_y;
	unsigned rect_w, rect_h;

	switch (state_.rect_mode) {
		case CORNER:
		default:
			// (x, y) is top-left corner, w and h are width and height
			rect_x = x;
			rect_y = y;
			rect_w = w;
			rect_h = h;
			break;
		case CENTER:
			// (x, y) is center, w and h are width and height
			rect_x = x - w / 2;
			rect_y = y - h / 2;
			rect_w = w;
			rect_h = h;
			break;
		case RADIUS:
			// (x, y) is center, w and h are radii (half width and height)
			rect_x = x - w;
			rect_y = y - h;
			rect_w = w * 2;
			rect_h = h * 2;
			break;
		case CORNERS:
			// (x, y) is one corner, w and h are the opposite corner coordinates
			rect_x = std::min(x, (int)w);
			rect_y = std::min(y, (int)h);
			rect_w = std::abs((int)w - x);
			rect_h = std::abs((int)h - y);
			break;
	}

	// Use converted coordinates
	x = rect_x;
	y = rect_y;
	w = rect_w;
	h = rect_h;

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
	h = std::min<int>(y + h, height - 1) - y;

	// clamp left side
	if (x < 0)
		x = 0;

	// clamp top side
	if (y < 0) {
		h += y;
		y = 0;
	}

	// Draw fill
	// TODO: shrink size by stroke/2
	if (state_.do_fill) {
		int inner_stroke = state_.stroke_width / 2;
		x += inner_stroke;
		x2 -= inner_stroke;
		for (int col = x; col < x2; col++) {
			// Fill a column
			draw_vline(y, h, col, state_.fill);
		}
	}

	// Draw stroke (centered on edge)
	if (state_.stroke_width > 0) {
		int sw = std::max(1, (int)state_.stroke_width);
		int half_sw = sw / 2;

		// Top edge: centered at orig_y
		int top_start = orig_y - half_sw;
		int top_end = top_start + sw;
		for (int sy = top_start; sy < top_end; sy++) {
			if (sy >= 0 && sy < (int)height) {
				int sx_start = std::max(0, orig_x - half_sw);
				int sx_end = std::min((int)width, orig_x + (int)orig_w + half_sw);
				for (int sx = sx_start; sx < sx_end; sx++) {
					*buf(sx, sy) = state_.stroke;
				}
			}
		}

		// Bottom edge: centered at orig_y + orig_h
		int bottom_start = orig_y + orig_h - half_sw;
		int bottom_end = bottom_start + sw;
		for (int sy = bottom_start; sy < bottom_end; sy++) {
			if (sy >= 0 && sy < (int)height) {
				int sx_start = std::max(0, orig_x - half_sw);
				int sx_end = std::min((int)width, orig_x + (int)orig_w + half_sw);
				for (int sx = sx_start; sx < sx_end; sx++) {
					*buf(sx, sy) = state_.stroke;
				}
			}
		}

		// Left edge: centered at orig_x
		int left_start = orig_x - half_sw;
		int left_end = left_start + sw;
		for (int sx = left_start; sx < left_end; sx++) {
			if (sx >= 0 && sx < (int)width) {
				// Don't redraw corners (already drawn by top/bottom edges)
				int sy_start = std::max(0, orig_y + half_sw);
				int sy_end = std::min((int)height, orig_y + (int)orig_h - half_sw);
				for (int sy = sy_start; sy < sy_end; sy++) {
					*buf(sx, sy) = state_.stroke;
				}
			}
		}

		// Right edge: centered at orig_x + orig_w
		int right_start = orig_x + orig_w - half_sw;
		int right_end = right_start + sw;
		for (int sx = right_start; sx < right_end; sx++) {
			if (sx >= 0 && sx < (int)width) {
				// Don't redraw corners (already drawn by top/bottom edges)
				int sy_start = std::max(0, orig_y + half_sw);
				int sy_end = std::min((int)height, orig_y + (int)orig_h - half_sw);
				for (int sy = sy_start; sy < sy_end; sy++) {
					*buf(sx, sy) = state_.stroke;
				}
			}
		}
	}
}

} // namespace Handheld
