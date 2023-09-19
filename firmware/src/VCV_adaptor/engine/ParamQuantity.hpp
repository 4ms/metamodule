#pragma once
#include "VCV_adaptor/json.hpp"
#include <string>
#include <string_view>

namespace rack::engine
{

struct Module;
struct Param;

struct ParamQuantity {
	virtual ~ParamQuantity() = default;
	Module *module = nullptr;
	int paramId = -1;

	float minValue = 0.f;
	float maxValue = 1.f;
	float defaultValue = 0.f;

	std::string_view name = "";
	std::string_view unit = "";
	float displayBase = 0.f;
	float displayMultiplier = 1.f;
	float displayOffset = 0.f;
	int displayPrecision = 5;
	std::string_view description = "";
	bool resetEnabled = true;
	bool randomizeEnabled = true;
	bool smoothEnabled = false;
	bool snapEnabled = false;

	void setValue(float value) {
	}
	float getValue() {
		return {};
	}
	float getMinValue() {
		return minValue;
	}
	float getMaxValue() {
		return maxValue;
	}
	float getDefaultValue() {
		return {};
	}
	virtual float getDisplayValue() {
		return {};
	}
	virtual void setDisplayValue(float displayValue) {
	}
	void setImmediateValue(float displayValue);
	float getImmediateValue() {
		return {};
	}
	int getDisplayPrecision() {
		return {};
	}
	virtual std::string getDisplayValueString() {
		return {};
	}
	virtual void setDisplayValueString(std::string s) {
	}
	std::string_view getLabel() {
		return {};
	}
	std::string_view getUnit() {
		return {};
	}
	std::string_view getString() {
		return {};
	}
	void reset() {
	}
	void randomize() {
	}
	bool isMin() {
		return false;
	}
	bool isMax() {
		return false;
	}
	void setMin() {
	}
	void setMax() {
	}
	void toggle() {
	}
	void moveValue(float deltaValue) {
	}

	float getRange() {
		return {};
	}
	bool isBounded() {
		return {};
	}
	float toScaled(float value) {
		return {};
	}
	float fromScaled(float scaledValue) {
		return {};
	}
	void setScaledValue(float scaledValue) {
	}
	float getScaledValue() {
		return {};
	}
	void moveScaledValue(float deltaScaledValue) {
	}
	Param *getParam() {
		return {};
	}
	void setSmoothValue(float value) {
	}
	float getSmoothValue() {
		return {};
	}

	std::string_view getDescription() {
		return {};
	}
	json_t *toJson() {
		return {};
	}
	void fromJson(json_t *rootJ) {
	}
};

struct SwitchQuantity : ParamQuantity {};

} // namespace rack::engine
