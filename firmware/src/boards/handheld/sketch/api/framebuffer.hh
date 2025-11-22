#include "../sketch.hh"
#include <span>

namespace Handheld
{

extern std::span<Color> buffer;

inline void set_buffer(std::span<Color> buf) {
	buffer = buf;
}

inline auto buf(int x, int y) {
	// Buffer is arranged in columns.
	// That is, pixels touching each other vertically occupy consectutive memory addresses
	constexpr int HEIGHT = 400;
	auto pos = (x + 1) * HEIGHT - 1 - y;

	return buffer.data() + pos;
}

inline void draw_vline(unsigned y_start, unsigned height, unsigned x, Color color) {
	std::fill_n(buf(x, y_start), height, color);
}

} // namespace Handheld
