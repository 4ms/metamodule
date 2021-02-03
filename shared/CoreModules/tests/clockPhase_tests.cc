#include "doctest.h"
#include "processors/tools/clockPhase.h"
#include <iostream>
#include <stdint.h>

TEST_CASE("basic count test")
{
	ClockPhase cp;
	for (int i = 0; i < 4; i++) {
		cp.updateClock(0.0f);
		cp.update();
		cp.updateClock(1.0f);
		cp.update();
	}
	CHECK(cp.getCount() == 4);
}

TEST_CASE("divide count test")
{
	ClockPhase cp;
	cp.setDivide(2);
	for (int i = 0; i < 4; i++) {
		cp.updateClock(0.0f);
		cp.update();
		cp.updateClock(1.0f);
		cp.update();
	}
	CHECK((int)cp.getPhase() == 2);
}

TEST_CASE("multiply count test")
{
	ClockPhase cp;
	cp.setMultiply(2);
	for (int i = 0; i < 4; i++) {
		cp.updateClock(0.0f);
		cp.update();
		cp.updateClock(1.0f);
		cp.update();
	}
	CHECK(cp.getPhase() == 8);
}