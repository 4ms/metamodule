#include "CoreModules/quantizerCore.h"
#include "doctest.h"
#include <stdint.h>

TEST_CASE("Quantizer parameter bounds")
{
	QuantizerCore q;
	SUBCASE("invalid param_id don't crash")
	{
		q.set_param(-99999999, 0.0f);
		q.set_param(99999999, 0.0f);
		q.set_input(999, 0.0f);
		q.get_output(999);
	}
}

TEST_CASE("Basic Quantizer functionality")
{
	QuantizerCore q;

	SUBCASE("all notes off, output = input")
	{
		for (int i = 0; i < 12; i++)
			q.set_param(i, 0.0f);

		for (float x = 0.f; x < 10.f; x += 0.05) {
			q.set_input(0, x);
			q.update();
			float out = q.get_output(0);
			CHECK(out == x);
		}
	}
	SUBCASE("With just one note on, all outputs should be fixed intervals from each other")
	{
		// Todo
	}
	// Todo more tests
}

