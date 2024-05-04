#include <Quantity.hpp>

namespace rack
{

float Quantity::getDisplayValue() {
	return getValue();
}

void Quantity::setDisplayValue(float displayValue) {
	setValue(displayValue);
}

int Quantity::getDisplayPrecision() {
	return 5;
}

std::string Quantity::getDisplayValueString() {
	float v = getDisplayValue();
	return std::to_string(v);
}

void Quantity::setDisplayValueString(std::string s) {
}

std::string Quantity::getString() {
	std::string s;
	std::string label = getLabel();
	std::string valueString = getDisplayValueString() + getUnit();
	s += label;
	if (label != "" && valueString != "")
		s += ": ";
	s += valueString;
	return s;
}

void Quantity::reset() {
	setValue(getDefaultValue());
}

void Quantity::randomize() {
	if (isBounded())
		setScaledValue(random::uniform());
}

bool Quantity::isMin() {
	return getValue() <= getMinValue();
}

bool Quantity::isMax() {
	return getValue() >= getMaxValue();
}

void Quantity::setMin() {
	setValue(getMinValue());
}

void Quantity::setMax() {
	setValue(getMaxValue());
}

void Quantity::toggle() {
	setValue(isMin() ? getMaxValue() : getMinValue());
}

void Quantity::moveValue(float deltaValue) {
	setValue(getValue() + deltaValue);
}

float Quantity::getRange() {
	return getMaxValue() - getMinValue();
}

bool Quantity::isBounded() {
	return std::isfinite(getMinValue()) && std::isfinite(getMaxValue());
}

float Quantity::toScaled(float value) {
	if (!isBounded())
		return value;
	else if (getMinValue() == getMaxValue())
		return 0.f;
	else
		return math::rescale(value, getMinValue(), getMaxValue(), 0.f, 1.f);
}

float Quantity::fromScaled(float scaledValue) {
	if (!isBounded())
		return scaledValue;
	else
		return math::rescale(scaledValue, 0.f, 1.f, getMinValue(), getMaxValue());
}

void Quantity::setScaledValue(float scaledValue) {
	setValue(fromScaled(scaledValue));
}

float Quantity::getScaledValue() {
	return toScaled(getValue());
}

void Quantity::moveScaledValue(float deltaScaledValue) {
	if (!isBounded())
		moveValue(deltaScaledValue);
	else
		moveValue(deltaScaledValue * getRange());
}

} // namespace rack
