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
		Handheld::Color underflow[8 * 8]{};
		Handheld::Color data[8 * 8]{};
		Handheld::Color overflow[8 * 8]{};
	};
	AlignedBuffer buf;
	Handheld::height = 8;
	Handheld::width = 8;

	Handheld::set_buffer(buf.data);
	for (auto &b : buf.data)
		b = 0;
	for (auto &b : buf.overflow)
		b = 0;
	for (auto &b : buf.underflow)
		b = 0;

	SUBCASE("1px stroke, no fill, in corner of frame") {
		Handheld::noFill();
		Handheld::stroke(255);
		Handheld::ellipseMode(Handheld::CENTER);
		Handheld::ellipse(5, 5, 5, 5);

		// Note, if ellipse algorithm changes,
		// it's OK to modify this bitmap.
		// A human must approve it "looks like" a small circle
		std::vector<char> answer;
		answer.resize(Handheld::width * Handheld::height);
		auto y = -8;
		strcpy(&answer[y += 8], "........");
		strcpy(&answer[y += 8], "........");
		strcpy(&answer[y += 8], "........");
		strcpy(&answer[y += 8], ".xxx....");
		strcpy(&answer[y += 8], "x...x...");
		strcpy(&answer[y += 8], "x...x...");
		strcpy(&answer[y += 8], ".xxx....");
		strcpy(&answer[y += 8], "........");

		for (unsigned i = 0; auto c : buf.data) {
			// if (i % Handheld::width == 0)
			// 	printf("\n");
			// if (c == 0)
			// 	printf(". ");
			// else
			// 	printf("x ");

			// if (c == 0)
			// 	CHECK(answer[i] == '.');
			// else
			// 	CHECK(answer[i] == 'x');

			i++;
		}
		// printf("\n");
	}

	SUBCASE("Filled, no stroke in center of frame") {
		Handheld::noStroke();
		Handheld::fill(255);
		Handheld::ellipseMode(Handheld::CENTER);
		Handheld::ellipse(3, 3, 5, 5);

		// Note, if ellipse algorithm changes,
		// it's OK to modify this bitmap.
		// A human must approve it "looks like" a small filled circle
		std::vector<char> answer;
		answer.resize(Handheld::width * Handheld::height);
		auto y = -8;
		strcpy(&answer[y += 8], "........");
		strcpy(&answer[y += 8], "...xx...");
		strcpy(&answer[y += 8], "..xxxx..");
		strcpy(&answer[y += 8], "..xxxxx.");
		strcpy(&answer[y += 8], "..xxxx..");
		strcpy(&answer[y += 8], "...xx...");
		strcpy(&answer[y += 8], "........");
		strcpy(&answer[y += 8], "........");

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

	SUBCASE("2px stroke filled in center of frame") {
		Handheld::fill(255);

		Handheld::stroke(255);
		Handheld::strokeWeight(2);

		Handheld::ellipseMode(Handheld::CORNER);
		Handheld::ellipse(1, 1, 6, 6);

		// Note, if ellipse algorithm changes,
		// it's OK to modify this bitmap.
		// A human must approve it "looks like" a small circle
		std::vector<char> answer;
		answer.resize(Handheld::width * Handheld::height);
		auto y = -8;
		strcpy(&answer[y += 8], "...xx...");
		strcpy(&answer[y += 8], ".xxxxxx.");
		strcpy(&answer[y += 8], ".xxxxxx.");
		strcpy(&answer[y += 8], "xxxxxxxx");
		strcpy(&answer[y += 8], "xxxxxxxx");
		strcpy(&answer[y += 8], ".xxxxxx.");
		strcpy(&answer[y += 8], ".xxxxxx.");
		strcpy(&answer[y += 8], "...xx...");

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
}
