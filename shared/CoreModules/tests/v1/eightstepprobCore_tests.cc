#include "CoreModules/eightstepprobCore.h"
#include "doctest.h"
#include <stdint.h>

TEST_CASE("100% probability always produces a gate")
{
	int output = 0;
	EightstepprobCore p;
	int numTests = 60000;
	for (int i = 0; i < 8; i++) {
		p.set_param(i, 1.0f);
	}
	for (int i = 0; i < numTests; i++) {
		p.set_input(0, 1.0f);
		p.update();
		output += (int)p.get_output(0);
		p.set_input(0, 0.0f);
		p.update();
	}
	CHECK(output == numTests);
}

TEST_CASE("Check lower probabilities don't always trigger")
{
	EightstepprobCore p;
	long numTests = 100;
	for (int n = 0; n < 10; n++) {
		int output = 0;
		int testPercent = rand() % 80;
		for (int i = 0; i < 8; i++) {
			p.set_param(i, (float)testPercent / 100.0f);
		}
		for (int i = 0; i < numTests; i++) {
			p.set_input(0, 1.0f);
			p.update();
			output += (int)p.get_output(0);
			p.set_input(0, 0.0f);
			p.update();
		}
		CHECK(output < numTests);
	}
}