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
	// Buffer is arranged in columns (adjacent memory addresses represent pixels in a vertical line)
	auto pos = x * height + (height - 1 - y);
	return buffer.data() + pos;
}

inline void draw_vert_line(int x, int y_start, int y_end, const Color color) {
#ifndef NDEBUG
	if ((uintptr_t(buffer.data()) & 0b11) != 0) {
		printf("Error: buffer is not aligned to 4-byte boundary\n");
		return;
	}
#endif

	if (y_end == y_start) {
		*buf(x, y_start) = color;
		return;
	}

	if (y_end < y_start)
		return;

	auto start_pos = x * height + (height - y_start - (y_end - y_start + 1));
	auto end_pos = start_pos + (y_end - y_start + 1);

	while (start_pos < end_pos) {

		// One pixel left to draw, or next pixel is not word-aligned: => draw one pixel
		if (end_pos - start_pos == 1 || start_pos & 0b1) {
			buffer[start_pos] = color;
			start_pos++;

		} else {
			// Two or more pixels to draw, and aligned on a word boundary => draw two pixels as a uint32_t.
			// Compiler optimizes this to vst1.64 {d16,d17} when possible (writes 4 words = 8 pixels at a time)
			uint32_t color_32 = (std::bit_cast<uint16_t>(color) << 16) | std::bit_cast<uint16_t>(color);
			while (end_pos - start_pos >= 2) {
				*(uint32_t *)(&buffer[start_pos]) = color_32;
				start_pos += 2;
			}
		}
	}
}

} // namespace Handheld
