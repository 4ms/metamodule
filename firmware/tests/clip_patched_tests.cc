#include "doctest.h"
#include "gui/notify/clip_patched.hh"

using MetaModule::patched_outputs_mask;

TEST_CASE("patched_outputs_mask: nothing patched") {
	CHECK(patched_outputs_mask(0, 16) == 0);
}

TEST_CASE("patched_outputs_mask: main outputs use the main jack-sense bit order") {
	// Main outs 1..8 sense bits: 4, 5, 6, 1, 2, 7, 3, 0
	CHECK(patched_outputs_mask(1u << 4, 8) == 0b0000'0001);
	CHECK(patched_outputs_mask(1u << 0, 8) == 0b1000'0000);
	CHECK(patched_outputs_mask(0xFF, 8) == 0xFF);
	// Input/gate sense bits don't count as outputs
	CHECK(patched_outputs_mask(0xFF00, 8) == 0);
}

TEST_CASE("patched_outputs_mask: expander outputs use the expander bit order") {
	// Expander outs 9..16 sense bits: 18, 22, 31, 25, 30, 27, 29, 28
	CHECK(patched_outputs_mask(1u << 18, 16) == (1u << 8));
	CHECK(patched_outputs_mask(1u << 28, 16) == (1u << 15));
}

TEST_CASE("patched_outputs_mask: ignores outputs beyond num_outputs") {
	CHECK(patched_outputs_mask(1u << 18, 8) == 0);
}
