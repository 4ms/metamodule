#include "doctest.h"
#include "processors/fadeloop.hh"
#include "util/interp_array.hh"
#include <iostream>
#include <stdint.h>

TEST_CASE("FadeloopExt basic usage")
{
	int loops;

	SUBCASE("Can use C_style array")
	{
		float _buf[100];
		FadeLoopExt2 fl2{_buf};
		loops = 0;
		while (fl2.process(1.f) != 1.f)
			loops++;
		CHECK(loops == 100);
	}

	SUBCASE("Can use std::array")
	{
		FadeLoopExt2 fl3{*(new std::array<float, 20>)};
		loops = 0;
		while (fl3.process(1.f) != 1.f)
			loops++;
		CHECK(loops == 20);
	}

	SUBCASE("Can use dynamic memory")
	{
		using BigDynArray = BigAlloc<std::array<float, 100>>;
		BigDynArray *dynbuf = new BigDynArray;
		FadeLoopExt2 bigfl{*dynbuf};
		loops = 0;
		while (bigfl.process(1.f) != 1.f)
			loops++;
		CHECK(loops == 100);

		FadeLoopExt2 bigfl2{*(new BigAlloc<InterpArray<float, 100>>)};
		loops = 0;
		while (bigfl2.process(1.f) != 1.f)
			loops++;
		CHECK(loops == 100);
	}

	SUBCASE("ext3: Can use C_style array")
	{
		float _buf[100];
		FadeLoopExt3 fl2{&_buf};
		loops = 0;
		while (fl2.process(1.f) != 1.f)
			loops++;
		CHECK(loops == 100);
	}

	SUBCASE("Can use std::array")
	{
		FadeLoopExt3 fl3{new std::array<float, 20>};
		loops = 0;
		while (fl3.process(1.f) != 1.f)
			loops++;
		CHECK(loops == 20);
	}

	SUBCASE("ext3: Can use dynamic memory")
	{
		using BigDynArray = BigAlloc<std::array<float, 100>>;
		BigDynArray *dynbuf = new BigDynArray;
		FadeLoopExt3 bigfl{dynbuf};
		loops = 0;
		while (bigfl.process(1.f) != 1.f)
			loops++;
		CHECK(loops == 100);

		FadeLoopExt3 bigfl2{new BigAlloc<InterpArray<float, 100>>};
		loops = 0;
		while (bigfl2.process(1.f) != 1.f)
			loops++;
		CHECK(loops == 100);
	}
}

TEST_CASE("Fadeloop basic usage")
{
	constexpr unsigned long max_buffer_size = 100;
	FadeLoop<float, max_buffer_size> fl;

	float out;

	SUBCASE("All outputs are zero initially")
	{
		bool all_outputs_zero = true;
		int loops = max_buffer_size;
		while (loops--) {
			out = fl.process(99999);
			if (out != 0.f)
				all_outputs_zero = false;
		}
		CHECK(all_outputs_zero);
	}

	SUBCASE("Simple delay: comes out as it went in after one delay period set by change_delay()")
	{
		const float initial_input = 0.3245f; // just some random number
		const int length = 10;
		fl.change_delay(length);
		fl.set_fade_speed(1.0f); // instant fading

		fl.process(initial_input);
		int loops = length;
		while (loops--) {
			out = fl.process(0);
			if (loops > 0)
				CHECK(out == doctest::Approx(0.f));
			else
				CHECK(out == doctest::Approx(initial_input));
		}
	}

	SUBCASE("Fading")
	{
		const float initial_input = 0.555555f;
		const int length = 30;
		const int loopsToFade = 8;

		fl.change_delay(length);
		fl.set_fade_speed(1.0f / (float)loopsToFade);

		SUBCASE("Crossfades for correct number of process() calls (=1/fadeSpeed)")
		{
			for (int loops = 0; loops < 30; loops++) {
				if (loops < loopsToFade)
					CHECK(fl.is_crossfading());
				else
					CHECK_FALSE(fl.is_crossfading());
				fl.process(loops == 0 ? initial_input : 0);
			}
		}
		SUBCASE("Crossfade to a blank section fades output down to zero over period of the fade")
		{
			// process enough samples so that we start to get a non-zero output
			out = 0.f;
			while (out == 0.f) {
				out = fl.read();
				fl.write(initial_input);
			}

			// starting fading the read head to somewhere that is blank
			const int length2 = length + max_buffer_size / 2;
			fl.change_delay(length2);

			float out;
			float xfade_phase = 0.f;
			for (int loops = 0; loops <= loopsToFade; loops++) {
				out = fl.read();
				fl.write(12345.f);

				float expected_out = MathTools::interpolate(initial_input, 0.f, xfade_phase);
				xfade_phase += 1.f / (float)loopsToFade;
				CHECK(out == doctest::Approx(expected_out));
			}
		}
	}

	SUBCASE("Queued crossfading")
	{
		const int length = 60;
		const int loopsToFade = 8;

		fl.change_delay(length);
		fl.set_fade_speed(1.0f / (float)loopsToFade);

		SUBCASE("Queued crossfade loads after first one is done")
		{
			float signal1 = 0.1234f;
			float signal2 = 0.9876f;

			// Fill buffer with half 1's and half 2's
			// [11111112222222]
			for (unsigned i = 0; i < length / 2; i++)
				fl.process(signal1);

			for (unsigned i = 0; i < length / 2; i++)
				fl.process(signal2);

			// Start a crossfade from start of 1's to start of 2's
			fl.change_delay(length / 2);

			float out;
			for (int loops = 0; loops < loopsToFade; loops++) {
				out = fl.process(0);

				// Half-way through the crossfade, queue another one to blank memory
				if (loops == loopsToFade / 2)
					fl.change_delay(1);

				// Expected output should not care that we have a queued crossfade
				float expected_out = MathTools::interpolate(signal1, signal2, (float)loops / (float)loopsToFade);
				CHECK(out == doctest::Approx(expected_out));
			}

			// Now check that we're crossfading to blank memory
			for (int loops = 0; loops < loopsToFade; loops++) {
				out = fl.process(0);
				float expected_out = MathTools::interpolate(signal2, 0, (float)loops / (float)loopsToFade);
				CHECK(out == doctest::Approx(expected_out));
			}
		}
	}
}
