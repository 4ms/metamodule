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
	for (int i = 0; i < 10; i++) {
		float value = (rand() % 100) / 100.0f;
		CHECK(originalFreqToNorm(value) == doctest::Approx(freqToNorm(value)));
	}

	SUBCASE("Check 0 equals NAN or +/-INF")
	{
		float val = freqToNorm(0.f);
		bool equals_pos_inf = (val == INFINITY);
		bool equals_neg_inf = (val == -INFINITY);
		bool equals_nan = (val == NAN);
		CHECK((equals_neg_inf || equals_pos_inf || equals_nan));
	}

	SUBCASE("Check 20 returns 0")
	{
		CHECK(freqToNorm(20.f) == doctest::Approx(0.f));
	}
}

