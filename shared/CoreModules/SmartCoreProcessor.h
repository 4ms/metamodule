#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/param_scales.hh"
#include <array>
#include <optional>

template<typename INFO>
class SmartCoreProcessor : public CoreProcessor {
	using Elem = typename INFO::Elem;

public:
	SmartCoreProcessor() = default;

protected:
	void setLED(Elem el, float val, size_t color_idx = 0) {
		if (count(el).num_lights == 0)
			return;
		auto idx = index(el);
		auto led_idx = idx.light_idx + color_idx;
		if (led_idx < ledValues.size())
			ledValues[led_idx] = val;
	}

	void setOutput(Elem el, float val) {
		if (count(el).num_outputs == 0)
			return;
		auto idx = index(el);
		outputValues[idx.output_idx] = val;
	}

	std::optional<float> getInput(Elem el) {
		if (count(el).num_inputs == 0)
			return 0;
		auto idx = index(el);
		auto result = inputValues[idx.input_idx];
		inputValues[idx.input_idx].reset();
		return result;
	}

	float getParam(Elem el) {
		if (count(el).num_params == 0)
			return 0;
		auto idx = index(el);
		return paramValues[idx.param_idx];
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

	void set_and_scale_param(int param_id, float val) override {
		if (param_id < (int)paramValues.size()) {
			val *= param_scales[param_id].range;
			val += param_scales[param_id].offset;
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
	constexpr static auto element_index(Elem el) {
		return static_cast<std::underlying_type_t<Elem>>(el);
	}

	constexpr static auto index(Elem el) {
		auto element_idx = element_index(el);
		return indices[element_idx];
	}

	constexpr static auto count(Elem el) {
		auto element_idx = element_index(el);
		return ElementCount::count(INFO::Elements[element_idx]);
	}

	constexpr static auto counts = ElementCount::count<INFO>();
	constexpr static auto indices = ElementCount::get_indices<INFO>();
	constexpr static auto param_scales = PotElementHelper::param_scales<INFO>();

	std::array<float, counts.num_params> paramValues;
	std::array<std::optional<float>, counts.num_inputs> inputValues;
	std::array<float, counts.num_outputs> outputValues;
	std::array<float, counts.num_lights> ledValues;
};
