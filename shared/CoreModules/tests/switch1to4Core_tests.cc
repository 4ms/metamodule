#include "CoreModules/switch1to4Core.h"
#include "doctest.h"
#include <stdint.h>

TEST_CASE("clock test")
{
	Switch1to4Core s;
	s.set_input(2, 0.73f); // set signal input
	s.update();
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			CHECK(s.get_output(i) == 0.73f);
		} else {
			CHECK(s.get_output(i) == 0);
		}
	}
	s.set_input(0, 1.0f); // clock high
	s.set_input(0, 0.0f); // clock low
	s.update();
	for (int i = 0; i < 3; i++) {
		if (i == 1) {
			CHECK(s.get_output(i) == 0.73f);
		} else {
			CHECK(s.get_output(i) == 0);
		}
	}
	s.set_input(0, 1.0f); // clock high
	s.set_input(0, 0.0f); // clock low
	s.update();
	for (int i = 0; i < 3; i++) {
		if (i == 2) {
			CHECK(s.get_output(i) == 0.73f);
		} else {
			CHECK(s.get_output(i) == 0);
		}
	}
	s.set_input(0, 1.0f); // clock high
	s.set_input(0, 0.0f); // clock low
	s.update();
	for (int i = 0; i < 3; i++) {
		if (i == 3) {
			CHECK(s.get_output(i) == 0.73f);
		} else {
			CHECK(s.get_output(i) == 0);
		}
	}
	s.set_input(0, 1.0f); // clock high
	s.set_input(0, 0.0f); // clock low
	s.update();
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			CHECK(s.get_output(i) == 0.73f);
		} else {
			CHECK(s.get_output(i) == 0);
		}
	}
}
