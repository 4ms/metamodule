#pragma once
#include "util/math.hh"
using namespace MathTools;

class CubicNonlinearDist {
public:
	float update(float input)
	{
		float output = 0;
		float fTemp0 = constrain(input, -1.0f, 1.0f);
		output = fTemp0 * (1.0f - (0.333333343f * fTemp0 * fTemp0));
		return output;
	}
};
