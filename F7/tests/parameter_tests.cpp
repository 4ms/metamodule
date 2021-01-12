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

TEST_CASE("Reference Parameter usage")
{

	float data = 0.75f;
	RefParameter<float> x{data};

	CHECK(x == data);

	SUBCASE("Changing the underlying data changes the ref param when we read it")
	{
		data = 10.0f;
		CHECK(x == 10.0f);
	}
	SUBCASE("Writing to the ref param changes the underlying data")
	{
		x = 4.2f;
		CHECK(data == 4.2f);
	}
	SUBCASE("Setting a different value causes isChanged() to be true")
	{
		SUBCASE("Writing to underlying data")
		{
			data = 1.5f;
			CHECK(x.isChanged());
			SUBCASE("And the next time isChanged() is called, it's false")
			{
				CHECK(x.isChanged() == false);
			}
		}

		SUBCASE("Writing to ref directly")
		{
			x = 2.554f;
			CHECK(x.isChanged());
			SUBCASE("And the next time isChanged() is called, it's false")
			{
				CHECK(x.isChanged() == false);
			}
		}

		SUBCASE("Using setValue()")
		{
			x.setValue(14.21f);
			CHECK(x.isChanged());
			SUBCASE("And the next time isChanged() is called, it's false")
			{
				CHECK(x.isChanged() == false);
			}
		}
	}

	SUBCASE("Writing to the underlying data with the same value causes isChanged() to be false")
	{
		SUBCASE("Writing to underlying data")
		{
			data = 1.5f;
			CHECK(x.isChanged());
			data = 1.5f;
			CHECK(x.isChanged() == false);
		}

		SUBCASE("Writing to ref directly")
		{
			x = 2.554f;
			CHECK(x.isChanged());
			x = 2.554f;
			CHECK(x.isChanged() == false);
		}

		SUBCASE("Using setValue()")
		{
			x.setValue(14.21f);
			CHECK(x.isChanged());
			x.setValue(14.21f);
			CHECK(x.isChanged() == false);
		}

		SUBCASE("isChanged() is false if we write a different value, but then write the original value before calling "
				"isChanged()")
		{
			x = 5.4f;
			CHECK(x.isChanged());
			x.setValue(99.5f);
			x.setValue(5.4f);
			CHECK(x.isChanged() == false);
		}
	}
}

