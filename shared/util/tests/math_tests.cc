#include "../math.hh"

TEST_CASE("Testing randomNumber()")
{
	SUBCASE("results are in range")
	{
		int reps = 100;
		while (reps--) {
			auto x = MathTools::randomNumber(-4.f, 4.f);
			CHECK(x >= -4.f);
			CHECK(x <= 4.f);
		}
	}
	SUBCASE("if minNum==maxNum, result will always be minNum")
	{
		int reps = 100;
		while (reps--) {
			auto x = MathTools::randomNumber(222.f, 222.f);
			CHECK(x == 222.f);
		}
	}
	SUBCASE("results are always < maxNum (unless minNum==maxNum)")
	{
		SUBCASE("...with floats")
		{
			int reps = 100;
			int num_high_x = 0;
			while (reps--) {
				double low = 1.0, high = 2.0;
				auto x = MathTools::randomNumber(low, high);
				if (x == doctest::Approx(high).epsilon(0.00001))
					num_high_x++;
			}
			CHECK(num_high_x == 0);
		}

		SUBCASE("...with integers")
		{
			int reps = 100;
			int num_high_x = 0;
			while (reps--) {
				auto x = MathTools::randomNumber(1UL, 2UL);
				if (x == 2UL)
					num_high_x++;
			}
			CHECK(num_high_x == 0);
		}
	}
}
