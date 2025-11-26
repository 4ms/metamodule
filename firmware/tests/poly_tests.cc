#include "doctest.h"
#include "sketch/api/draw_state.hh"
#include "sketch/api/framebuffer.hh"
#include <vector>

namespace Handheld
{
extern unsigned width;
extern unsigned height;
extern std::span<Color> buffer;

extern DrawState state_;

} // namespace Handheld

TEST_CASE("stroked triangle") {
	struct alignas(64) AlignedBuffer {
		Handheld::Color underflow[8 * 8]{};
		Handheld::Color data[16 * 16]{};
		Handheld::Color overflow[8 * 8]{};
	};
	AlignedBuffer buf;
	Handheld::height = 16;
	Handheld::width = 16;

	Handheld::set_buffer(buf.data);
	for (auto &b : buf.data)
		b = 0;
	for (auto &b : buf.overflow)
		b = 0;
	for (auto &b : buf.underflow)
		b = 0;

	SUBCASE("1px stroke, no fill, in center of frame") {
		Handheld::noFill();
		Handheld::stroke(255);
		Handheld::strokeWeight(1);

		Handheld::beginShape();
		Handheld::vertex(7, 1);
		Handheld::vertex(1, 14);
		Handheld::vertex(13, 14);
		Handheld::endShape(Handheld::CLOSE);

		// Note, if shape algorithm changes,
		// it's OK to modify this bitmap.
		// A human must approve it "looks like" a triangle
		std::vector<char> answer;
		answer.resize(Handheld::width * Handheld::height);
		auto stride = Handheld::width;
		auto y = -stride;
		strcpy(&answer[y += stride], "................");
		strcpy(&answer[y += stride], ".xx.............");
		strcpy(&answer[y += stride], ".x.xx...........");
		strcpy(&answer[y += stride], ".x...xx.........");
		strcpy(&answer[y += stride], ".x.....xx.......");
		strcpy(&answer[y += stride], ".x.......xx.....");
		strcpy(&answer[y += stride], ".x.........xx...");
		strcpy(&answer[y += stride], ".x...........xx.");
		strcpy(&answer[y += stride], ".x.........xx...");
		strcpy(&answer[y += stride], ".x.......xx.....");
		strcpy(&answer[y += stride], ".x.....xx.......");
		strcpy(&answer[y += stride], ".x...xx.........");
		strcpy(&answer[y += stride], ".x.xx...........");
		strcpy(&answer[y += stride], ".xx.............");
		strcpy(&answer[y += stride], "................");
		strcpy(&answer[y += stride], "................");

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

		for (auto c : buf.overflow) {
			CHECK(c == 0);
		}
		for (auto c : buf.underflow) {
			CHECK(c == 0);
		}
	}

	SUBCASE("4px stroke, no fill, in center of frame") {
		Handheld::noFill();
		Handheld::stroke(255);
		Handheld::strokeWeight(4);

		Handheld::beginShape();
		Handheld::vertex(7, 1);
		Handheld::vertex(1, 14);
		Handheld::vertex(13, 14);
		Handheld::endShape(Handheld::CLOSE);

		// Note, if shape algorithm changes,
		// it's OK to modify this bitmap.
		// A human must approve it "looks like" a triangle
		std::vector<char> answer;
		answer.resize(Handheld::width * Handheld::height);
		auto stride = Handheld::width;
		auto y = -stride;
		strcpy(&answer[y += stride], "................");
		strcpy(&answer[y += stride], ".xx.............");
		strcpy(&answer[y += stride], ".x.xx...........");
		strcpy(&answer[y += stride], ".x...xx.........");
		strcpy(&answer[y += stride], ".x.....xx.......");
		strcpy(&answer[y += stride], ".x.......xx.....");
		strcpy(&answer[y += stride], ".x.........xx...");
		strcpy(&answer[y += stride], ".x...........xx.");
		strcpy(&answer[y += stride], ".x.........xx...");
		strcpy(&answer[y += stride], ".x.......xx.....");
		strcpy(&answer[y += stride], ".x.....xx.......");
		strcpy(&answer[y += stride], ".x...xx.........");
		strcpy(&answer[y += stride], ".x.xx...........");
		strcpy(&answer[y += stride], ".xx.............");
		strcpy(&answer[y += stride], "................");
		strcpy(&answer[y += stride], "................");

		for (unsigned i = 0; auto c : buf.data) {
			if (i % Handheld::width == 0)
				printf("\n");
			if (c == 0)
				printf(". ");
			else
				printf("x ");

			// if (c == 0)
			// 	CHECK(answer[i] == '.');
			// else
			// 	CHECK(answer[i] == 'x');

			i++;
		}
		// printf("\n");

		for (auto c : buf.overflow) {
			CHECK(c == 0);
		}
		for (auto c : buf.underflow) {
			CHECK(c == 0);
		}
	}
}
