#include "CppUTest/TestHarness.h"
#include "pin.hh"
#include "fake_gpio.h"
#include <fff.h>

TEST_GROUP(fake_gpio_tests){

	void setup(){}

	void teardown(){}};

TEST(fake_gpio_tests, fake_pin_init_at_0)
{
	bool initval = read_fake_pin(FakeGPIO::B, 1);
	CHECK_FALSE(initval);
}

TEST(fake_gpio_tests, fake_pin_reads_what_was_written)
{
	set_fake_pin(FakeGPIO::B, 1, true);
	bool postval = read_fake_pin(FakeGPIO::B, 1);
	CHECK_TRUE(postval);

	set_fake_pin(FakeGPIO::B, 1, false);
	postval = read_fake_pin(FakeGPIO::B, 1);
	CHECK_FALSE(postval);
}
