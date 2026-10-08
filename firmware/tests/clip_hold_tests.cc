#include "doctest.h"
#include "gui/notify/clip_hold.hh"

using MetaModule::ClipHold;

TEST_CASE("ClipHold: nothing lit initially") {
	ClipHold<16> h;
	for (unsigned i = 0; i < 16; i++)
		CHECK_FALSE(h.is_lit(i, 1000));
}

TEST_CASE("ClipHold: lit for HoldMs after a hit, then off") {
	ClipHold<16> h;
	h.update(0b10, 1000);
	CHECK(h.is_lit(1, 1000));
	CHECK(h.is_lit(1, 1499));
	CHECK_FALSE(h.is_lit(1, 1500));
	CHECK_FALSE(h.is_lit(0, 1000));
}

TEST_CASE("ClipHold: re-hit extends hold; slots are independent") {
	ClipHold<16> h;
	h.update(0b01, 1000);
	h.update(0b10, 1300);
	h.update(0b01, 1400);
	CHECK(h.is_lit(0, 1899));
	CHECK_FALSE(h.is_lit(0, 1900));
	CHECK(h.is_lit(1, 1799));
	CHECK_FALSE(h.is_lit(1, 1800));
}

TEST_CASE("ClipHold: empty mask does not extend") {
	ClipHold<16> h;
	h.update(0b1, 1000);
	h.update(0, 1400);
	CHECK_FALSE(h.is_lit(0, 1500));
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
	uint32_t t = 0xFFFF'FF00; // 256 ms before wrap
	h.update(0b1, t);
	CHECK(h.is_lit(0, t + 100));
	CHECK(h.is_lit(0, t + 499)); // wrapped past 0
	CHECK_FALSE(h.is_lit(0, t + 500));
	CHECK_FALSE(h.is_lit(0, t + 0x8000'0000u)); // long after: not stuck on
}

TEST_CASE("ClipHold: expired slot doesn't relight when the tick counter wraps all the way around") {
	ClipHold<16> h;
	h.update(0b1, 1000);
	h.update(0, 2000); // expired: slot retired

	// 2^32 ms later, the counter reads 1100 again
	CHECK_FALSE(h.is_lit(0, 1100));
}
