#include "CoreModules/fadeDelayCore.h"
#include "doctest.h"
#include <iostream>
#include <stdint.h>

TEST_CASE("FadeDelayCore basic usage")
{
	constexpr unsigned long max_buffer_size = FadeDelayCore::maxSamples;
	FadeDelayCore fd;

	float out;

	SUBCASE("All outputs are zero if fed only zeros")
	{
		bool all_outputs_zero = true;
		int loops = max_buffer_size + 1;
		while (loops--) {
			fd.set_input(FadeDelayCore::Inputs::AudioIn, 0);
			out = fd.get_output(FadeDelayCore::Outputs::AudioOut);
			if (out != 0.f)
				all_outputs_zero = false;
		}
		CHECK(all_outputs_zero);
	}

	SUBCASE("minimum delay time: comes out as it went in after one sample")
	{
		const float initial_input = 0.3245f;
		const int length = 10;
		fd.set_param(FadeDelayCore::Params::DelayTime, 0);
		fd.set_param(FadeDelayCore::Params::Feedback, 0);
		fd.set_param(FadeDelayCore::Params::Mix, 1.0f);
		fd.set_param(FadeDelayCore::Params::CVAmount, 0);

		fd.set_input(FadeDelayCore::Inputs::AudioIn, 0);

		// Clear fading
		fd.set_param(FadeDelayCore::Params::FadeTime, 0);
		int loops = FadeDelayCore::minFadeTimeInSeconds * 48000;
		while (loops--)
			fd.update();

		// Input: 1 0 0 0 0 0 0 0 0 0
		// Output: 0 1 0 0 0 0 0 0 0 0
		for (int i = 0; i < length; i++) {
			fd.set_input(FadeDelayCore::Inputs::AudioIn, i == 0 ? initial_input : 0);
			fd.update();
			out = fd.get_output(FadeDelayCore::Outputs::AudioOut);
			if (i == FadeDelayCore::minDelayTimeInSamples)
				CHECK(out == doctest::Approx(initial_input));
			else
				CHECK(out == doctest::Approx(0.f));
		}
	}
	SUBCASE("With some feedback, output is at full volume after the first loop, then decreases by the feedback amount "
			"on each subsequent loop (and loop sizes are consistant)")
	{
		const float feedback = 0.4f;
		const float initial_input = 0.73245f; // random number

		fd.set_param(FadeDelayCore::Params::DelayTime, 0.1f);
		fd.set_param(FadeDelayCore::Params::Feedback, feedback);
		fd.set_param(FadeDelayCore::Params::Mix, 1.0f);
		fd.set_param(FadeDelayCore::Params::CVAmount, 0);

		// Clear fading
		fd.set_param(FadeDelayCore::Params::FadeTime, 0);
		int loops = FadeDelayCore::minFadeTimeInSeconds * 48000;
		while (loops--)
			fd.update();

		// input the test signal
		fd.set_input(FadeDelayCore::Inputs::AudioIn, initial_input);
		fd.update();

		// Run the delay until we get our original input back out
		// in order to measure the delay loop time
		long measured_delay_samples = 0;
		const long TIMEOUT = 0xFFFF;
		out = 0.f;
		while (out == 0.f) {
			fd.set_input(FadeDelayCore::Inputs::AudioIn, 0);
			fd.update();
			out = fd.get_output(FadeDelayCore::Outputs::AudioOut);
			measured_delay_samples++;
			if (measured_delay_samples > TIMEOUT)
				break;
		}
		CHECK(measured_delay_samples < TIMEOUT);
		CHECK(out == initial_input);

		out = 0.f;
		for (long i = 0; i < measured_delay_samples; i++) {
			fd.set_input(FadeDelayCore::Inputs::AudioIn, 0);
			fd.update();
			out = fd.get_output(FadeDelayCore::Outputs::AudioOut);
		}
		CHECK(out == doctest::Approx(initial_input * feedback));

		out = 0.f;
		for (long i = 0; i < measured_delay_samples; i++) {
			fd.set_input(FadeDelayCore::Inputs::AudioIn, 0);
			fd.update();
			out = fd.get_output(FadeDelayCore::Outputs::AudioOut);
		}
		CHECK(out == doctest::Approx(initial_input * feedback * feedback));

		out = 0.f;
		for (long i = 0; i < measured_delay_samples; i++) {
			fd.set_input(FadeDelayCore::Inputs::AudioIn, 0);
			fd.update();
			out = fd.get_output(FadeDelayCore::Outputs::AudioOut);
		}
		CHECK(out == doctest::Approx(initial_input * feedback * feedback * feedback));
	}

	SUBCASE("Fading")
	{
		// Todo
	}

	SUBCASE("Queued Fading")
	{
		// Todo
	}

	SUBCASE("Mix")
	{
		// Todo
	}

	SUBCASE("DelayTime range")
	{
		// Todo
	}
}
