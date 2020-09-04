#include "CppUTest/TestHarness.h"
#include "drivers/pin.hh"
#include "drivers/rotary.hh"
#include "fake_gpio.h"
#include <fff.h>

TEST_GROUP(rotary_tests){

	//RotaryEncoder<RotaryHalfStep> r{GPIO::A, 0, GPIO::B, 1};

	void setup(){}

	void teardown(){}};

TEST(rotary_tests, starts_at_zero)
{
	bool initval = read_fake_pin(FakeGPIO::B, 1);
	CHECK_FALSE(initval);

	set_fake_pin(FakeGPIO::B, 1, true);
	bool postval = read_fake_pin(FakeGPIO::B, 1);
	CHECK_TRUE(postval);

	set_fake_pin(FakeGPIO::B, 1, false);
	postval = read_fake_pin(FakeGPIO::B, 1);
	CHECK_FALSE(postval);
}
