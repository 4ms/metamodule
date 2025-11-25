#include "doctest.h"
#include "sketch/api/draw_state.hh"
#include "sketch/api/framebuffer.hh"
#include <vector>

namespace Handheld
{
extern unsigned width;
extern unsigned height;
extern std::span<Color> buffer;

DrawState state_;

} // namespace Handheld

TEST_CASE("draw ellipse") {
	struct alignas(64) AlignedBuffer {
		Handheld::Color data[8 * 8]{};
	};
	AlignedBuffer buf;
	Handheld::height = 8;
	Handheld::width = 8;

	Handheld::set_buffer(buf.data);
	for (auto &b : buf.data)
		b = 0;

	Handheld::noFill();
	Handheld::stroke(255);
	Handheld::ellipseMode(Handheld::CENTER);
	Handheld::ellipse(3, 3, 5, 5);

	// Note, if ellipse algorithm changes,
	// it's OK to modify this bitmap.
	// A human must approve it "looks like" a small circle
	std::vector<char> answer;
	answer.resize(Handheld::width * Handheld::height);
	strcpy(&answer[0x00], "........");
	strcpy(&answer[0x08], "...xxx..");
	strcpy(&answer[0x10], "..x...x.");
	strcpy(&answer[0x18], "..x...x.");
	strcpy(&answer[0x20], "..x...x.");
	strcpy(&answer[0x28], "..xxxxx.");
	strcpy(&answer[0x30], "........");
	strcpy(&answer[0x38], "........");

	for (unsigned i = 0; auto c : buf.data) {
		// if (i % Handheld::width == 0)
		// 	printf("\n");
		// if (c == 0)
		// 	printf(". ");
		// else
		// 	printf("x ");

		if (c == 0)
			CHECK(answer[i] == '.');
		else
			CHECK(answer[i] == 'x');

		i++;
	}
	// printf("\n");
}
