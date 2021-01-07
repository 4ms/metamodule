
#include "util/math_tables.hh"

#include <iostream>

const float FTWOPI = 2.f * (float)M_PI;

TEST_CASE("math_table_tests: sinTable_starts_at_0")
{
	FLOATS_NEARLY_EQUAL(0.f, sinTable[0]);
}

TEST_CASE("math_table_tests: sinTable_is_approx_sin")
{
	int table_size = sizeof(sinTable) / sizeof(float);

	for (int i = 0; i < table_size; i++) {
		float x = ((float)i / (float)table_size) * FTWOPI;
		FLOATS_NEARLY_EQUAL(sinf(x), sinTable[i]);
	}
}

TEST_CASE("math_table_tests: sinTable_wraps")
{
	int table_size = sizeof(sinTable) / sizeof(float);

	float x = FTWOPI;
	FLOATS_NEARLY_EQUAL(sinf(x), sinTable[0]);
	x += (1.f / (float)table_size) * FTWOPI;
	FLOATS_NEARLY_EQUAL(sinf(x), sinTable[1]);
}

TEST_CASE("math_table_tests: sinTable_interp")
{
	for (float x = 0; x < 1.f; x += 0.001f) {
		float rad = x * FTWOPI;
		FLOATS_NEARLY_EQUAL(sinf(rad), sinTable.interp(x));
	}
}

TEST_CASE("math_table_tests: sinTable_interp_wrap")
{
	float x = 1.0f;
	FLOATS_NEARLY_EQUAL(sinf(x * FTWOPI), sinTable.interp_wrap(x));

	// x += 0.001f;
	// FLOATS_NEARLY_EQUAL(sinf(x * FTWOPI), sinTable.interp_wrap(x));
}
