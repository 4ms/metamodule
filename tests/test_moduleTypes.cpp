#include "CoreModules/moduleTypes.h"
#include "CppUTest/TestHarness.h"
#include <fff.h>

//#define FLOATS_NEARLY_EQUAL(e, a) DOUBLES_EQUAL(static_cast<double>(e), static_cast<double>(a), 0.00001);

TEST_GROUP(module_type_tests){

	void setup(){}

	void teardown(){}

};

TEST(module_type_tests, construct_with_short_string)
{
	CHECK(true);
}
