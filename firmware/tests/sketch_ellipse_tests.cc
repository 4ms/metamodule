#include "doctest.h"
#include "sketch/api/draw_state.hh"
#include "sketch/api/framebuffer.hh"

namespace Handheld
{
extern unsigned width;
extern unsigned height;
extern std::span<Color> buffer;

DrawState state_;

} // namespace Handheld

TEST_CASE("draw ellipse") {
	struct alignas(64) AlignedBuffer {
		Handheld::Color data[20 * 20]{};
	};
	AlignedBuffer buf;
	Handheld::height = 20;
	Handheld::width = 20;

	Handheld::set_buffer(buf.data);
	for (auto &b : buf.data)
		b = 0;

	Handheld::fill(127);
	Handheld::noStroke();
	Handheld::ellipseMode(Handheld::CENTER);
	Handheld::ellipse(3, 3, 4, 4);

	/*
	on screen:
	   0 1 2 3 4 5 6
	 0 . . . x . . . 
	 1 . . x x x . .
	 2 . x x c x x .
	 3 . . x x x . .
	 4 . . . . . . .
	 5 . . . . . . .
	 6 . . . . . . . 
	 */

	for (unsigned i = 0; auto c : buf.data) {
		if (i % Handheld::width == 0)
			printf("\n");
		if (c == 0)
			printf(". ");
		else
			printf("x ");
		i++;
	}
	printf("\n");
}
