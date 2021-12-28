#include "doctest.h"
#include "util/math.hh"
#include <iostream>
#include <stdint.h>

using namespace MathTools;

float originalFreqToNorm(float input)
{
	float output = (logf(input) - logf(20)) / (3 * logf(10));
	return output;
}

TEST_CASE("values are equal to original function")
{
	for (int i = 0; i < 20; i++) {
		float value = map_value(static_cast<float>(i), 0.0f, 19.0f, 20.0f, 20000.0f);
		CHECK(originalFreqToNorm(value) == doctest::Approx(audioFreqToNorm(value)));
	}

	SUBCASE("Check value below 20 returns same value as 20")
	{
		CHECK(audioFreqToNorm(20)==audioFreqToNorm(0));
	}

	SUBCASE("Check that value above 20000 returns same value as 20000")
	{
		CHECK(audioFreqToNorm(30000.0f)==audioFreqToNorm(20000.0f));
	}

	SUBCASE("Check 20 returns 0")
	{
		CHECK(audioFreqToNorm(20.f) == doctest::Approx(0.f));
	}
}
