#include "CppUTest/TestHarness.h"
#include "fff.h"
#include "frame_buffer_led.hh"

TEST_GROUP(frame_buffer_led_tests)
{
	uint32_t fb[12];
	const uint32_t DUMMYVAL = 55;

	void setup()
	{
		for (uint8_t i = 0; i < 12; i++) {
			fb[i] = DUMMYVAL;
		}
	}

	void teardown() {}
};

TEST(frame_buffer_led_tests, init_doesnt_change_buffer)
{
	FrameBufferLED led{&fb[0]};
	LONGS_EQUAL(DUMMYVAL, fb[0]);
}

TEST(frame_buffer_led_tests, set_and_read_first_value_of_array)
{
	FrameBufferLED led{&fb[0]};
	int kShiftAmount = 20; //Todo: this is the result of what should be a template param for FrameBufferLED
	led.set(12);
	LONGS_EQUAL(12 << kShiftAmount, fb[0]);
}

TEST(frame_buffer_led_tests, set_and_read_last_value_of_array)
{
	FrameBufferLED led{&fb[11]};
	led.set(65536U);
	LONGS_EQUAL(65536U << 16, fb[11]);
}

TEST(frame_buffer_led_tests, set_32b_value_doesnt_overflow)
{
	FrameBufferLED led{&fb[2]};
	led.set(0xFFFFFFFF);
	LONGS_EQUAL(DUMMYVAL, fb[1]);
	LONGS_EQUAL(DUMMYVAL, fb[3]);
}
