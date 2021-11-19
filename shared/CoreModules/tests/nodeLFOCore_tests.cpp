#include "CoreModules/lfoCore.h"
#include "doctest.h"
#include <stdint.h>

TEST_CASE("Basic LFO usage") {
	SUBCASE("Using get/set") {
		NodeLFOCore lfo;

		SUBCASE("Output starts at 0") {
			CHECK(lfo.get_output(0) == doctest::Approx(0.0f));

			SUBCASE("Output rises when updated") {
				lfo.set_input(0, 0.5);
				lfo.update();
				lfo.update();
				CHECK(lfo.get_output(0) > doctest::Approx(0.0f));

				SUBCASE("Reset going high resets phase after next update()") {
					lfo.set_input(1, 1.0f);
					lfo.update();
					CHECK(lfo.get_output(0) == 0.0f);
					SUBCASE("and LFO keeps running when reset stays high") {
						lfo.update();
						auto lastout = lfo.get_output(0);
						lfo.update();
						CHECK(lfo.get_output(0) > lastout);

						SUBCASE("Reset going low does nothing") {
							NodeLFOCore lfo1;
							lfo1.set_input(0, 0.5f);
							lfo1.update();
							lfo1.update();
							// Do a reset
							lfo1.set_input(1, 1.0f);
							lfo1.update();
							CHECK(lfo1.get_output(0) == 0.0f);

							lfo1.update(); //#1
							// lower the reset
							lfo1.set_input(1, 0.0f);
							lfo1.update(); //#2
							lfo1.update(); //#3

							NodeLFOCore lfo2;
							lfo2.set_input(0, 0.5);
							lfo2.update(); //#1
							lfo2.update(); //#2
							lfo2.update(); //#3

							CHECK(lfo1.get_output(0) == lfo2.get_output(0));
						}
					}
				}
			}
		}
	}

	// SUBCASE("Using Nodes")
	// {

	// 	SUBCASE("Can read output directly from node, and it's the same as using get_output()")
	// 	{
	// 		NodeLFOCore lfo2;
	// 		lfo2.set_input(0, 0.5); // freq
	// 		lfo2.set_input(1, 0.0); // reset

	// 		float freq = 0.0f, reset = 0.f, out = 0.f;
	// 		NodeLFOCore lfo{freq, reset, out};
	// 		lfo.set_input(0, 0.5);

	// 		lfo.update();
	// 		lfo2.update();
	// 		lfo.update();
	// 		lfo2.update();

	// 		CHECK(out == lfo.get_output(0));
	// 		CHECK(out == lfo2.get_output(0));
	// 	}

	// 	SUBCASE("Directly setting input node is same as using set_input()")
	// 	{
	// 		float freq = 0.0f, reset = 0.f, out = 0.f;
	// 		NodeLFOCore lfo{freq, reset, out};

	// 		freq = 0.5;

	// 		NodeLFOCore lfo2;
	// 		lfo2.set_input(0, 0.5);

	// 		for (int i = 0; i < 30; i++) {
	// 			lfo2.update();
	// 			lfo.update();
	// 		}

	// 		CHECK(out == lfo.get_output(0));
	// 		CHECK(out == lfo2.get_output(0));
	// 	}

	// 	SUBCASE("Initializing a node to a non-zero value acts the same as initializing to 0 and then setting it to "
	// 			"non-zero")
	// 	{
	// 		float non_zero_value = 0.3f;

	// 		float freq = non_zero_value, reset = non_zero_value, out = non_zero_value;
	// 		NodeLFOCore lfo{freq, reset, out};
	// 		freq = non_zero_value;

	// 		float freq2 = 0.f, reset2 = 0.f, out2 = 0.f;
	// 		NodeLFOCore lfo2{freq2, reset2, out2};
	// 		freq2 = non_zero_value;

	// 		for (int i = 0; i < 30; i++) {
	// 			lfo2.update();
	// 			lfo.update();
	// 		}

	// 		CHECK(out == out2);
	// 	}
	// }
}
