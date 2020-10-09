#include "CppUTest/TestHarness.h"
#include "util/interp_array.hh"
#include <fff.h>

#define FLOATS_NEARLY_EQUAL(e, a) DOUBLES_EQUAL(static_cast<double>(e), static_cast<double>(a), 0.000001);

TEST_GROUP(interp_array_tests){

	void setup(){}

	void teardown(){}

};

TEST(interp_array_tests, inits_with_single_value_sets_just_first_element)
{
	InterpArray<long, 4> x = {42};
	LONGS_EQUAL(42, x[0]);
	LONGS_EQUAL(0, x[1]);
	LONGS_EQUAL(0, x[2]);
	LONGS_EQUAL(0, x[2]);
}

TEST(interp_array_tests, inits_to_multiple_values)
{
	InterpArray<long, 3> x = {42, 43, 44};
	LONGS_EQUAL(42, x[0]);
	LONGS_EQUAL(43, x[1]);
	LONGS_EQUAL(44, x[2]);
}

TEST(interp_array_tests, basic_usage_by_phase)
{
	InterpArray<long, 4> x;
	x[0] = 200;	 // 0
	x[1] = 300;	 // 0.333
	x[2] = 400;	 // 0.666
	x[3] = 4000; // 1
	FLOATS_NEARLY_EQUAL(4000.f, x.interp(1.f));
	FLOATS_NEARLY_EQUAL(400.f, x.interp(0.666666666f));
	FLOATS_NEARLY_EQUAL(350.f, x.interp(0.5f));
	FLOATS_NEARLY_EQUAL(300.f, x.interp(0.3333333333f));
	FLOATS_NEARLY_EQUAL(200.f, x.interp(0.f));
}

TEST(interp_array_tests, floats_by_phase)
{
	InterpArray<float, 3> x;
	x[0] = 100.f;  // 0
	x[1] = 200.f;  // 0.5
	x[2] = 2000.f; // 1

	float expected_0_75 = (x[1] + x[2]) / 2.f;
	FLOATS_NEARLY_EQUAL(expected_0_75, x.interp(0.75f));

	float expected_0_875 = (expected_0_75 + x[2]) / 2.f;
	FLOATS_NEARLY_EQUAL(expected_0_875, x.interp(0.875f));
}

TEST(interp_array_tests, basic_usage_by_index)
{
	InterpArray<long, 300> x;
	x[201] = 4200;
	x[202] = 4300;
	FLOATS_NEARLY_EQUAL(4300.f, x.interp_by_index(202.f));
	FLOATS_NEARLY_EQUAL(4275.f, x.interp_by_index(201.75f));
	FLOATS_NEARLY_EQUAL(4250.f, x.interp_by_index(201.5f));
	FLOATS_NEARLY_EQUAL(4225.f, x.interp_by_index(201.25f));
	FLOATS_NEARLY_EQUAL(4200.f, x.interp_by_index(201.f));
}

TEST(interp_array_tests, floats_by_index)
{
	InterpArray<float, 3> x;
	x[0] = 100.f;
	x[1] = 200.f;
	FLOATS_NEARLY_EQUAL(115.6f, x.interp_by_index(0.156f));
}

TEST(interp_array_tests, wrapping_by_phase) {}

TEST(interp_array_tests, wrapping_by_index) {}

TEST(interp_array_tests, basic_usage_of_closest)
{
	InterpArray<float, 3> x;
	x[0] = 100.f;
	x[1] = 200.f;
	x[2] = 150.f;
	FLOATS_NEARLY_EQUAL(100.f, x.closest(0.0f));
	FLOATS_NEARLY_EQUAL(100.f, x.closest(0.49999f));
	FLOATS_NEARLY_EQUAL(200.f, x.closest(0.5f));
	FLOATS_NEARLY_EQUAL(200.f, x.closest(0.6f));
	FLOATS_NEARLY_EQUAL(200.f, x.closest(0.9999f));
	FLOATS_NEARLY_EQUAL(150.f, x.closest(1.f));
}

TEST(interp_array_tests, wrapping_with_closest)
{
	InterpArray<float, 3> x;
	x[0] = 100.f;
	x[1] = 200.f;
	x[2] = 150.f;
	FLOATS_NEARLY_EQUAL(150.f, x.closest_wrap(1.f));
	FLOATS_NEARLY_EQUAL(150.f, x.closest_wrap(1.499f));

	FLOATS_NEARLY_EQUAL(100.f, x.closest_wrap(1.5f));
	FLOATS_NEARLY_EQUAL(100.f, x.closest_wrap(1.999f));

	FLOATS_NEARLY_EQUAL(200.f, x.closest_wrap(2.0f));
	FLOATS_NEARLY_EQUAL(200.f, x.closest_wrap(2.4999f));
}
