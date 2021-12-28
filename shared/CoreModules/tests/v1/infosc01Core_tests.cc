#include "CoreModules/infosc01Core.h"
#include "doctest.h"
#include <iostream>
#include <stdint.h>

TEST_CASE("Check params are set") {
	Infosc01Core inf;

	SUBCASE("Phase Knob 0..1 is stored as Q27 (0..1<<27)") {
		inf.set_param(Infosc01Core::PhaseKnob, 0.0);
		CHECK(inf.param_phase.val == 0x00000000);

		inf.set_param(Infosc01Core::PhaseKnob, 0.5);
		CHECK(inf.param_phase.val == 0x40000000); //1<<26 = 0.5 in Q27

		inf.set_param(Infosc01Core::PhaseKnob, 1.0);
		CHECK((inf.param_phase.val == 0x80000000 || inf.param_phase.val == 0x7FFFFFFF)); //1<<27 = 1.0 in Q27
	}

	SUBCASE("Phase knob is unsigned, clamps at 0") {
		inf.set_param(Infosc01Core::PhaseKnob, -0.5);
		CHECK(inf.param_phase.val == 0x00000000);

		inf.set_param(Infosc01Core::PhaseKnob, -1.0);
		CHECK(inf.param_phase.val == 0x00000000);
	}

	SUBCASE("Pitch Knob 0..1 is stored as Q27 (-1<<27..1<<27)") {
		inf.set_param(Infosc01Core::PitchKnob, 0.0);
		CHECK(inf.param_pitch.val == -(0x08000000UL)); //-1(1<<27) = -1.0 in Q27
		CHECK(inf.param_pitch.val == (int32_t)(0xF8000000L));

		inf.set_param(Infosc01Core::PitchKnob, 0.25);
		CHECK(inf.param_pitch.val == -(0x04000000UL)); //-(1<<26) = -0.5 in Q27
		CHECK(inf.param_pitch.val == (int32_t)(0xFC000000L));

		inf.set_param(Infosc01Core::PitchKnob, 0.5);
		CHECK(inf.param_pitch.val == 0x00000000);

		inf.set_param(Infosc01Core::PitchKnob, 0.75);
		CHECK(inf.param_pitch.val == 0x04000000); //1<<26 = 0.5 in Q27

		inf.set_param(Infosc01Core::PitchKnob, 1.0);
		CHECK(inf.param_pitch.val == 0x08000000); //1<<27 = 1.0 in Q27
	}

	CHECK(inf.inlet_phase.val == 0);
}

TEST_CASE("update_params") {
	Infosc01Core inf;

	//TODO:

	// inf.set_param(Infosc01Core::PhaseKnob, 0.0);
	// inf.set_param(Infosc01Core::PitchKnob, 0.3);
	// inf.set_param(Infosc01Core::RangeKnob, 0.2);
	// for (int i = 0; i < 80; i++)
	// 	inf.update_params();
	// inf.update();
	// inf.update();
	// inf.update();
	// inf.update();
}
