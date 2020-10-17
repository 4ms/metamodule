#include "CppUTest/TestHarness.h"
#include "audio_frame.hh"
#include "fff.h"

TEST_GROUP(audio_frame_tests){void setup(){}

							  void teardown(){}};
#define FLOATS_NEARLY_EQUAL(e, a) DOUBLES_EQUAL(static_cast<double>(e), static_cast<double>(a), 0.000001);

using AudioFrame = GenericAudioFrame<int32_t, 24>;
TEST(audio_frame_tests, input_scales)
{
	AudioFrame a;

	a.l = 0x00000000;
	FLOATS_NEARLY_EQUAL(0.0f, AudioFrame::scaleInput(a.l));

	a.l = 0x00400000;
	FLOATS_NEARLY_EQUAL(0.5f, AudioFrame::scaleInput(a.l));

	a.l = 0x007FFFFF;
	FLOATS_NEARLY_EQUAL(1.0f, AudioFrame::scaleInput(a.l));

	a.r = 0x800000;
	FLOATS_NEARLY_EQUAL(-1.0f, AudioFrame::scaleInput(a.r));

	a.r = 0xC00000;
	FLOATS_NEARLY_EQUAL(-0.5f, AudioFrame::scaleInput(a.r));

	a.r = 0xFFFFFF;
	FLOATS_NEARLY_EQUAL(0.0f, AudioFrame::scaleInput(a.r));
}

TEST(audio_frame_tests, output_scales)
{
	const float smallest_val = 1.f / 8388608.f;
	LONGS_EQUAL(-8388608, AudioFrame::scaleOutput(-1.f));
	LONGS_EQUAL(-8388607, AudioFrame::scaleOutput(-1.f + smallest_val));
	LONGS_EQUAL(-8388606, AudioFrame::scaleOutput(-1.f + 2 * smallest_val));

	LONGS_EQUAL(-4194304, AudioFrame::scaleOutput(-0.5f));

	LONGS_EQUAL(-2, AudioFrame::scaleOutput(-2 * smallest_val));
	LONGS_EQUAL(-1, AudioFrame::scaleOutput(-smallest_val));
	LONGS_EQUAL(0, AudioFrame::scaleOutput(0.f));
	LONGS_EQUAL(1, AudioFrame::scaleOutput(smallest_val));
	LONGS_EQUAL(2, AudioFrame::scaleOutput(2 * smallest_val));

	LONGS_EQUAL(0x100000, AudioFrame::scaleOutput(0.125f));
	LONGS_EQUAL(0x200000, AudioFrame::scaleOutput(0.25f));
	LONGS_EQUAL(0x400000, AudioFrame::scaleOutput(0.5f));

	LONGS_EQUAL(0x7FFFFE, AudioFrame::scaleOutput(1.0f - 2 * smallest_val));
	LONGS_EQUAL(0x7FFFFF, AudioFrame::scaleOutput(1.0f - smallest_val));
	LONGS_EQUAL(0x7FFFFF, AudioFrame::scaleOutput(1.0f));
}
