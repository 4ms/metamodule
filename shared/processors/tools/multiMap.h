#pragma once

#include <vector>
#include "util/math.hh"

class MultiMap
{
public:
	std::vector<float> update(float value)
	{
		std::vector<float> fromVec;
		std::vector<float> toVec;
		std::vector<float> tempVec;
		int size = settings.size();
		float index = value * (size - 1);
		int intIndex = index;
		fromVec = settings[intIndex];
		if (index < (size - 1))
		{
			toVec = settings[intIndex + 1];
		}
		else
		{
			toVec = settings[intIndex];
		}

		float frac = index - intIndex;

		for (int i = 0; i < setSize; i++)
		{
			tempVec.push_back(MathTools::interpolate(fromVec.at(i), toVec.at(i), frac));
		}


		return tempVec;
	}

	void addPreset(std::vector<float> set)
	{
		settings.push_back(set);
		setSize = set.size();
	}
private:
	std::vector<std::vector<float>> settings;
	int setSize;
};