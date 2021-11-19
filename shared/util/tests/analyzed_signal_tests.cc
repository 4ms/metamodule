#include "../analyzed_signal.hh"
#include "doctest.h"

TEST_CASE("Basic usage") {

	AnalyzedSignal<100> s;

	for (int i = 12; i < 112; i++)
		s.update(i);

	CHECK(s.min == 12);
	CHECK(s.max == 111);
	CHECK(s.iir > 40);
	CHECK(s.iir < 60);

	SUBCASE("Resetting") {
		s.reset_to(200);
		CHECK(s.iir == 200);

		for (int i = 12; i < 112; i++)
			s.update(i);

		CHECK(s.min == 12);
		CHECK(s.max == 200);
		// Just a ballpark range:
		CHECK(s.iir > 100);
		CHECK(s.iir < 120);
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
