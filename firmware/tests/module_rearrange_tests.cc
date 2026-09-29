#include "doctest.h"
#include "gui/pages/module_rearrange.hh"
#include <vector>

using MetaModule::ModuleRearrange;
using Slot = ModuleRearrange::Slot;

static constexpr int32_t MaxW = 200;

static Slot const &at(ModuleRearrange const &r, uint16_t id) {
	return *r.find(id);
}

static void check_pos(ModuleRearrange const &r, uint16_t id, int32_t x, int32_t row) {
	CAPTURE(id);
	CHECK(at(r, id).x == x);
	CHECK(at(r, id).row == row);
}

TEST_CASE("Turning right closes a gap 2HP at a time") {
	ModuleRearrange r{{{0, 0, 0, 4}, {1, 9, 0, 8}}, 40, MaxW};

	CHECK(r.step_horiz(0, 1));
	check_pos(r, 0, 2, 0);
	CHECK(r.step_horiz(0, 1));
	check_pos(r, 0, 4, 0);

	// 1HP left: closes exactly, no overshoot
	CHECK(r.step_horiz(0, 1));
	check_pos(r, 0, 5, 0);
	check_pos(r, 1, 9, 0);
}

TEST_CASE("Turning left closes a gap to the left neighbour or the left edge") {
	ModuleRearrange r{{{0, 0, 0, 4}, {1, 7, 0, 8}}, 40, MaxW};

	CHECK(r.step_horiz(1, -1));
	check_pos(r, 1, 5, 0);
	CHECK(r.step_horiz(1, -1));
	check_pos(r, 1, 4, 0);

	ModuleRearrange edge{{{0, 1, 0, 4}}, 40, MaxW};
	CHECK(edge.step_horiz(0, -1));
	check_pos(edge, 0, 0, 0);
}

TEST_CASE("Touching neighbours of different widths swap within the same span") {
	// 0: [0,4)  1: [4,24)  2: [30,34)
	ModuleRearrange r{{{0, 0, 0, 4}, {1, 4, 0, 20}, {2, 30, 0, 4}}, 40, MaxW};

	CHECK(r.step_horiz(0, 1));
	check_pos(r, 1, 0, 0);
	check_pos(r, 0, 20, 0);
	check_pos(r, 2, 30, 0);

	CHECK(r.step_horiz(0, -1));
	check_pos(r, 0, 0, 0);
	check_pos(r, 1, 4, 0);
}

TEST_CASE("Turning right past the end of a row moves to the start of the next row, pushing modules aside") {
	ModuleRearrange r{{{0, 36, 0, 4}, {1, 0, 1, 10}, {2, 10, 1, 6}, {3, 30, 1, 4}}, 40, MaxW};

	CHECK(r.step_horiz(0, 1));
	check_pos(r, 0, 0, 1);
	check_pos(r, 1, 4, 1);
	check_pos(r, 2, 14, 1);
	// Wasn't in the way, so it stays put
	check_pos(r, 3, 30, 1);
}

TEST_CASE("Pushing modules past the right edge widens the canvas") {
	ModuleRearrange r{{{0, 36, 0, 4}, {1, 0, 1, 20}, {2, 20, 1, 20}}, 40, MaxW};

	CHECK(r.step_horiz(0, 1));
	check_pos(r, 2, 24, 1);
	CHECK(r.canvas_width() == 44);
}

TEST_CASE("A move that would push past the maximum width is refused") {
	ModuleRearrange r{{{0, 36, 0, 4}, {1, 0, 1, 20}, {2, 20, 1, 20}}, 40, 42};

	CHECK_FALSE(r.step_horiz(0, 1));
	check_pos(r, 0, 36, 0);
	check_pos(r, 2, 20, 1);
	CHECK(r.canvas_width() == 40);
}

TEST_CASE("A new row past the maximum row is refused") {
	ModuleRearrange r{{{0, 0, 0, 4}, {1, 4, 0, 4}}, 40, MaxW, 0};

	CHECK_FALSE(r.step_vert(1, 1));
	check_pos(r, 1, 4, 0);
}

TEST_CASE("Turning left past the start of a row moves to the right end of the previous row") {
	ModuleRearrange r{{{0, 0, 0, 10}, {1, 0, 1, 4}}, 40, MaxW};

	CHECK(r.step_horiz(1, -1));
	check_pos(r, 1, 36, 0);

	// When the row is full to the edge, it goes after the last module
	ModuleRearrange full{{{0, 0, 0, 40}, {1, 0, 1, 4}}, 40, MaxW};
	CHECK(full.step_horiz(1, -1));
	check_pos(full, 1, 40, 0);
	CHECK(full.canvas_width() == 44);
}

TEST_CASE("Moving off the end of the last row wraps to the top, and vice versa") {
	ModuleRearrange r{{{0, 0, 0, 10}, {1, 36, 1, 4}}, 40, MaxW};

	CHECK(r.step_horiz(1, 1));
	check_pos(r, 1, 0, 0);
	check_pos(r, 0, 4, 0);

	ModuleRearrange up{{{0, 0, 0, 4}, {1, 0, 1, 10}}, 40, MaxW};
	CHECK(up.step_horiz(0, -1));
	check_pos(up, 0, 36, 1);
}

TEST_CASE("Moving down keeps x and pushes overlapping modules right") {
	ModuleRearrange r{{{0, 8, 0, 6}, {1, 4, 1, 8}, {2, 12, 1, 4}, {3, 30, 1, 4}}, 40, MaxW};

	CHECK(r.step_vert(0, 1));
	check_pos(r, 0, 8, 1);
	// 1 straddled x=8, so it gets pushed to 0's right edge, and 2 after that
	check_pos(r, 1, 14, 1);
	check_pos(r, 2, 22, 1);
	check_pos(r, 3, 30, 1);
}

TEST_CASE("Moving down from the last row makes a new row, unless the module is alone there") {
	ModuleRearrange r{{{0, 0, 0, 4}, {1, 4, 0, 4}}, 40, MaxW};

	CHECK(r.step_vert(1, 1));
	check_pos(r, 1, 4, 1);

	CHECK_FALSE(r.step_vert(1, 1));
	check_pos(r, 1, 4, 1);
}

TEST_CASE("Moving up from the top row does nothing") {
	ModuleRearrange r{{{0, 0, 0, 4}, {1, 0, 1, 4}}, 40, MaxW};

	CHECK_FALSE(r.step_vert(0, -1));
	check_pos(r, 0, 0, 0);

	CHECK(r.step_vert(1, -1));
	check_pos(r, 1, 0, 0);
	check_pos(r, 0, 4, 0);
}
