#include "../api.hh"
#include "draw_state.hh"
#include "framebuffer.hh"

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

} // namespace Handheld
