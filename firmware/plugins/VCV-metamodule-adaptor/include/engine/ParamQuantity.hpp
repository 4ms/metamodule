#pragma once
#include <vector>

#include <jansson.h>

#include <Quantity.hpp>
#include <engine/Param.hpp>

namespace rack::engine
{

struct Module;

struct ParamQuantity : Quantity {
	Module *module = nullptr;
	int paramId = -1;

	float minValue = 0.f;
	float maxValue = 1.f;
	float defaultValue = 0.f;

	std::string name;
	std::string unit;
	float displayBase = 0.f;
	float displayMultiplier = 1.f;
	float displayOffset = 0.f;
	int displayPrecision = 5;
	std::string description;

	bool resetEnabled = true;
	bool randomizeEnabled = true;
	bool smoothEnabled = false;
	bool snapEnabled = false;

	Param *getParam();

	void setImmediateValue(float value);
	float getImmediateValue();

	virtual std::string getDescription() {
		return description;
	}

	virtual json_t *toJson() {
		return nullptr;
	}
	virtual void fromJson(json_t *rootJ) {
	}

	//MM:
	std::vector<std::string> labels;
};

struct SwitchQuantity : ParamQuantity {};

} // namespace rack::engine
