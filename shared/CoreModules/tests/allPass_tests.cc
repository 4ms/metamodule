#include "doctest.h"
#include "processors/allpass.h"
#include <iostream>
#include <stdint.h>

TEST_CASE("Allpass basic usage")
{
	constexpr unsigned long max_buffer_size = 100;
	AllPass<max_buffer_size> ap;

	float out;

	SUBCASE("All outputs are zero if fed only zeros")
	{
		bool all_outputs_zero = true;
		int loops = max_buffer_size + 1;
		while (loops--) {
			out = ap.process(0);
			if (out != 0.f)
				all_outputs_zero = false;
		}
		CHECK(all_outputs_zero);
	}

	SUBCASE("Simple delay: comes out as it went in after one delay period set by setLength()")
	{
		const float initial_input = 0.3245f; // just some random number
		const int length = 10;
		ap.setFeedback(0);
		ap.setLength(length);
		ap.setFadeSpeed(1.0f);

		ap.process(initial_input);
		int loops = length;
		while (loops--) {
			out = ap.process(0);
			if (loops > 0)
				CHECK(out == doctest::Approx(0.f));
			else
				CHECK(out == doctest::Approx(initial_input));
		}
	}

	SUBCASE("With some feedback, output is at full volume after the first loop, then decreases by the feedback amount "
			"on each subsequent loop")
	{
		const int length = 10;
		const float feedback = 0.4f;
		const float initial_input = 0.73245f; // random number
		ap.setFeedback(feedback);
		ap.setLength(length);
		ap.setFadeSpeed(1.0f);

		ap.process(initial_input);

		int loops = length;
		while (loops--) {
			out = ap.process(0);
			if (loops > 0)
				CHECK(out == doctest::Approx(0.f));
			else
				CHECK(out == doctest::Approx(initial_input));
		}

		loops = length;
		while (loops--) {
			out = ap.process(0);
			if (loops > 0)
				CHECK(out == doctest::Approx(0.f));
			else
				CHECK(out == doctest::Approx(initial_input * feedback));
		}

		loops = length;
		while (loops--) {
			out = ap.process(0);
			if (loops > 0)
				CHECK(out == doctest::Approx(0.f));
			else
				CHECK(out == doctest::Approx(initial_input * feedback * feedback));
		}
	}

	SUBCASE("Fading")
	{
		const float initial_input = 0.555555f;
		const int length = 30;
		const float feedback = 0.0f;
		const int loopsToFade = 8;

		ap.setFeedback(feedback);
		ap.setLength(length);
		ap.setFadeSpeed(1.0f / (float)loopsToFade);

		SUBCASE("Crossfades for correct number of process() calls (=1/fadeSpeed)")
		{
			for (int loops = 0; loops < 30; loops++) {
				if (loops < loopsToFade)
					CHECK(ap.is_crossfading());
				else
					CHECK_FALSE(ap.is_crossfading());
				ap.process(loops == 0 ? initial_input : 0);
			}
		}
		SUBCASE("Crossfade to a blank section fades output down to zero over period of the fade")
		{
			// process enough samples so that we start to get a non-zero output
			for (int i = 0; i < length; i++)
				ap.process(initial_input);

			// change read head to somewhere that is silent
			const int length2 = length + 50;
			ap.setLength(length2);

			float out;
			float xfade_phase = 0.f;
			for (int loops = 0; loops <= loopsToFade; loops++) {
				out = ap.process(0);

				float expected_out = MathTools::interpolate(initial_input, 0.f, xfade_phase);
				xfade_phase += 1.f / (float)loopsToFade;
				CHECK(out == doctest::Approx(expected_out));
			}
		}
	}

	SUBCASE("Queued crossfading")
	{
		const int length = 60;
		const float feedback = 0.0f;
		const int loopsToFade = 8;

		ap.setFeedback(feedback);
		ap.setLength(length);
		ap.setFadeSpeed(1.0f / (float)loopsToFade);

		SUBCASE("Queued crossfade loads after first one is done")
		{
			float signal1 = 0.1234f;
			float signal2 = 0.9876f;

			// Fill buffer with 11111112222222
			for (unsigned i = 0; i < length / 2; i++)
				ap.process(signal1);

			for (unsigned i = 0; i < length / 2; i++)
				ap.process(signal2);

			// Start a crossfade from start of 1's to start of 2's
			ap.setLength(length / 2);

			float out;
			for (int loops = 0; loops < loopsToFade; loops++) {
				out = ap.process(0);

				// Half-way through the crossfade, queue another one to blank memory
				if (loops == loopsToFade / 2)
					ap.setLength(1);

				// Expected output should not care that we have a queued crossfade
				float expected_out = MathTools::interpolate(signal1, signal2, (float)loops / (float)loopsToFade);
				CHECK(out == doctest::Approx(expected_out));
			}

			// Now check that we're crossfading to blank memory
			for (int loops = 0; loops < loopsToFade; loops++) {
				out = ap.process(0);
				float expected_out = MathTools::interpolate(signal2, 0, (float)loops / (float)loopsToFade);
				CHECK(out == doctest::Approx(expected_out));
			}
		}
	}
}
