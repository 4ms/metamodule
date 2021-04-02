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
}