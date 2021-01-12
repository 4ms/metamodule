#include "doctest.h"
#include "processors/tools/parameter.h"
#include <stdint.h>

TEST_CASE("Basic usage")
{
	Parameter<int> x;

	SUBCASE("initial value is 0")
	{
		CHECK(x.getValue() == 0);
	}
	SUBCASE("initial changed status is true")
	{
		CHECK(x.isChanged());

		SUBCASE("calling isChanged() a second time returns false")
		{
			CHECK(x.isChanged() == false);

			SUBCASE("setting a new value makes isChanged() return true (just once)")
			{
				x.setValue(1);
				CHECK(x.isChanged());
				CHECK(x.isChanged() == false);
			}

			SUBCASE("setting it to the same value it already is, doesn't make isChanged return true")
			{
				x.setValue(x.getValue());
				CHECK(x.isChanged() == false);
			}

			SUBCASE("setting it to a new value, and then the same value a few times in a row, still reports as changed")
			{
				x.setValue(100.f);
				x.setValue(200.f);
				x.setValue(200.f);
				CHECK(x.isChanged());
			}
		}
	}
}

TEST_CASE("Short-hand usage")
{
	SUBCASE("Parameter<int>")
	{
		Parameter<int> x;

		x = 987654321;
		CHECK((int)x == 987654321);
	}

	SUBCASE("Parameter<float>")
	{
		Parameter<float> f;

		f = 12345.0f;
		CHECK((int)f == 12345.0f);
	}
}

