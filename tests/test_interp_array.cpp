#include "CppUTest/TestHarness.h"
#include "util/interp_array.hh"
#include <fff.h>

// #define FLOATS_NEARLY_EQUAL(e, a)                                                                  \
// 	DOUBLES_EQUAL(static_cast<double>(e), static_cast<double>(a), 0.000001);

TEST_GROUP(interp_array_tests){

	void setup(){}

	void teardown(){}

};

TEST(interp_array_tests, inits_to_value)
{
	InterpArray<long, 6> x{42};
	LONGS_EQUAL(42, x[0]);
	LONGS_EQUAL(42, x[1]);
	LONGS_EQUAL(42, x[2]);
}

