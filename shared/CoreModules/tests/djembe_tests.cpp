//Hack: include the .cc file:
#include "CoreModules/4ms/core/DjembeCore.cc"

#include "CoreModules/4ms/core/DjembeCore_neon.h"
#include "CoreModules/4ms/info/Djembe_info.hh"
#include "doctest.h"
#include <iostream>
#include <stdint.h>

TEST_CASE("Soft-neon matches non-neon output") {
	constexpr int BufferSize = 255;
	float no_outsig[256];
	float ne_outsig[256];

	{
		using namespace MetaModule;

		DjembeCore no;
		int n = 0;
		no.update();

		// no.set_input(DjembeInfo::InputPitch_Cv, 0.f);
		// no.set_input(DjembeInfo::InputHit_Cv, 0.f);
		// no.set_input(DjembeInfo::InputSharp_Cv, 0.0f);
		// no.set_input(DjembeInfo::InputStrike_Cv, 0.0f);

		// no.set_param(DjembeInfo::KnobPitch, 60.f);
		// no.set_param(DjembeInfo::KnobHit, 1.f);
		// no.set_param(DjembeInfo::KnobSharpness, 0.5f);
		// no.set_param(DjembeInfo::KnobStrike_Amt, 0.3f);

		no.set_input(0, 0.f);
		no.set_input(2, 0.f);
		no.set_input(1, 0.0f);
		no.set_input(3, 0.0f);

		no.set_param(0, 60.f);
		no.set_param(2, 1.f);
		no.set_param(1, 0.5f);
		no.set_param(3, 0.3f);

		// Trigger low for 3
		for (int i = 0; i < 3; i++) {
			no.set_input(4, 0.f);
			no.update();
			no_outsig[n++] = no.get_output(0);
		}

		// Trigger high for 1
		for (int i = 0; i < 1; i++) {
			no.set_input(4, 1.f);
			no.update();
			no_outsig[n++] = no.get_output(0);
		}

		// Trigger low for the rest of the buffer
		for (int i = 0; i < (BufferSize - 1 - 3); i++) {
			no.set_input(4, 0.f);
			no.update();
			no_outsig[n++] = no.get_output(0);
		}
	}

	{
		MetaModule::DjembeCoreNeon ne;
		int n = 0;
		ne.update();

		ne.set_input(0, 0.f);
		ne.set_input(2, 0.f);
		ne.set_input(1, 0.0f);
		ne.set_input(3, 0.0f);

		ne.set_param(0, 60.f);
		ne.set_param(2, 1.f);
		ne.set_param(1, 0.5f);
		ne.set_param(3, 0.3f);

		// ne.set_input(DjembeInfo::InputPitch_Cv, 0.f);
		// ne.set_input(DjembeInfo::InputHit_Cv, 0.f);
		// ne.set_input(DjembeInfo::InputSharp_Cv, 0.0f);
		// ne.set_input(DjembeInfo::InputStrike_Cv, 0.0f);

		// ne.set_param(DjembeInfo::KnobPitch, 60.f);
		// ne.set_param(DjembeInfo::KnobHit, 1.f);
		// ne.set_param(DjembeInfo::KnobSharpness, 0.5f);
		// ne.set_param(DjembeInfo::KnobStrike_Amt, 0.3f);

		// Trigger low for 3
		for (int i = 0; i < 3; i++) {
			ne.set_input(4, 0.f);
			ne.update();
			ne_outsig[n++] = ne.get_output(0);
		}

		// Trigger high for 1
		for (int i = 0; i < 1; i++) {
			ne.set_input(4, 1.f);
			ne.update();
			ne_outsig[n++] = ne.get_output(0);
		}

		// Trigger low for the rest of the buffer
		for (int i = 0; i < (BufferSize - 1 - 3); i++) {
			ne.set_input(4, 0.f);
			ne.update();
			ne_outsig[n++] = ne.get_output(0);
		}
	}

	for (int i = 0; i < BufferSize; i++) {
		CHECK(no_outsig[i] == doctest::Approx(ne_outsig[i]));
	}
}
