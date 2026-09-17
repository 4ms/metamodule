#include "doctest.h"
#include "gui/pages/module_layout.hh"
#include <cmath>
#include <vector>

using MetaModule::ModuleLayout;
using Box = ModuleLayout::Box;
using Coord = ModuleLayout::Coord;

// A row of 180px modules, 3px apart, like PatchView at the default zoom
static constexpr int32_t RowPitch = 183;
static constexpr int32_t H = 180;

TEST_CASE("Auto layout flows modules left to right and wraps") {
	std::vector<Box> boxes(5, Box{.width = 28, .height = H});

	auto r = ModuleLayout::arrange(boxes, 100, RowPitch, false);

	CHECK(r.num_unplaced == 0);
	CHECK(r.positions[0] == Coord{0, 0});
	CHECK(r.positions[1] == Coord{28, 0});
	CHECK(r.positions[2] == Coord{56, 0});
	// 4 * 28 = 112 > 100, so the fourth wraps
	CHECK(r.positions[3] == Coord{0, RowPitch});
	CHECK(r.positions[4] == Coord{28, RowPitch});

	CHECK(r.width == 84);
	CHECK(r.height == RowPitch + H);
}

TEST_CASE("Auto layout ignores the positions stored in the patch") {
	std::vector<Box> boxes{
		Box{.width = 28, .height = H, .wanted = Coord{500, RowPitch * 3}},
		Box{.width = 28, .height = H},
	};

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, false);

	CHECK(r.positions[0] == Coord{0, 0});
	CHECK(r.positions[1] == Coord{28, 0});
}

TEST_CASE("Stored positions are used, and unpositioned modules follow the last one") {
	std::vector<Box> boxes{
		Box{.width = 40, .height = H, .wanted = Coord{100, 0}},
		Box{.width = 40, .height = H}, // no position: goes after the one above
		Box{.width = 40, .height = H, .wanted = Coord{0, RowPitch}},
	};

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, true);

	CHECK(r.num_unplaced == 0);
	CHECK(r.positions[0] == Coord{100, 0});
	CHECK(r.positions[2] == Coord{0, RowPitch});
	// The cursor sits after the last *positioned* module, which is box 2 at (0, RowPitch)
	CHECK(r.positions[1] == Coord{40, RowPitch});
}

TEST_CASE("A stored position that overlaps an already-placed module is dropped") {
	std::vector<Box> boxes{
		Box{.width = 40, .height = H, .wanted = Coord{0, 0}},
		Box{.width = 40, .height = H, .wanted = Coord{20, 0}}, // overlaps the first
	};

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, true);

	CHECK(r.num_unplaced == 0);
	CHECK(r.positions[0] == Coord{0, 0});
	// Dropped from its stored spot and flowed in after the first instead
	CHECK(r.positions[1] == Coord{40, 0});
}

TEST_CASE("A stored position past the canvas limit is dropped") {
	std::vector<Box> boxes{
		Box{.width = 40, .height = H, .wanted = Coord{ModuleLayout::MaxCanvasDim - 10, 0}},
		Box{.width = 40, .height = H, .wanted = Coord{0, ModuleLayout::MaxCanvasDim - 10}},
		Box{.width = 40, .height = H, .wanted = Coord{-5, 0}},
	};

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, true);

	CHECK(r.num_unplaced == 0);
	for (auto const &p : r.positions) {
		REQUIRE(p.has_value());
		CHECK(p->x + 40 <= ModuleLayout::MaxCanvasDim);
		CHECK(p->y + H <= ModuleLayout::MaxCanvasDim);
		CHECK(p->x >= 0);
		CHECK(p->y >= 0);
	}
}

TEST_CASE("A lone positioned module anchors the layout at the origin") {
	// Parked far down the canvas, but it is the only position, so it defines the origin
	std::vector<Box> boxes{
		Box{.width = 40, .height = H, .wanted = Coord{0, RowPitch * 8}},
		Box{.width = 40, .height = H},
		Box{.width = 40, .height = H},
	};

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, true);

	CHECK(r.num_unplaced == 0);
	CHECK(r.positions[0] == Coord{0, 0});
	// The unpositioned ones flow on from it
	CHECK(r.positions[1] == Coord{40, 0});
	CHECK(r.positions[2] == Coord{80, 0});
}

TEST_CASE("Normalizing does not guarantee a module at the corner") {
	// Left-most module is on the bottom row, top-most is off to the right: x=0 and y=0 are
	// each occupied, but nothing sits at 0,0
	std::vector<Box> boxes{
		Box{.width = 40, .height = H, .wanted = Coord{60, RowPitch * 3}},
		Box{.width = 40, .height = H, .wanted = Coord{200, RowPitch * 2}},
	};

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, true);

	CHECK(r.positions[1] == Coord{140, 0});
	CHECK(r.positions[0] == Coord{0, RowPitch});
}

