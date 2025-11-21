#include "../sketch.hh"
#include <span>

namespace Handheld
{

extern std::span<Color> buffer;

inline void set_buffer(std::span<Color> buf) {
	buffer = buf;
}

inline auto buf(unsigned x, unsigned y) {
	// Buffer is arranged in columns.
	// That is, pixels touching each other vertically occupy consectutive memory addresses
	return buffer.data() + x * height + (height - y + 1);
}

inline void draw_vline(unsigned y_start, unsigned height, unsigned x, Color color) {
	std::fill_n(buf(x, y_start), height, color);
}

} // namespace Handheld
