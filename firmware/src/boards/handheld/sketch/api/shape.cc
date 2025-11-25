#include "../api.hh"
#include "draw_state.hh"
#include "framebuffer.hh"
#include "util/fixed_vector.hh"

namespace Handheld
{

extern DrawState state_;

void beginShape() {
	state_.vertices.clear();
}

void vertex(float x, float y) {
	// Apply current transformation matrix
	state_.transform_matrix.transform(x, y);
	state_.vertices.push_back({x, y});
}

// Helper function to draw a single-pixel line using Bresenham's algorithm
static void draw_thin_line(int x0, int y0, int x1, int y1, Color color) {
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

// Helper function to draw a thick line centered on the edge
static void draw_thick_line(float x0, float y0, float x1, float y1, float thickness, Color color) {
	if (thickness <= 1.0f) {
		// For single-pixel lines, use the fast algorithm
		draw_thin_line((int)x0, (int)y0, (int)x1, (int)y1, color);
		return;
	}

	// Calculate line direction and perpendicular
	float dx = x1 - x0;
	float dy = y1 - y0;
	float length = std::sqrt(dx * dx + dy * dy);

	if (length < 0.001f)
		return; // Degenerate line

	// Perpendicular unit vector
	float px = -dy / length;
	float py = dx / length;

	// Half thickness
	float half_thick = thickness / 2.0f;

	// Draw multiple parallel lines to create thickness
	int num_lines = std::max(1, (int)(thickness + 0.5f));
	for (int i = 0; i < num_lines; i++) {
		// Offset from center line, ranging from -half_thick to +half_thick
		float offset = -half_thick + (thickness * i) / (num_lines - 1);

		int line_x0 = (int)(x0 + px * offset);
		int line_y0 = (int)(y0 + py * offset);
		int line_x1 = (int)(x1 + px * offset);
		int line_y1 = (int)(y1 + py * offset);

		draw_thin_line(line_x0, line_y0, line_x1, line_y1, color);
	}
}

void endShape(ShapeMode mode) {
	FixedVector<float, 960> intersections;

	if (state_.vertices.size() < 2)
		return;

	bool closed = (mode == CLOSE);
	size_t num_vertices = state_.vertices.size();

	// Draw fill using column-based scan algorithm (optimized for rotated framebuffer)
	if (state_.do_fill && num_vertices >= 3) {
		// Find bounding box
		float min_x = state_.vertices[0].x;
		float max_x = state_.vertices[0].x;
		for (const auto &v : state_.vertices) {
			min_x = std::min(min_x, v.x);
			max_x = std::max(max_x, v.x);
		}

		int x_start = std::max(0, (int)min_x);
		int x_end = std::min((int)width - 1, (int)max_x);

		// For each column (scan along X axis)
		for (int scan_x = x_start; scan_x <= x_end; scan_x++) {
			intersections.clear();

			// Find intersections with polygon edges
			for (size_t i = 0; i < num_vertices; i++) {
				size_t j = (i + 1) % num_vertices;
				if (!closed && j == 0)
					break; // Don't connect last to first if open

				const Vertex &v1 = state_.vertices[i];
				const Vertex &v2 = state_.vertices[j];

				// Check if edge crosses vertical scan line
				if ((v1.x <= scan_x && v2.x > scan_x) || (v2.x <= scan_x && v1.x > scan_x)) {
					// Calculate intersection y coordinate
					float t = (scan_x - v1.x) / (v2.x - v1.x);
					float y_intersect = v1.y + t * (v2.y - v1.y);
					intersections.push_back(y_intersect);
				}
			}

			// Sort intersections
			std::sort(intersections.begin(), intersections.end());

			// Fill between pairs of intersections using optimized vertical line drawing
			for (size_t i = 0; i + 1 < intersections.size(); i += 2) {
				int y_start = std::clamp((int)intersections[i], 0, (int)height - 1);
				int y_end = std::clamp((int)intersections[i + 1], 0, (int)height - 1);

				if (y_end >= y_start) {
					draw_vert_line(scan_x, y_start, y_end, state_.fill);
				}
			}
		}
	}

	// Draw stroke
	if (state_.stroke_width > 0) {
		// Draw lines between consecutive vertices
		for (size_t i = 0; i < num_vertices - 1; i++) {
			float x0 = state_.vertices[i].x;
			float y0 = state_.vertices[i].y;
			float x1 = state_.vertices[i + 1].x;
			float y1 = state_.vertices[i + 1].y;

			draw_thick_line(x0, y0, x1, y1, state_.stroke_width, state_.stroke);
		}

		// Close the shape if requested
		if (closed && num_vertices >= 2) {
			float x0 = state_.vertices[num_vertices - 1].x;
			float y0 = state_.vertices[num_vertices - 1].y;
			float x1 = state_.vertices[0].x;
			float y1 = state_.vertices[0].y;

			draw_thick_line(x0, y0, x1, y1, state_.stroke_width, state_.stroke);
		}
	}
}

} // namespace Handheld
