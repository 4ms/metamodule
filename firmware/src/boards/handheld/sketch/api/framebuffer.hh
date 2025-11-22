#include "../sketch.hh"
#include <cstring>
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
	// constexpr int HEIGHT = 400;
	// auto pos = (x + 1) * HEIGHT - 1 - y;

	auto pos = x * height + (height - 1 - y);

	// auto pos = x * height + y;

	return buffer.data() + pos;
}

inline void draw_vline(int y_start, int h, int x, Color color) {
	// uint32_t c = color << 16 | color;
	// std::memset(buf(x, y_start), c, h / 2);
	// if (h & 1) {
	// 	*buf(x, y_start + h) = color;
	// }

	std::fill_n(buf(x, y_start), h, color);

	// for (int i = 0; i < h; i++) {
	// 	*buf(x, y_start + i) = color;
	// }
}

} // namespace Handheld
