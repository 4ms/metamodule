#include "CoreModules/switch4to1Core.h"
#include "doctest.h"
#include <stdint.h>

TEST_CASE("clock test")
{
	Switch4to1Core s;
	s.set_input(2, 0.1f);
	s.set_input(3, 0.2f);
	s.set_input(4, 0.3f);
	s.set_input(5, 0.4f);
	s.update();
	CHECK(s.get_output(0) == 0.1f);
	s.set_input(0, 1.0f); // clock high
	s.set_input(0, 0.0f); // clock low
	s.update();
	CHECK(s.get_output(0) == 0.2f);
	s.set_input(0, 1.0f); // clock high
	s.set_input(0, 0.0f); // clock low
	s.update();
	CHECK(s.get_output(0) == 0.3f);
	s.set_input(0, 1.0f); // clock high
	s.set_input(0, 0.0f); // clock low
	s.update();
	CHECK(s.get_output(0) == 0.4f);
	s.set_input(0, 1.0f); // clock high
	s.set_input(0, 0.0f); // clock low
	s.update();
	CHECK(s.get_output(0) == 0.1f);
}