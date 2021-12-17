#include "CoreModules/logicCore.h"
#include "doctest.h"
#include <stdint.h>

TEST_CASE("initial test returns 0")
{
	LogicCore log;
	CHECK(log.get_output(0) == 0.0f);
}