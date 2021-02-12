#include "CoreModules/minmaxCore.h"
#include "doctest.h"
#include <stdint.h>

TEST_CASE("min test")
{
	MinmaxCore m;

	m.set_input(0, 0.1f);
	m.set_input(1, 0.3f);
	m.update();
	CHECK(m.get_output(0) == 0.1f);
}

TEST_CASE("max test")
{
	MinmaxCore m;

	m.set_input(0, 0.1f);
	m.set_input(1, 0.3f);
	m.update();
	CHECK(m.get_output(1) == 0.3f);
}
