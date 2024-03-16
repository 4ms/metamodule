#pragma once
#include <string>
// #include <common.hpp>
// #include <math.hpp>
// #include <random.hpp>

namespace rack
{

struct Quantity {
	virtual ~Quantity() = default;

	virtual void setValue(float value) {
	}

	virtual float getValue() {
		return 0.f;
	}

	virtual float getMinValue() {
		return 0.f;
	}

	virtual float getMaxValue() {
		return 1.f;
	}

	virtual float getDefaultValue() {
		return 0.f;
	}

	virtual float getDisplayValue() {
		return 0;
	}

	virtual void setDisplayValue(float displayValue) {
	}

	virtual int getDisplayPrecision() {
		return 0;
	}

	virtual std::string getDisplayValueString() {
		return "";
	}

	virtual void setDisplayValueString(std::string s) {
	}

	virtual std::string getLabel() {
		return "";
	}

	virtual std::string getUnit() {
		return "";
	}

	virtual std::string getString() {
		return "";
	}

	virtual void reset() {
	}

	virtual void randomize() {
	}

	bool isMin() {
		return true;
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
		return 0;
	}
	bool isBounded() {
		return false;
	}
	float toScaled(float value) {
		return 0;
	}
	float fromScaled(float scaledValue) {
		return 0;
	}
	void setScaledValue(float scaledValue) {
	}
	float getScaledValue() {
		return 0;
	}
	void moveScaledValue(float deltaScaledValue) {
	}
};

} // namespace rack