TEST_CASE("The gap between two positioned modules gets filled") {
	std::vector<Box> boxes{
		Box{.width = 40, .height = H, .wanted = Coord{0, 0}},
		Box{.width = 40, .height = H, .wanted = Coord{120, 0}},
		Box{.width = 40, .height = H}, // fits exactly in the 40..120 gap
	};

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, true);

	CHECK(r.num_unplaced == 0);
	// The cursor starts after the last positioned module (160, 0) and finds room there
	CHECK(r.positions[2] == Coord{160, 0});
}

TEST_CASE("Only once the canvas runs out does a module go back and use an early gap") {
	// Tall rows so the canvas only holds two of them: y = 0 and y = 1000 (2000 would overflow)
	constexpr int32_t Pitch = 1000;
	constexpr int32_t Tall = 900;

	std::vector<Box> boxes{
		Box{.width = 40, .height = Tall, .wanted = Coord{0, 0}},
		Box{.width = 40, .height = Tall, .wanted = Coord{120, 0}}, // leaves a 40..120 gap
		Box{.width = 120, .height = Tall},						   // fills the rest of row 0
		Box{.width = 240, .height = Tall},						   // starts row 1
		Box{.width = 40, .height = Tall},						   // fills the rest of row 1
		Box{.width = 28, .height = Tall},						   // nowhere left to flow
	};

	auto r = ModuleLayout::arrange(boxes, 280, Pitch, true);

	CHECK(r.num_unplaced == 0);
	CHECK(r.positions[2] == Coord{160, 0});
	CHECK(r.positions[3] == Coord{0, Pitch});
	CHECK(r.positions[4] == Coord{240, Pitch});

	// Out of rows, so this one wraps back to the top and drops into the gap
	CHECK(r.positions[5] == Coord{40, 0});
}

TEST_CASE("Modules that cannot be fitted are counted") {
	// Fill the canvas: each row holds one 300px module, and there are only so many rows
	auto rows = ModuleLayout::MaxCanvasDim / RowPitch + 1;
	std::vector<Box> boxes((size_t)rows + 4, Box{.width = 300, .height = H});

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, false);

	CHECK(r.num_unplaced > 0);
	CHECK(r.height <= ModuleLayout::MaxCanvasDim);

	// Only a module too wide for the canvas itself can never be placed
	std::vector<Box> too_wide{Box{.width = ModuleLayout::MaxCanvasDim + 1, .height = H}};
	auto r2 = ModuleLayout::arrange(too_wide, 308, RowPitch, false);
	CHECK(r2.num_unplaced == 1);
	CHECK(!r2.positions[0].has_value());
}

TEST_CASE("A module wider than the rack widens the rack instead of being dropped") {
	// 48HP is 341px at the default zoom, well past the 308px of a screen-width rack
	std::vector<Box> boxes{
		Box{.width = 341, .height = H},
		Box{.width = 28, .height = H},
	};

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, false);

	CHECK(r.num_unplaced == 0);
	CHECK(r.positions[0] == Coord{0, 0});

	// The bound grew to 341, but 341 + 28 still doesn't fit, so the small one wraps
	CHECK(r.positions[1] == Coord{0, RowPitch});
	CHECK(r.width == 341);
}

TEST_CASE("Widening for one module lets the others use the extra room") {
	std::vector<Box> boxes{
		Box{.width = 341, .height = H},
		Box{.width = 100, .height = H},
		Box{.width = 100, .height = H},
		Box{.width = 100, .height = H},
	};

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, false);

	CHECK(r.num_unplaced == 0);
	CHECK(r.positions[0] == Coord{0, 0});
	// Three 100px modules now share a row, because the rack is 341 wide
	CHECK(r.positions[1] == Coord{0, RowPitch});
	CHECK(r.positions[2] == Coord{100, RowPitch});
	CHECK(r.positions[3] == Coord{200, RowPitch});
}

