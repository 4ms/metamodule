#include "CoreModules/djembeCore.h"
#include "CoreModules/djembeCore_neon.h"
#include "doctest.h"
#include <iostream>
#include <stdint.h>

TEST_CASE("first test")
{
	constexpr int BufferSize = 256;
	float no_outsig[BufferSize];
	float ne_outsig[BufferSize];
	{
		DjembeCore no;
		std::cout << "Initial no.noise[0]: " << no.noise[0] << std::endl;
		std::cout << "Initial no.noise[1]: " << no.noise[1] << std::endl;
		no.update();

		no.set_input(DjembeCore::Params::Freq, 0.f);
		no.set_input(DjembeCore::Params::Gain, 0.f);
		no.set_input(DjembeCore::Params::Sharpness, 0.0f);
		no.set_input(DjembeCore::Params::Strike, 0.0f);

		no.set_param(DjembeCore::Params::Freq, 60.f);
		no.set_param(DjembeCore::Params::Gain, 1.f);
		no.set_param(DjembeCore::Params::Sharpness, 0.5f);
		no.set_param(DjembeCore::Params::Strike, 0.3f);

		int n = 0;

		// Trigger low for 3
		no.set_input(DjembeCore::Params::Trigger, 0.f);
		no.update();
		no_outsig[n++] = no.get_output(0);
		std::cout << n << ": no.noise[0]: " << no.noise[0] << std::endl;
		std::cout << n << ": no.noise[1]: " << no.noise[1] << std::endl;

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
		int n = 0;
		DjembeCoreN ne;
		std::cout << "Initial ne.noise[0]: " << ne.noise[0] << std::endl;
		std::cout << "Initial ne.noise[1]: " << ne.noise[1] << std::endl;
		ne.set_input(DjembeCore::Params::Freq, 0.f);
		ne.set_input(DjembeCore::Params::Gain, 0.f);
		ne.set_input(DjembeCore::Params::Sharpness, 0.0f);
		ne.set_input(DjembeCore::Params::Strike, 0.0f);

		ne.set_param(DjembeCore::Params::Freq, 60.f);
		ne.set_param(DjembeCore::Params::Gain, 1.f);
		ne.set_param(DjembeCore::Params::Sharpness, 0.5f);
		ne.set_param(DjembeCore::Params::Strike, 0.3f);

		// Trigger low for 3
		ne.set_input(DjembeCore::Params::Trigger, 0.f);
		ne.update();
		ne_outsig[n++] = ne.get_output(0);

		std::cout << n << ": ne.noise[0]: " << ne.noise[0] << std::endl;
		std::cout << n << ": ne.noise[1]: " << ne.noise[1] << std::endl;

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

		for (int i = 0; i < BufferSize; i++) {
			// std::cout << no_outsig[i] << ", ";
			// CHECK(no_outsig[i] == doctest::Approx(ne_outsig[i]));
		}
		std::cout << std::endl;
		for (int i = 0; i < BufferSize; i++) {
			// std::cout << ne_outsig[i] << ", ";
		}
	}
}
