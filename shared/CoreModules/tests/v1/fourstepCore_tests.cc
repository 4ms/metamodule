#include "CoreModules/fourstepCore.h"
#include "doctest.h"
#include <stdint.h>

TEST_CASE("basic step testing")
{
	FourstepCore s;
	s.set_param(0, 0.1f);
	s.set_param(1, 0.2f);
	s.set_param(2, 0.3f);
	s.set_param(3, 0.4f);

	s.update();
	CHECK(s.get_output(0) == 0.1f);
	s.set_input(0, 1.0f);
	s.update();
	s.set_input(0, 0.0f);
	s.update();
	CHECK(s.get_output(0) == 0.2f);
	s.set_input(0, 1.0f);
	s.update();
	s.set_input(0, 0.0f);
	s.update();
	CHECK(s.get_output(0) == 0.3f);
	s.set_input(0, 1.0f);
	s.update();
	s.set_input(0, 0.0f);
	s.update();
	CHECK(s.get_output(0) == 0.4f);
}