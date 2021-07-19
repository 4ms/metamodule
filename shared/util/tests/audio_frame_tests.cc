#include "../audio_frame.hh"
#include "doctest.h"

using AudioFrame = GenericAudioFrame<int32_t, 24>;
TEST_CASE("audio_frame_tests: input_scales")
{
	AudioFrame a;

	a.chan[0] = 0x00000000;
	CHECK(((float)AudioFrame::scaleInput(a.chan[0])) == doctest::Approx(0.0));

	a.chan[0] = 0x00400000;
	CHECK(((float)AudioFrame::scaleInput(a.chan[0])) == doctest::Approx(0.5));

	a.chan[0] = 0x007FFFFF;
	CHECK(((float)AudioFrame::scaleInput(a.chan[0])) == doctest::Approx(1.0));

	a.chan[1] = 0x800000;
	CHECK(((float)AudioFrame::scaleInput(a.chan[1])) == doctest::Approx(-1.0));

	a.chan[1] = 0xC00000;
	CHECK(((float)AudioFrame::scaleInput(a.chan[1])) == doctest::Approx(-0.5));

	a.chan[1] = 0xFFFFFF;
	CHECK(((float)AudioFrame::scaleInput(a.chan[1])) == doctest::Approx(0.0));
}

TEST_CASE("audio_frame_tests: output_scales")
{
	const float smallest_val = 1.f / 8388608.f;
	CHECK(AudioFrame::scaleOutput(-1.f) == -8388608);
	CHECK(AudioFrame::scaleOutput(-1.f + smallest_val) == -8388607);
	CHECK(AudioFrame::scaleOutput(-1.f + 2 * smallest_val) == -8388606);

	CHECK(AudioFrame::scaleOutput(-0.5f) == -4194304);

	CHECK(AudioFrame::scaleOutput(-2 * smallest_val) == -2);
	CHECK(AudioFrame::scaleOutput(-smallest_val) == -1);
	CHECK(AudioFrame::scaleOutput(0.f) == 0);
	CHECK(AudioFrame::scaleOutput(smallest_val) == 1);
	CHECK(AudioFrame::scaleOutput(2 * smallest_val) == 2);

	CHECK(AudioFrame::scaleOutput(0.125f) == 0x100000);
	CHECK(AudioFrame::scaleOutput(0.25f) == 0x200000);
	CHECK(AudioFrame::scaleOutput(0.5f) == 0x400000);

	CHECK(AudioFrame::scaleOutput(1.0f - 2 * smallest_val) == 0x7FFFFE);
	CHECK(AudioFrame::scaleOutput(1.0f - smallest_val) == 0x7FFFFF);
	CHECK(AudioFrame::scaleOutput(1.0f) == 0x7FFFFF);
}
