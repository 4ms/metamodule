#include "../sketch.hh"
#include <cstdio>
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

	auto pos = x * height + (height - 1 - y);
	// printf("[%d, %d] pos = %d\n", x, y, pos);

	return buffer.data() + pos;
}

inline void draw_vline(int y_start, int h, int x, Color color) {
	if ((uintptr_t(buffer.data()) & 0b11) != 0) {
		printf("Error: buffer is not aligned to 4-byte boundary\n");
		return;
	}

	// 0.875us
	uint32_t color_32 = (uint16_t(color) << 16) | uint16_t(color);
	auto start_pos = x * height + (height - y_start - h);
	while (h > 0) {

		// One pixel left to draw, or next pixel is not word-aligned: => draw one pixel
		if (h == 1 || start_pos & 0b1) {
			// printf("One pixel pos(x=%d, y=%d, h=%d) = [%d]\n", x, y_start, h, start_pos);
			buffer[start_pos] = color;
			h--;
			start_pos++;
		} else {
			// Two or more pixels to draw, starting with a word boundary => draw two pixels as a uint32_t
			// printf("Two pixels pos(x=%d, y=%d, h=%d) = [%d]\n", x, y_start, h, start_pos);
			while (h >= 2) {
				*(uint32_t *)(&buffer[start_pos]) = color_32;
				h -= 2;
				start_pos += 2;
			}
		}
	}

	// 2.32ms
	// std::fill_n(buf(x, y_start + h - 1), h, color);

	// 1.07ms
	// for (int i = 0; i < h; i++) {
	// 	*buf(x, y_start + i) = color;
	// }
}

} // namespace Handheld
