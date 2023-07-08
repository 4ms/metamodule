#pragma once

struct ParamQuantity {
	float maxValue;
	float minValue;
	float getValue() {
		return 0;
	}
	void setValue(float) {
	}

	float defaultValue = 0.f;
	// std::string name;
	// std::string unit;
	float displayBase = 0.f;
	float displayMultiplier = 1.f;
	float displayOffset = 0.f;
	int displayPrecision = 5;
	// std::string description;

	bool resetEnabled = true;
	bool randomizeEnabled = true;
	bool smoothEnabled = false;
	bool snapEnabled = false;
};
