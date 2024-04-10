#include <engine/Module.hpp>
#include <engine/ParamQuantity.hpp>

namespace rack::engine
{

void ParamQuantity::setImmediateValue(float value) {
	if (!module)
		return;
	if ((unsigned)paramId >= module->params.size())
		return;

	module->params[paramId].setValue(value);
}

float ParamQuantity::getImmediateValue() {
	if (!module)
		return 0.f;
	if ((unsigned)paramId >= module->params.size())
		return 0.f;

	return module->params[paramId].getValue();
}

Param *ParamQuantity::getParam() {
	if (!module)
		return nullptr;
	if (!(0 <= paramId && paramId < (int)module->params.size()))
		return nullptr;
	return &module->params[paramId];
}

void ParamQuantity::setValue(float value) {
	if (!module)
		return;
	value = math::clampSafe(value, getMinValue(), getMaxValue());

	if (snapEnabled)
		value = std::round(value);

	//TODO handle smoothEnabled?
	module->params[paramId].setValue(value);
}

float ParamQuantity::getValue() {
	if (auto param = getParam())
		return param->getValue();
	else
		return 0.f;
}

float ParamQuantity::getMinValue() {
	return minValue;
}

float ParamQuantity::getMaxValue() {
	return maxValue;
}

float ParamQuantity::getDefaultValue() {
	return defaultValue;
}

float ParamQuantity::getDisplayValue() {
	float v = getValue();
	if (displayBase == 0.f) {
		// Linear
		// v is unchanged
	} else if (displayBase < 0.f) {
		// Logarithmic
		v = std::log(v) / std::log(-displayBase);
	} else {
		// Exponential
		v = std::pow(displayBase, v);
	}
	return v * displayMultiplier + displayOffset;
}

void ParamQuantity::setDisplayValue(float displayValue) {
	// Handle displayOffset
	float v = displayValue - displayOffset;

	// Handle displayMultiplier
	if (displayMultiplier == 0.f)
		v = 0.f;
	else
		v /= displayMultiplier;

	// Handle displayBase
	if (displayBase == 0.f) {
		// Linear
		// v is unchanged
	} else if (displayBase < 0.f) {
		// Logarithmic
		v = std::pow(-displayBase, v);
	} else {
		// Exponential
		v = std::log(v) / std::log(displayBase);
	}

	if (std::isnan(v))
		return;

	// Set the value directly without smoothing
	setImmediateValue(v);
}

int ParamQuantity::getDisplayPrecision() {
	return displayPrecision;
}

std::string ParamQuantity::getDisplayValueString() {
	return Quantity::getDisplayValueString();
}

void ParamQuantity::setDisplayValueString(std::string s) {
	Quantity::setDisplayValueString(s);
}

std::string ParamQuantity::getLabel() {
	if (name == "")
		return "#" + std::to_string(paramId + 1);
	return name;
}

std::string ParamQuantity::getUnit() {
	return unit;
}

void ParamQuantity::reset() {
	setImmediateValue(getDefaultValue());
}

void ParamQuantity::randomize() {
	if (!isBounded())
		return;

	if (snapEnabled) {
		// Randomize inclusive of the maximum value
		float value = math::rescale(random::uniform(), 0.f, 1.f, getMinValue(), getMaxValue() + 1.f);
		value = std::floor(value);
		setImmediateValue(value);
	} else {
		// Same as Quantity::randomize() but with setImmediateValue()
		setImmediateValue(fromScaled(random::uniform()));
	}
}

std::string ParamQuantity::getDescription() {
	return description;
}

json_t *ParamQuantity::toJson() {
	json_t *rootJ = json_object();
	json_object_set_new(rootJ, "value", json_real(getValue()));
	return rootJ;
}

void ParamQuantity::fromJson(json_t *rootJ) {
	json_t *valueJ = json_object_get(rootJ, "value");
	if (valueJ)
		setImmediateValue(json_number_value(valueJ));
}

// SwitchQuantity

std::string SwitchQuantity::getDisplayValueString() {
	int index = (int)std::floor(getValue() - getMinValue());
	if (!(0 <= index && index < (int)labels.size()))
		return "";
	return labels[index];
}

void SwitchQuantity::setDisplayValueString(std::string s) {
	// Find label that matches string, case insensitive.
	auto it = std::find_if(labels.begin(), labels.end(), [&](const std::string &a) {
		return string::lowercase(a) == string::lowercase(s);
	});
	if (it == labels.end())
		return;
	int index = std::distance(labels.begin(), it);
	setImmediateValue(getMinValue() + index);
}

} // namespace rack::engine
