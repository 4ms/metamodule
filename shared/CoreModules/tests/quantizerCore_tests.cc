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
	SUBCASE("Scale change is effective before running update")
	{
		QuantizerCore q;

		q.set_input(0, 0);

		q.set_param(0, 1.0f);

		q.update();

		CHECK(q.get_output(0) == 0);

		q.set_param(0, 0.0f);
		q.set_param(1, 1.0f);

		q.update();

		CHECK(q.get_output(0) == doctest::Approx(1.0f / 60.0f));
	}

	SUBCASE("Rounds to nearest value")
	{
		float out;

		// All off except C E A
		q.set_param(0, 1.f); // C = 0
		q.set_param(1, 0.f);
		q.set_param(2, 0.f);
		q.set_param(3, 0.f);
		q.set_param(4, 1.f); // E = 0.33
		q.set_param(5, 0.f);
		q.set_param(6, 0.f);
		q.set_param(7, 0.f);
		q.set_param(8, 0.f);
		q.set_param(9, 1.f); // A = 0.75
		q.set_param(10, 0.f);
		q.set_param(11, 0.f);

		SUBCASE("Round down to C")
		{
			q.set_input(0, 0.14f / InputHighRangeVolts);
			q.update();
			out = q.get_output(0) * InputHighRangeVolts;
			CHECK(out == doctest::Approx(0.0f));
		}

		SUBCASE("Round up to E")
		{
			q.set_input(0, 0.17f / InputHighRangeVolts);
			q.update();
			out = q.get_output(0) * InputHighRangeVolts;
			CHECK(out == doctest::Approx(0.3333333f));
		}

		SUBCASE("Round down to E")
		{
			q.set_input(0, 0.34f / InputHighRangeVolts);
			q.update();
			out = q.get_output(0) * InputHighRangeVolts;
			CHECK(out == doctest::Approx(0.3333333f));
		}

		SUBCASE("Round up to A")
		{
			q.set_input(0, 0.60f / InputHighRangeVolts);
			q.update();
			out = q.get_output(0) * InputHighRangeVolts;
			CHECK(out == doctest::Approx(0.75f));
		}

		SUBCASE("Round down to A")
		{
			q.set_input(0, 0.77f / InputHighRangeVolts);
			q.update();
			out = q.get_output(0) * InputHighRangeVolts;
			CHECK(out == doctest::Approx(0.75f));
		}

		SUBCASE("Round down to A")
		{
			q.set_input(0, 0.77f / InputHighRangeVolts);
			q.update();
			out = q.get_output(0) * InputHighRangeVolts;
			CHECK(out == doctest::Approx(0.75f));
		}

		SUBCASE("Round up to C1")
		{
			q.set_input(0, 0.90f / InputHighRangeVolts);
			q.update();
			out = q.get_output(0) * InputHighRangeVolts;
			CHECK(out == doctest::Approx(1.00f));
		}

		SUBCASE("Round down to C1")
		{
			q.set_input(0, 1.09f / InputHighRangeVolts);
			q.update();
			out = q.get_output(0) * InputHighRangeVolts;
			CHECK(out == doctest::Approx(1.00f));
		}

		SUBCASE("Round up to E1")
		{
			q.set_input(0, 1.17f / InputHighRangeVolts);
			q.update();
			out = q.get_output(0) * InputHighRangeVolts;
			CHECK(out == doctest::Approx(1.33333333f));
		}
	}
}