TEST_CASE("Nothing placed overlaps anything else") {
	std::vector<Box> boxes{
		Box{.width = 40, .height = H, .wanted = Coord{0, 0}},
		Box{.width = 60, .height = H, .wanted = Coord{35, 0}}, // overlaps -> dropped
		Box{.width = 40, .height = H, .wanted = Coord{0, RowPitch}},
		Box{.width = 28, .height = H},
		Box{.width = 28, .height = H},
		Box{.width = 90, .height = H, .wanted = Coord{100, RowPitch}},
		Box{.width = 28, .height = H},
	};

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, true);

	for (auto i = 0u; i < boxes.size(); i++) {
		if (!r.positions[i].has_value())
			continue;

		for (auto j = i + 1; j < boxes.size(); j++) {
			if (!r.positions[j].has_value())
				continue;

			auto a = *r.positions[i];
			auto b = *r.positions[j];
			bool apart = a.x + boxes[i].width <= b.x || b.x + boxes[j].width <= a.x || a.y + boxes[i].height <= b.y ||
						 b.y + boxes[j].height <= a.y;
			INFO("box ", i, " at ", a.x, ",", a.y, " overlaps box ", j, " at ", b.x, ",", b.y);
			CHECK(apart);
		}
	}
}

TEST_CASE("Modules meant to sit side by side are snapped flush") {
	// A 4HP module is 28.46px on the HP grid but is drawn 28px wide, so the stored positions
	// drift a pixel ahead of the modules and leave a gap on every other seam
	std::vector<Box> boxes;
	for (auto hp = 0; hp < 32; hp += 4)
		boxes.push_back(Box{.width = 28, .height = H, .wanted = Coord{(int32_t)std::lround(hp * 7.116), 0}});

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, true);

	CHECK(r.num_unplaced == 0);
	for (auto i = 1u; i < boxes.size(); i++) {
		REQUIRE(r.positions[i].has_value());
		REQUIRE(r.positions[i - 1].has_value());
		INFO("seam ", i);
		CHECK(r.positions[i]->x == r.positions[i - 1]->x + 28);
	}
}

TEST_CASE("A deliberate gap is left alone") {
	// 4HP of space between the two modules is far more than the snap tolerance
	std::vector<Box> boxes{
		Box{.width = 28, .height = H, .wanted = Coord{0, 0}},
		Box{.width = 28, .height = H, .wanted = Coord{57, 0}}, // 8HP: a 4HP gap
	};

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, true);
	CHECK(r.positions[1] == Coord{57, 0});
}

TEST_CASE("A one-pixel rounding overlap snaps instead of dropping the module") {
	std::vector<Box> boxes{
		Box{.width = 28, .height = H, .wanted = Coord{0, 0}},
		Box{.width = 28, .height = H, .wanted = Coord{27, 0}}, // 1px into its neighbour
	};

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, true);

	CHECK(r.num_unplaced == 0);
	CHECK(r.positions[1] == Coord{28, 0});
}

TEST_CASE("Snapping does not reach across rows") {
	std::vector<Box> boxes{
		Box{.width = 28, .height = H, .wanted = Coord{0, 0}},
		Box{.width = 28, .height = H, .wanted = Coord{29, RowPitch}}, // next row, 1px off
	};

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, true);
	CHECK(r.positions[1] == Coord{29, RowPitch});
}

TEST_CASE("Stored positions are normalized to the top left") {
	// Nothing anywhere near the origin: the whole layout should slide up and left
	std::vector<Box> boxes{
		Box{.width = 40, .height = H, .wanted = Coord{300, RowPitch * 4}},
		Box{.width = 40, .height = H, .wanted = Coord{340, RowPitch * 4}},
		Box{.width = 40, .height = H, .wanted = Coord{300, RowPitch * 5}},
	};

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, true);

	CHECK(r.num_unplaced == 0);
	CHECK(r.positions[0] == Coord{0, 0});
	CHECK(r.positions[1] == Coord{40, 0});
	CHECK(r.positions[2] == Coord{0, RowPitch});
}

TEST_CASE("Normalizing keeps the modules' spacing relative to each other") {
	std::vector<Box> boxes{
		Box{.width = 40, .height = H, .wanted = Coord{100, RowPitch * 2}},
		Box{.width = 40, .height = H, .wanted = Coord{220, RowPitch * 2}}, // 80px gap
	};

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, true);

	CHECK(r.positions[0] == Coord{0, 0});
	CHECK(r.positions[1] == Coord{120, 0});
}

TEST_CASE("Negative stored positions are normalized in rather than dropped") {
	std::vector<Box> boxes{
		Box{.width = 40, .height = H, .wanted = Coord{-80, -RowPitch}},
		Box{.width = 40, .height = H, .wanted = Coord{-40, -RowPitch}},
	};

	auto r = ModuleLayout::arrange(boxes, 308, RowPitch, true);

	CHECK(r.num_unplaced == 0);
	CHECK(r.positions[0] == Coord{0, 0});
	CHECK(r.positions[1] == Coord{40, 0});
}
