#include "CppUTest/TestHarness.h"
#include "drivers/pin.hh"
#include "drivers/rotary.hh"
#include "fake_gpio.h"
#include <fff.h>

TEST_GROUP(rotary_tests)
{
	RotaryEncoder<RotaryHalfStep> r{GPIO::A, 0, GPIO::B, 1};

	void setup() {}

	void teardown() {}
};

TEST(rotary_tests, starts_at_zero)
{
	auto init_state = r.read();
	LONGS_EQUAL(0, init_state);
}

TEST(rotary_tests, starts_at_zero)
{
	auto init_state = r.read();
	LONGS_EQUAL(0, init_state);
}
