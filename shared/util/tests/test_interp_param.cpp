
#include "interp_param.hh"
#include <array>

TEST_CASE("interp_param_tests: inits_to_zero")
{
	Interp<float, 6> x;
	CHECK(x.cur_val == 0.f);
	CHECK(x.next() == 0.f);
}

TEST_CASE("interp_param_tests: basic_usage")
{
	Interp<float, 6> x;
	x.set_new_value(12.f);
	CHECK(x.next() == 2.0f);
	CHECK(x.next() == 4.0f);
	CHECK(x.next() == 6.0f);
	CHECK(x.next() == 8.0f);
	CHECK(x.next() == 10.0f);
	CHECK(x.next() == 12.0f);
}

TEST_CASE("interp_param_tests: many_many_updates")
{
	const unsigned int updates = 0x1000000;
	Interp<double, updates> x;

	x.set_new_value(123456789.0);
	for (unsigned int i = 0; i < (updates - 1); i++)
		x.next();

	DOUBLES_EQUAL(123456789.0, x.next(), 0.000001);
}

TEST_CASE("interp_param_tests: goes_negative")
{
	Interp<long, 3> x;
	x.set_new_value(-12L);
	LONGS_EQUAL(-4L, x.next());
	LONGS_EQUAL(-8L, x.next());
	LONGS_EQUAL(-12L, x.next());
}

TEST_CASE("interp_param_tests: two_updates_opposite_directions")
{
	Interp<long, 3> x;
	x.set_new_value(-12L);
	LONGS_EQUAL(-4L, x.next());
	LONGS_EQUAL(-8L, x.next());
	LONGS_EQUAL(-12L, x.next());
	x.set_new_value(9L);
	LONGS_EQUAL(-5L, x.next());
	LONGS_EQUAL(2L, x.next());
	LONGS_EQUAL(9L, x.next());
}

TEST_CASE("interp_param_tests: overflow_keeps_incrementing")
{
	Interp<float, 6> x;
	x.set_new_value(12.f);
	CHECK(x.next() == 2.0f);
	CHECK(x.next() == 4.0f);
	CHECK(x.next() == 6.0f);
	CHECK(x.next() == 8.0f);
	CHECK(x.next() == 10.0f);
	CHECK(x.next() == 12.0f);
	FLOATS_NEARLY_EQUAL(14.0f, x.next());
}

TEST_CASE("interp_param_tests: zero_breaks")
{
	// Interp<float, 0> x;
}

TEST_CASE("interp_param_tests: step_size_is_nearly_zero_if_value_doesnt_change")
{
	Interp<float, 1> x;
	x.set_new_value(12.f);
	CHECK(x.next() == 12.f);
	x.set_new_value(12.f);
	FLOATS_NEARLY_EQUAL(x.get_step_size(), (float)0.f);
}
