#include "calibrator.hh"
#include "doctest.h"
#include <limits>

TEST_CASE("Basic usage: inputting the high and low notes used to calibrate, gives the target high and low notes") {
	Calibrator c;

	constexpr int LowNote = 2;
	constexpr int HighNote = 4;

	SUBCASE("provide a zero measurement to check linearity better") {
		bool good = c.calibrate_chan<LowNote, HighNote>(-0.02, 0.22, 0.46);
		CHECK(good == true);

		bool bad = c.calibrate_chan<LowNote, HighNote>(-0.12, 0.22, 0.46);
		CHECK(bad == false);
	}

	c.calibrate_chan<LowNote, HighNote>(0.22, 0.46);
	CHECK(c.adjust(0.22) == doctest::Approx(LowNote));
	CHECK(c.adjust(0.46) == doctest::Approx(HighNote));

	SUBCASE("Linearly extrapolated") {
		CHECK(c.adjust((0.22 + 0.46) / 2) == (HighNote + LowNote) / 2);

		float octave = (0.46f - 0.22f) / 2;
		CHECK(c.adjust(0.22f - 2 * octave) == doctest::Approx(LowNote - 2.f));
		CHECK(c.adjust(0.22f - octave) == doctest::Approx(LowNote - 1.f));
		CHECK(c.adjust(0.46f + octave) == doctest::Approx(HighNote + 1.f));
		CHECK(c.adjust(0.46f + 2 * octave) == doctest::Approx(HighNote + 2.f));
	}
}

TEST_CASE("Works to convert 32-bit ints to -1.0...+1.0 float") {
	Calibrator c;
	constexpr int32_t LowVal = -32768;
	constexpr int32_t HighVal = 32768;
	constexpr int32_t LowVal24 = 0xFF800000;
	constexpr int32_t HighVal24 = 0x007FFFFF;

	SUBCASE("16 bit signed") {
		c.calibrate_chan<LowVal, HighVal>(-1., 1.);
		CHECK(c.adjust(0) == doctest::Approx(0.));
		CHECK(c.adjust(0.5) == doctest::Approx(16384));
		CHECK(c.adjust(-0.5) == doctest::Approx(-16384));
	}

	SUBCASE("24 bit signed") {
		c.calibrate_chan<LowVal24, HighVal24>(-1., 1.);

		// Range is asymmetrical (-8388608 to +8388607) so 0 is not the center
		CHECK(c.adjust(0) == doctest::Approx(-1.));
		CHECK(c.adjust(1.0f / 8388608.f) == doctest::Approx(0.));
		CHECK(c.adjust(2.0f / 8388608.f) == doctest::Approx(1.));
	}

	SUBCASE("24 bit with uneven range calibrated on a subset (2V/4V)") {
		constexpr uint32_t TenVolts = HighVal24;
		constexpr uint32_t TwoVolts = TenVolts / 5;
		constexpr uint32_t FourVolts = TwoVolts * 2;

		c.calibrate_chan<TwoVolts, FourVolts>(0.1938f, 0.3848f);
		CHECK(c.adjust(0.3848) == doctest::Approx(FourVolts));
		CHECK(c.adjust(0.1938) == doctest::Approx(TwoVolts));
		CHECK(c.adjust(0.1938 - (0.3848 - 0.1938)) ==
			  doctest::Approx(0).epsilon(0.2)); // epsilon 0.2 in a range of 2^24 is quite small!
		CHECK(c.adjust(0.3848 + (0.3848 - 0.1938)) == doctest::Approx(TwoVolts + FourVolts));
	}
}

TEST_CASE("Default values mean input doesn't change when 'adjusted'") {
	Calibrator c;
	CHECK(c.adjust(12.29f) == 12.29f);
	CHECK(c.adjust(-1.1f) == -1.1f);
	CHECK(c.adjust(0.f) == doctest::Approx(0.f));
}
