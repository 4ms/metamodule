#pragma once

#include "gcem/include/gcem.hpp"
#include "helpers/mapping.h"
#include <algorithm>
#include <cmath>

class SSI2162 {
public:
	SSI2162()
		: scalingFactor(1.f) {
	}

	void setScaling(float gainInV) {
		scalingFactor = GainTable.lookup(gainInV);
	}

	float process(float input) const {
		return input * scalingFactor;
	}

private:
	float scalingFactor;

	static constexpr auto GainTable = Mapping::LookupTable_t<0.f, 5.4f, 64>::generate([](auto voltage) {
		auto gainIndB = voltage / -33e-3f;
		return gcem::pow(10.f, gainIndB / 20.f);
	});
};
