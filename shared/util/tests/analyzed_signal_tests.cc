#include "../analyzed_signal.hh"
#include "doctest.h"

TEST_CASE("Basic usage") {

	AnalyzedSignal<100> s;

	for (int i = 12; i < 112; i++)
		s.update(i);

	CHECK(s.min == 12);
	CHECK(s.max == 111);
	// Just a ballpark range:
	CHECK(s.iir > 40);
	CHECK(s.iir < 60);

	SUBCASE("Resetting immediately sets iir value") {
		s.reset_to(200);
		CHECK(s.iir == 200);

		SUBCASE(
			"Resetting to a particular value can change min or max (even if the input signal never hits that value)") {
			for (int i = 12; i < 15; i++)
				s.update(i);

			CHECK(s.min == 12);
			CHECK(s.max == 200);

			SUBCASE("iir is changed because of the value reset to") {
				// Just a ballpark range:
				CHECK(s.iir > 190);
				CHECK(s.iir < 200);
			}
		}
	}
}

TEST_CASE("iir coef math") {
	AnalyzedSignal<2> s; // each sample averages with previous average

	s.reset_to(10);
	s.update(20);
	CHECK(s.iir == 15);

	s.update(20);
	CHECK(s.iir == 17.5);
}
