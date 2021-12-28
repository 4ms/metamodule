#include "CoreModules/adCore.h"
#include "doctest.h"
#include <iostream>
#include <stdint.h>

TEST_CASE("timing test")
{
	AdCore ad;
	ad.set_samplerate(48000);
	ad.set_param(0, 0); // 1 ms attack
	ad.set_param(1, 0); // 1 ms decay
	ad.set_input(0, 0.0f);
	ad.update();
	ad.set_input(0, 1.0f); // gate high
	for (int i = 0; i < 49; i++) {
		if (i == 0) {
			CHECK(ad.get_output(1) == doctest::Approx(0)); // EOA output is low
			CHECK(ad.get_output(2) == doctest::Approx(0)); // EOD output is low
		}
		ad.update();
	}
	for (int i = 0; i < 49; i++) {
		if (i == 0) {
			CHECK(ad.get_output(1) == doctest::Approx(1)); // EOA output is high
			CHECK(ad.get_output(2) == doctest::Approx(0)); // EOD output is low
		}
		ad.update();
	}
	for (int i = 0; i < 49; i++) {
		ad.update();
	}
	CHECK(ad.get_output(1) == doctest::Approx(1)); // EOA output is high
	CHECK(ad.get_output(2) == doctest::Approx(1)); // EOD output is high
}