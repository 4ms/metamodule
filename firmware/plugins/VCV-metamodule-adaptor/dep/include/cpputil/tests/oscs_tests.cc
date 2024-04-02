#include "doctest.h"
#include "util/oscs.hh"
#include <iostream>

TEST_CASE("Basic TriangleOscillator usage") {
	// 1Hz triangle wave that we update (call Process()) at 100Hz
	const uint32_t updates_per_cycle = 120;
	TriangleOscillator<updates_per_cycle> tri;
	tri.set_frequency(1);

	uint32_t val;
	val = tri.val();
	CHECK(val == 0);

	int loops;
	float val_approx;
	// simulate 1 second, checking value every 0.25 seconds

	loops = updates_per_cycle / 8;
	while (loops--) {
		val = tri.process();
	}
	val_approx = (float)val / (float)(0xFFFFFFFF);
	CHECK(val_approx == doctest::Approx(0.25));

	loops = updates_per_cycle / 8;
	while (loops--) {
		val = tri.process();
	}
	val_approx = (float)val / (float)(0xFFFFFFFF);
	CHECK(val_approx == doctest::Approx(0.50));

	loops = updates_per_cycle / 4;
	while (loops--) {
		val = tri.process();
	}
	val_approx = (float)val / (float)(0xFFFFFFFF);
	CHECK(val_approx == doctest::Approx(1.00));

	loops = updates_per_cycle / 4;
	while (loops--) {
		val = tri.process();
	}
	val_approx = (float)val / (float)(0xFFFFFFFF);
	CHECK(val_approx == doctest::Approx(0.50));

	loops = updates_per_cycle / 4;
	while (loops--) {
		val = tri.process();
	}
	val_approx = (float)val / (float)(0xFFFFFFFF);
	CHECK(val_approx == doctest::Approx(0.00));
}

TEST_CASE("OneShot") {

	auto os = OneShot{48000}; //48kHz = .020833 ms
	os.start(1e-3);

	unsigned expected_updates = 48;
	while (expected_updates--) {
		CHECK(os.update());
	}

	CHECK_FALSE(os.update());
}

TEST_CASE("OneShot Edge case") {

	SUBCASE("1/1") {
		auto os = OneShot{1};
		os.start(1);

		CHECK(os.update());
		CHECK_FALSE(os.update());
	}

	SUBCASE("1/2") {
		auto os = OneShot{2};
		os.start(1);

		CHECK(os.update());
		CHECK(os.update());
		CHECK_FALSE(os.update());
	}

	SUBCASE("2/1") {
		auto os = OneShot{1};
		os.start(2);

		CHECK(os.update());
		CHECK(os.update());
		CHECK_FALSE(os.update());
	}
}
