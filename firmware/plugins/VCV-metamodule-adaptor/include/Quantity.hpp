#pragma once
#include <common.hpp>
#include <math.hpp>
#include <random.hpp>

namespace rack
{

struct Quantity {
	virtual ~Quantity() {
	}

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

	virtual float getDisplayValue();

	virtual void setDisplayValue(float displayValue);

	virtual int getDisplayPrecision();

	virtual std::string getDisplayValueString();

	virtual void setDisplayValueString(std::string s);

	virtual std::string getLabel() {
		return "";
	}

	virtual std::string getUnit() {
		return "";
	}

	virtual std::string getString();

	virtual void reset();

	virtual void randomize();

	// Helper methods

	bool isMin();
	bool isMax();
	void setMin();
	void setMax();
	void toggle();
	void moveValue(float deltaValue);

	float getRange();
	bool isBounded();
	float toScaled(float value);
	float fromScaled(float scaledValue);
	void setScaledValue(float scaledValue);
	float getScaledValue();
	void moveScaledValue(float deltaScaledValue);
};

} // namespace rack
