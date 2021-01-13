#include "CoreModules/quantizerCore.h"
#include "doctest.h"
#include <iostream>
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
		QuantizerCore q;

		q.set_input(0, 0);

		for (int i = 0; i < 12; i++) {
			q.set_param(i, 0.0f);
		}

		q.update();

		q.set_param(1, 1.0f);

		q.update();

		float outputs[5];

		for (int i = 0; i < 5; i++) {
			q.set_input(0, (i) / 5.0f);
			q.update();
			outputs[i] = q.get_output(0);
		}

		float checks[4];
		for (int i = 0; i < 4; i++) {
			checks[i] = outputs[i + 1] - outputs[i];
			CHECK(checks[i] == doctest::Approx(0.2f));
		}
	}
	// Todo more tests
}
