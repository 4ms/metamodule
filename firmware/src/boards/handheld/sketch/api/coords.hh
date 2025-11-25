#include "../api.hh"
// #include "draw_state.hh"
// #include "framebuffer.hh"

namespace Handheld
{

inline void convert_coords(CoordMode mode, int &x, int &y, int &x2, int &y2) {
	switch (mode) {
		case CORNER:
		default:
			// (x, y) is top-left corner, x2 and y2 are width and height
			break;
		case CENTER:
			// (x, y) is center, x2 and y2 are width and height
			x = x - x2 / 2;
			y = y - y2 / 2;
			break;
		case RADIUS:
			// (x, y) is center, x2 and y2 are radii (half width and height)
			x = x - x2;
			y = y - y2;
			x2 = x2 * 2;
			y2 = y2 * 2;
			break;
		case CORNERS: {
			// (x, y) is one corner, x2 and y2 are the opposite corner coordinates
			int ww = std::abs(x2 - x);
			int hh = std::abs(y2 - y);
			x = std::min(x, x2);
			y = std::min(y, y2);
			x2 = ww;
			y2 = hh;
		} break;
	}
}
} // namespace Handheld
