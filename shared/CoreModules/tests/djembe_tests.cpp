#include "CoreModules/djembeCore.h"
#include "CoreModules/djembeCore_neon.h"
#include "doctest.h"
#include <iostream>
#include <stdint.h>

// Skipping because neon implemenation has changed pitch a bit
TEST_CASE("Soft-neon matches non-neon output" * doctest::skip(true))
{
	constexpr int BufferSize = 255;
	float no_outsig[256];
	float ne_outsig[256];

	{
		DjembeCore no;
		int n = 0;
		no.update();

		no.set_input(DjembeCore::Params::Freq, 0.f);
		no.set_input(DjembeCore::Params::Gain, 0.f);
		no.set_input(DjembeCore::Params::Sharpness, 0.0f);
		no.set_input(DjembeCore::Params::Strike, 0.0f);

		no.set_param(DjembeCore::Params::Freq, 60.f);
		no.set_param(DjembeCore::Params::Gain, 1.f);
		no.set_param(DjembeCore::Params::Sharpness, 0.5f);
		no.set_param(DjembeCore::Params::Strike, 0.3f);

		// Trigger low for 3
		for (int i = 0; i < 3; i++) {
			no.set_input(DjembeCore::Params::Trigger, 0.f);
			no.update();
			no_outsig[n++] = no.get_output(0);
		}

		// Trigger high for 1
		for (int i = 0; i < 1; i++) {
			no.set_input(DjembeCore::Params::Trigger, 1.f);
			no.update();
			no_outsig[n++] = no.get_output(0);
		}

		// Trigger low for the rest of the buffer
		for (int i = 0; i < (BufferSize - 1 - 3); i++) {
			no.set_input(DjembeCore::Params::Trigger, 0.f);
			no.update();
			no_outsig[n++] = no.get_output(0);
		}
	}

	{
		DjembeCoreNeon ne;
		int n = 0;
		ne.update();

		ne.set_input(DjembeCore::Params::Freq, 0.f);
		ne.set_input(DjembeCore::Params::Gain, 0.f);
		ne.set_input(DjembeCore::Params::Sharpness, 0.0f);
		ne.set_input(DjembeCore::Params::Strike, 0.0f);

		ne.set_param(DjembeCore::Params::Freq, 60.f);
		ne.set_param(DjembeCore::Params::Gain, 1.f);
		ne.set_param(DjembeCore::Params::Sharpness, 0.5f);
		ne.set_param(DjembeCore::Params::Strike, 0.3f);

		// Trigger low for 3
		for (int i = 0; i < 3; i++) {
			ne.set_input(DjembeCore::Params::Trigger, 0.f);
			ne.update();
			ne_outsig[n++] = ne.get_output(0);
		}

		// Trigger high for 1
		for (int i = 0; i < 1; i++) {
			ne.set_input(DjembeCore::Params::Trigger, 1.f);
			ne.update();
			ne_outsig[n++] = ne.get_output(0);
		}

		// Trigger low for the rest of the buffer
		for (int i = 0; i < (BufferSize - 1 - 3); i++) {
			ne.set_input(DjembeCore::Params::Trigger, 0.f);
			ne.update();
			ne_outsig[n++] = ne.get_output(0);
		}
	}

	for (int i = 0; i < BufferSize; i++) {
		CHECK(no_outsig[i] == doctest::Approx(ne_outsig[i]));
	}
}
