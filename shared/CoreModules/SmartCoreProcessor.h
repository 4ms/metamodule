#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/elements/element_counter.hh"
#include <array>
#include <optional>

template<typename INFO>
class SmartCoreProcessor : public CoreProcessor {
public:
	SmartCoreProcessor() {
	}

protected:
	void setOutput(int i, float val) {
		if (i < (int)outputValues.size())
			outputValues[i] = val;
	}

	void setLED(int i, float val) {
		if (i < (int)ledValues.size())
			ledValues[i] = val;
	}

	std::optional<float> getInput(int i) {
		if (i < (int)inputValues.size()) {
			auto result = inputValues[i];
			inputValues[i].reset();
			return result;
		}
		return {};
	}

	float getKnob(int i) {
		if (i < (int)paramValues.size())
			return paramValues[i];
		return 0.f;
	}

	float getSwitch(int i) {
		if (i < (int)paramValues.size())
			return paramValues[i];
		return 0.f;
	}

protected:
	float get_output(int output_id) const override {
		if (output_id < (int)outputValues.size())
			return outputValues[output_id] / 5.f; // Note: this undoes what CommModule does
		return 0.f;
	}

	void set_input(int input_id, float val) override {
		if (input_id < (int)inputValues.size())
			inputValues[input_id] = val * 5.f; // Note: this undoes what CommModule does
	}

	void set_param(int param_id, float val) override {
		if (param_id < (int)paramValues.size()) {
			paramValues[param_id] = val;
		}
	}

	float get_led_brightness(int led_id) const override {
		// ignores switches with light for now
		if (led_id < (int)ledValues.size()) {
			return ledValues[led_id];
		} else {
			return 0.0f;
		}
	}

private:
	constexpr static ElementCount::Counts counts = ElementCount::count<INFO>();

	std::array<float, counts.num_params> paramValues;
	std::array<std::optional<float>, counts.num_inputs> inputValues;
	std::array<float, counts.num_outputs> outputValues;

	// ignores switches with light for now
	std::array<float, counts.num_lights> ledValues;
};
