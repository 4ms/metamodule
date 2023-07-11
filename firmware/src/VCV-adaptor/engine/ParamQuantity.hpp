#pragma once
#include <vector>

#include "VCV-adaptor/Quantity.hpp"
#include "VCV-adaptor/engine/Param.hpp"
#include "VCV-adaptor/json.hpp"

namespace rack::engine
{

struct Module;

struct ParamQuantity : Quantity {
	// Module *module = nullptr;
	// int paramId = -1;

	float minValue = 0.f;
	float maxValue = 1.f;
	float defaultValue = 0.f;

	std::string_view name = "";
	/** The numerical unit of measurement appended to the value.
	Unit words and abbreviations should have a space to separate the numerical value from the number (e.g. " semitones", " V", " ms").
	Unit symbols should have no space (e.g. "%", "º").
	*/
	std::string unit;
	/** Set to 0 for linear, positive for exponential, negative for logarithmic.
	The formula is \f$displayValue = f(value) * displayMultiplier + displayOffset\f$ where \f$f(value)\f$ is
	- \f$value\f$ for \f$displayBase = 0\f$.
	- \f$\log_{-displayBase}(value)\f$ for \f$displayBase < 0\f$.
	- \f$displayBase^{value}\f$ for \f$displayBase > 0\f$.
	*/
	float displayBase = 0.f;
	float displayMultiplier = 1.f;
	float displayOffset = 0.f;
	/** Number of digits of precision to display.
	With displayPrecision = 5 for example, numbers will print as 12.345, 0.12345, 1.2345e6, or 1.2345e-6.
	*/
	int displayPrecision = 5;
	/** An optional one-sentence description of the parameter. */
	std::string description;

	/** Enables parameter resetting when the module or parameter itself is reset.
	*/
	bool resetEnabled = true;
	/** Enables parameter randomization when the module is randomized.
	Unbounded (infinite) parameters are not randomizable, regardless of this setting.
	*/
	bool randomizeEnabled = true;
	/** Enables per-sample Engine parameter smoothing when setSmoothValue() is called. */
	bool smoothEnabled = false;
	/** Rounds values to the nearest integer. */
	bool snapEnabled = false;

	Param *getParam();
	/** If smoothEnabled is true, requests to the engine to smoothly move to a target value each sample. */
	void setSmoothValue(float value);
	float getSmoothValue();

	void setValue(float value) override;
	float getValue() override;
	float getMinValue() override;
	float getMaxValue() override;
	float getDefaultValue() override;
	float getDisplayValue() override;
	void setDisplayValue(float displayValue) override;
	std::string getDisplayValueString() override;
	void setDisplayValueString(std::string s) override;
	int getDisplayPrecision() override;
	std::string getLabel() override;
	std::string getUnit() override;
	void reset() override;
	void randomize() override;

	virtual std::string getDescription();

	virtual json_t *toJson();
	virtual void fromJson(json_t *rootJ);
};

struct SwitchQuantity : ParamQuantity {
	std::vector<std::string> labels;

	std::string getDisplayValueString() override;
	void setDisplayValueString(std::string s) override;
};

} // namespace rack::engine
