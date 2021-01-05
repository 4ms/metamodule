#include "CppUTest/TestHarness.h"
#include "util/math_tables.hh"
#include <fff.h>
#include <iostream>

#define FLOATS_NEARLY_EQUAL(e, a) DOUBLES_EQUAL(static_cast<double>(e), static_cast<double>(a), 0.005);

const float FTWOPI = 2.f * (float)M_PI;

TEST_GROUP(math_table_tests){

	void setup(){}

	void teardown(){}

};

TEST(math_table_tests, sinTable_starts_at_0)
{
	FLOATS_NEARLY_EQUAL(0.f, sinTable[0]);
}

TEST(math_table_tests, sinTable_is_approx_sin)
{
	int table_size = sizeof(sinTable) / sizeof(float);

	for (int i = 0; i < table_size; i++) {
		float x = ((float)i / (float)table_size) * FTWOPI;
		FLOATS_NEARLY_EQUAL(sinf(x), sinTable[i]);
	}
}

TEST(math_table_tests, sinTable_wraps)
{
	int table_size = sizeof(sinTable) / sizeof(float);

	float x = FTWOPI;
	FLOATS_NEARLY_EQUAL(sinf(x), sinTable[0]);
	x += (1.f / (float)table_size) * FTWOPI;
	FLOATS_NEARLY_EQUAL(sinf(x), sinTable[1]);
}

TEST(math_table_tests, sinTable_interp)
{
	for (float x = 0; x < 1.f; x += 0.001f) {
		float rad = x * FTWOPI;
		FLOATS_NEARLY_EQUAL(sinf(rad), sinTable.interp(x));
	}
}

TEST(math_table_tests, sinTable_interp_wrap)
{
	float x = 1.0f;
	FLOATS_NEARLY_EQUAL(sinf(x * FTWOPI), sinTable.interp_wrap(x));

	// x += 0.001f;
	// FLOATS_NEARLY_EQUAL(sinf(x * FTWOPI), sinTable.interp_wrap(x));
}
