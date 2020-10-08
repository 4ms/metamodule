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
	float maxv = 8388607.f / 8388608.f;

	LONGS_EQUAL(0x800000, 0x00FFFFFF & AudioFrame::scaleOutput(-1.f));
	LONGS_EQUAL(0xC00000, 0x00FFFFFF & AudioFrame::scaleOutput(-0.5f));
	LONGS_EQUAL(0, AudioFrame::scaleOutput(0.f));
	LONGS_EQUAL(0x400000, AudioFrame::scaleOutput(0.5f));
	LONGS_EQUAL(0x7FFFFF, AudioFrame::scaleOutput(maxv));
}
