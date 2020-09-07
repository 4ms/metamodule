#include "CppUTest/TestHarness.h"
#include "drivers/pin.hh"
#include "drivers/rotary.hh"
#include "fake_gpio.h"
#include <fff.h>

TEST_GROUP(rotary_tests)
{
	RotaryEncoder<RotaryHalfStep> rotary_half_step{GPIO::A, 0, GPIO::B, 1};
	RotaryEncoder<RotaryFullStep> rotary_full_step{GPIO::A, 0, GPIO::B, 1};

	void setup() {}

	void teardown() {}
};
static void set_fake_rotary(uint8_t AB);
static void set_fake_rotary(uint8_t AB)
{
	set_fake_pin(FakeGPIO::A, 0, AB & 0b10 ? false : true);
	set_fake_pin(FakeGPIO::B, 1, AB & 0b01 ? false : true);
}

TEST(rotary_tests, starts_at_zero)
{
	int32_t init_state = rotary_half_step.read();
	LONGS_EQUAL(0, init_state);
}

TEST(rotary_tests, half_step_clockwise)
{
	set_fake_pin(FakeGPIO::A, 0, true);
	set_fake_pin(FakeGPIO::B, 1, true);
	rotary_half_step.update();
	set_fake_pin(FakeGPIO::A, 0, false);
	set_fake_pin(FakeGPIO::B, 1, true);
	rotary_half_step.update();
	set_fake_pin(FakeGPIO::A, 0, false);
	set_fake_pin(FakeGPIO::B, 1, false);
	rotary_half_step.update();

	int32_t new_state = rotary_half_step.read();
	LONGS_EQUAL(1, new_state);
}
TEST(rotary_tests, zeros_after_read)
{
	set_fake_rotary(0b00);
	rotary_half_step.update();
	set_fake_rotary(0b10);
	rotary_half_step.update();
	set_fake_rotary(0b11);
	rotary_half_step.update();

	int32_t first_read = rotary_half_step.read();
	LONGS_EQUAL(1, first_read);
	int32_t second_read = rotary_half_step.read();
	LONGS_EQUAL(0, second_read);
}

TEST(rotary_tests, half_step_cw_starts_at_00)
{
	set_fake_rotary(0b00);
	rotary_half_step.update();
	set_fake_rotary(0b10);
	rotary_half_step.update();
	set_fake_rotary(0b11);
	rotary_half_step.update();

	int32_t new_state = rotary_half_step.read();
	LONGS_EQUAL(1, new_state);
}

TEST(rotary_tests, half_step_ccw_start_at_11)
{
	set_fake_rotary(0b11);
	rotary_half_step.update();
	set_fake_rotary(0b10);
	rotary_half_step.update();
	set_fake_rotary(0b00);
	rotary_half_step.update();

	int32_t new_state = rotary_half_step.read();
	LONGS_EQUAL(-1, new_state);
}

TEST(rotary_tests, half_step_ccw_starts_at_00)
{
	set_fake_rotary(0b00);
	rotary_half_step.update();
	set_fake_rotary(0b01);
	rotary_half_step.update();
	set_fake_rotary(0b11);
	rotary_half_step.update();

	int32_t new_state = rotary_half_step.read();
	LONGS_EQUAL(-1, new_state);
}
TEST(rotary_tests, two_ccw_half_steps)
{
	set_fake_rotary(0b00);
	rotary_half_step.update();
	set_fake_rotary(0b01);
	rotary_half_step.update();
	set_fake_rotary(0b11);
	rotary_half_step.update();
	set_fake_rotary(0b10);
	rotary_half_step.update();
	set_fake_rotary(0b00);
	rotary_half_step.update();

	int32_t new_state = rotary_half_step.read();
	LONGS_EQUAL(-2, new_state);
}

TEST(rotary_tests, full_step_ccw)
{
	set_fake_rotary(0b00);
	rotary_full_step.update();
	set_fake_rotary(0b01);
	rotary_full_step.update();
	set_fake_rotary(0b11);
	rotary_full_step.update();
	set_fake_rotary(0b10);
	rotary_full_step.update();
	set_fake_rotary(0b00);
	rotary_full_step.update();

	LONGS_EQUAL(-1, rotary_full_step.read());
}
TEST(rotary_tests, full_step_cw)
{
	set_fake_rotary(0b00);
	rotary_full_step.update();
	set_fake_rotary(0b10);
	rotary_full_step.update();
	set_fake_rotary(0b11);
	rotary_full_step.update();
	set_fake_rotary(0b01);
	rotary_full_step.update();
	set_fake_rotary(0b00);
	rotary_full_step.update();

	LONGS_EQUAL(1, rotary_full_step.read());
}
TEST(rotary_tests, two_full_steps_cw)
{
	set_fake_rotary(0b00);
	rotary_full_step.update();
	set_fake_rotary(0b10);
	rotary_full_step.update();
	set_fake_rotary(0b11);
	rotary_full_step.update();
	set_fake_rotary(0b01);
	rotary_full_step.update();
	set_fake_rotary(0b00);
	rotary_full_step.update();

	set_fake_rotary(0b10);
	rotary_full_step.update();
	set_fake_rotary(0b11);
	rotary_full_step.update();
	set_fake_rotary(0b01);
	rotary_full_step.update();
	set_fake_rotary(0b00);
	rotary_full_step.update();

	LONGS_EQUAL(2, rotary_full_step.read());
}

