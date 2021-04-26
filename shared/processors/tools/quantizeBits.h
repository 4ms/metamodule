#pragma once

#include "util/math.hh"
#include <vector>

class BitQuantizer {
public:
	float update(float input)
	{
		interval = (valueMax - valueMin) / static_cast<float>(numSteps - 1);
		float position = input - valueMin;
		int index;
		if (((position / interval) - (long)(position / interval)) <= 0.5f) {
			index = floorf(position / interval);
		} else {
			index = ceilf(position / interval);
		}

		return (index * interval + valueMin);
	}

	void setSteps(int val)
	{
		numSteps = val;
	}

	void setMin(float val)
	{
		valueMin = val;
	}

	void setMax(float val)
	{
		valueMax = val;
	}

private:
	float valueMin = -1;
	float valueMax = 1;
	int numSteps = 1;
	float interval = 1;
};