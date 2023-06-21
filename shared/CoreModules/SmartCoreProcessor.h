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
	void setLED(auto el, float val, size_t color_idx = 0) {
		if (ElementCount::count(el).num_lights) {
			if (auto idx = ElementCount::get_indices<INFO>(el)) {
				auto led_idx = idx->light_idx + color_idx;
				if (led_idx < ledValues.size())
					ledValues[led_idx] = val;
			}
		}
	}

	void setOutput(MetaModule::JackOutput el, float val) {
		if (auto idx = ElementCount::get_indices<INFO>(el)) {
			outputValues[idx->output_idx] = val;
		}
	}

	std::optional<float> getInput(MetaModule::JackInput el) {
		if (auto idx = ElementCount::get_indices<INFO>(el)) {
			auto result = inputValues[idx->input_idx];
			inputValues[idx->input_idx].reset();
			return result;
		}
		return {};
	}

	float getParam(MetaModule::ParamElement el) {
		if (auto idx = ElementCount::get_indices<INFO>(el)) {
			return paramValues[idx->param_idx];
		}
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
	std::array<float, counts.num_lights> ledValues;
};
