#include "../api.hh"
#include "draw_state.hh"
#include "framebuffer.hh"

namespace Handheld
{

extern DrawState state_;

void ellipse(int x, int y, int w, int h) {
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

	// Draw stroke (centered on edge)
	if (state_.stroke_width > 0) {
		float sw = state_.stroke_width;
		float half_sw = sw / 2.0f;

		// Draw stroke using inner and outer ellipse, centered on the original ellipse boundary
		// Outer ellipse has radii extended by half stroke width
		// Inner ellipse has radii reduced by half stroke width
		float rx_outer = rx + half_sw;
		float ry_outer = ry + half_sw;
		float rx_inner = std::max(0.0f, rx - half_sw);
		float ry_inner = std::max(0.0f, ry - half_sw);

		// Expand scan range to cover the outer ellipse
		int stroke_y_start = std::max(0, (int)(cy - ry_outer));
		int stroke_y_end = std::min((int)height - 1, (int)(cy + ry_outer));

		for (int scan_y = stroke_y_start; scan_y <= stroke_y_end; scan_y++) {
			float dy = scan_y - cy;

			// Outer ellipse
			float y_ratio_outer = dy / ry_outer;
			float discriminant_outer = 1.0f - y_ratio_outer * y_ratio_outer;

			if (discriminant_outer < 0)
				continue;

			float dx_outer = rx_outer * std::sqrt(discriminant_outer);

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
} // namespace Handheld
