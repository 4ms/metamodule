#include "boards/handheld/sketch/api/framebuffer.hh"
#include "doctest.h"

namespace Handheld
{
unsigned width = 7;
unsigned height = 7;
std::span<Color> buffer;
} // namespace Handheld

TEST_CASE("draw vline") {

	struct alignas(64) AlignedBuffer {
		Handheld::Color data[49]{};
	};
	AlignedBuffer buf;
	for (auto &b : buf.data)
		b = 0;

	SUBCASE("Test operator=(uint16_t)") {
		buf.data[0] = 0xFFFF;
		buf.data[1] = 0x1234;
		CHECK(buf.data[0] == 0xFFFF);
		CHECK(uint16_t(buf.data[1]) == 0x1234);
	}

	SUBCASE("Test settings two pixels with one op") {
		*(uint32_t *)(&buf.data[0]) = 0x1234FFFF;
		CHECK(buf.data[0] == 0xFFFF);
		CHECK(buf.data[1] == 0x1234);
	}

	Handheld::set_buffer(buf.data);

	SUBCASE("line 1") {
		/* 
	line (x=4, y=1) to (4, 3)

	on screen:
	   0 1 2 3 4 5 6
	 0 . . . . . . . 
	 1 . . . . x . .
	 2 . . . . x . .
	 3 . . . . x . .
	 4 . . . . . . .
	 5 . . . . . . .
	 6 . . . . . . . 

	 in memory:
	  . . . . . . . 
	  . . . . x . .
	  . . . . x . .
	  . . . . x . .
	  . . . . . . .
	  . . . . . . .
	  . . . . . . . 
	  0 7 14  28  42 
      ^
	  ^
      |
	 in memory (rotated 90 degrees, starting at bottom left and moving up):
	  0 1 2 3       7             14            21            28            35            42          48
	  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . x x x . . . . . . . . . . . . . . . 
   */
		auto color = Handheld::Color(0x11AA55);
		Handheld::draw_vert_line(4, 1, 3, color);

		CHECK(uint16_t(buf.data[31]) == uint16_t(color));
		CHECK(buf.data[32].raw() == color.raw());
		CHECK(buf.data[33].raw() == color.raw());

		for (unsigned i = 0; auto b : buf.data) {
			if (i >= 31 && i <= 33) {
				// CHECK(uint16_t(b) == uint16_t(color));
			} else {
				CHECK(uint16_t(b) == 0);
			}
			i++;
		}
	}

	SUBCASE("line 2") {
		/* 
	line (1, 1) to (1, 6)
	   on screen:
	   0 1 2 3 4 5 6
	 0 . . . . . . . 
	 1 . x . . . . .
	 2 . x . . . . .
	 3 . x . . . . .
	 4 . x . . . . .
	 5 . x . . . . .
	 6 . x . . . . . 

	  in memory:
	   . . . . . . . 
	   . x . . . . .
	   . x . . . . .
	   . x . . . . .
	   . x . . . . .
	   . x . . . . .
	   . x . . . . . 
	   0 7 14  28  42 
       ^
	   ^
       |
	 in memory (rotated 90 degrees, starting at bottom left and moving up):
	  0 1 2 3       7             14            21            28            35            42          48
	  . . . . . . . x x x x x x . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
   */
		auto color = Handheld::Color(0x55AA);
		Handheld::draw_vert_line(1, 1, 6, color);
		for (unsigned i = 0; auto b : buf.data) {
			if (i >= 7 && i <= 12) {
				CHECK(uint16_t(b) == uint16_t(color));
			} else {
				CHECK(uint16_t(b) == 0);
			}
			i++;
		}
	}

	SUBCASE("dot at loweset memory address") {
		auto color = Handheld::Color(0x5555);
		Handheld::draw_vert_line(0, 6, 6, color);
		for (unsigned i = 0; auto b : buf.data) {
			if (i == 0) {
				CHECK(uint16_t(b) == uint16_t(color));
			} else {
				CHECK(uint16_t(b) == 0);
			}
			i++;
		}
	}
}
