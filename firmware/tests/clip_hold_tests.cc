#include "doctest.h"
#include "gui/notify/clip_hold.hh"

using MetaModule::ClipHold;

// Times are relative to the hold time, so tests don't depend on its value
constexpr uint32_t Hold = ClipHold<16>::HoldMs;
static_assert(Hold >= 4, "tests need distinct quarter/half points");

TEST_CASE("ClipHold: nothing lit initially") {
	ClipHold<16> h;
	for (unsigned i = 0; i < 16; i++)
		CHECK_FALSE(h.is_lit(i, 1000));
}

TEST_CASE("ClipHold: lit for HoldMs after a hit, then off") {
	ClipHold<16> h;
	uint32_t t = 1000;
	h.update(0b10, t);
	CHECK(h.is_lit(1, t));
	CHECK(h.is_lit(1, t + Hold - 1));
	CHECK_FALSE(h.is_lit(1, t + Hold));
	CHECK_FALSE(h.is_lit(0, t));
}

TEST_CASE("ClipHold: re-hit extends hold; slots are independent") {
	ClipHold<16> h;
	uint32_t t = 1000;
	uint32_t t1 = t + Hold / 4;
	uint32_t t2 = t + Hold / 2;
	h.update(0b01, t);
	h.update(0b10, t1);
	h.update(0b01, t2);
	CHECK(h.is_lit(0, t + Hold)); // would have expired without the re-hit
	CHECK(h.is_lit(0, t2 + Hold - 1));
	CHECK_FALSE(h.is_lit(0, t2 + Hold));
	CHECK(h.is_lit(1, t1 + Hold - 1));
	CHECK_FALSE(h.is_lit(1, t1 + Hold));
}

TEST_CASE("ClipHold: empty mask does not extend") {
	ClipHold<16> h;
	uint32_t t = 1000;
	h.update(0b1, t);
	h.update(0, t + Hold - 1);
	CHECK(h.is_lit(0, t + Hold - 1));
	CHECK_FALSE(h.is_lit(0, t + Hold));
}

TEST_CASE("ClipHold: bits beyond N ignored, out-of-range index is unlit") {
	ClipHold<8> h;
	h.update(0xFFFF'FF00, 1000);
	for (unsigned i = 0; i < 8; i++)
		CHECK_FALSE(h.is_lit(i, 1000));
	CHECK_FALSE(h.is_lit(8, 1000));
}

TEST_CASE("ClipHold: tick wraparound") {
	ClipHold<16> h;
	uint32_t t = 0u - Hold / 2; // hold window straddles the wrap
	h.update(0b1, t);
	CHECK(h.is_lit(0, t + Hold / 4));
	CHECK(h.is_lit(0, t + Hold - 1)); // wrapped past 0
	CHECK_FALSE(h.is_lit(0, t + Hold));
	CHECK_FALSE(h.is_lit(0, t + 0x8000'0000u)); // long after: not stuck on
}

TEST_CASE("ClipHold: expired slot doesn't relight when the tick counter wraps all the way around") {
	ClipHold<16> h;
	uint32_t t = 1000;
	h.update(0b1, t);
	h.update(0, t + Hold); // expired: slot retired

	// 2^32 ms later, the counter is back inside the original hold window
	CHECK_FALSE(h.is_lit(0, t + Hold / 2));
}
