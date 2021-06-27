#include "CoreModules/djembeCore.h"
#include "CoreModules/djembeCore_neon.h"
#include "doctest.h"
#include <iostream>
#include <stdint.h>

TEST_CASE("first test")
{
	DjembeCore no;
	constexpr int BufferSize = 256;
	float no_outsig[BufferSize];

	int n = 0;

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

	DjembeCoreN ne;
	float ne_outsig[BufferSize];

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

	for (int i = 0; i < BufferSize; i++) {
		std::cout << no_outsig[i] << ", ";
		// CHECK(no_outsig[i] == doctest::Approx(ne_outsig[i]));
	}
	std::cout << std::endl;
	for (int i = 0; i < BufferSize; i++) {
		std::cout << ne_outsig[i] << ", ";
	}
}
