#pragma once

#include "util/math.hh"
#include <vector>

class MultiMap {
public:
	std::vector<float> update(float value)
	{
		lastValue = currentValue;
		currentValue = value;
		if (currentValue != lastValue) {
			std::vector<float> fromVec;
			std::vector<float> toVec;
			int size = settings.size();
			float index = value * (size - 1);
			int intIndex = index;
			fromVec = settings[intIndex];
			if (index < (size - 1)) {
				toVec = settings[intIndex + 1];
			} else {
				toVec = settings[intIndex];
			}

			float frac = index - intIndex;

			tempVec.clear();

			for (int i = 0; i < setSize; i++) {
				tempVec.push_back(MathTools::interpolate(fromVec.at(i), toVec.at(i), frac));
			}
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
	std::vector<float> tempVec;
	float currentValue = 1;
	float lastValue = 2;
};