#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/element_state_conversion.hh"
#include <array>
#include <optional>

namespace MetaModule
{

template<typename INFO>
class SmartCoreProcessor : public CoreProcessor {
	using Elem = typename INFO::Elem;

	constexpr static auto element_index(Elem el) {
		return static_cast<std::underlying_type_t<Elem>>(el);
	}

	constexpr static auto count(Elem el) {
		auto element_idx = element_index(el);
		return ElementCount::count(INFO::Elements[element_idx]);
	}

protected:
	template<Elem EL>
	void setOutput(float val) requires(count(EL).num_outputs == 1)
	{
		auto idx = index(EL);
		outputValues[idx.output_idx] = val;
	}

	template<Elem EL>
	bool isPatched() requires(count(EL).num_outputs == 1)
	{
		auto idx = index(EL);
		return outputPatched[idx.output_idx];
	}

	template<Elem EL>
	bool isPatched() requires(count(EL).num_inputs == 1)
	{
		auto idx = index(EL);
		return inputValues[idx.input_idx].has_value();
	}

	template<Elem EL>
	std::optional<float> getInput() requires(count(EL).num_inputs == 1)
	{
		auto idx = index(EL);
		auto result = inputValues[idx.input_idx];
		inputValues[idx.input_idx].reset();
		return result;
	}

	template<Elem EL>
	auto getState() requires(count(EL).num_params > 0)
	{
		// get back the typed element from the list of elements
		constexpr auto elementID = element_index(EL);
		constexpr auto &elementRef = INFO::Elements[elementID];

		// reconstruct the element with its original type
		constexpr auto variantIndex = elementRef.index();
		constexpr auto specializedElement = std::get<variantIndex>(elementRef);

		// read raw value
		std::array<float, specializedElement.NumParams> rawValues;
		for (std::size_t i = 0; i < rawValues.size(); i++) {
			rawValues[i] = getParamRaw(EL, i);
		}

		// call conversion function for that type of element
		// use shortcut for special but common case of single parameter elements
		// in order to keep the conversion functions simple
		if constexpr (rawValues.size() == 1) {
			return MetaModule::StateConversion::convertState(specializedElement, rawValues[0]);
		} else {
			return MetaModule::StateConversion::convertState(specializedElement, rawValues);
		}
	}

	template<Elem EL, typename VAL>
	void setLED(const VAL &value) requires(count(EL).num_lights > 0)
	{
		// get back the typed element from the list of elements
		constexpr auto elementID = static_cast<size_t>(EL);
		constexpr auto &elementRef = INFO::Elements[elementID];

		// reconstruct the element with its original type
		constexpr auto variantIndex = elementRef.index();
		constexpr auto specializedElement = std::get<variantIndex>(elementRef);

		// call conversion function for that type of element
		auto rawValues = StateConversion::convertLED(specializedElement, value);

		for (std::size_t i = 0; i < rawValues.size(); i++) {
			setLEDRaw(EL, rawValues[i], i);
		}
	}

private:
	float getParamRaw(Elem el, size_t local_index = 0) {
		auto idx = index(el);
		auto param_id = idx.param_idx + local_index;
		return (param_id < paramValues.size()) ? paramValues[param_id] : 0.f;
	}

	void setLEDRaw(Elem el, float val, size_t color_idx = 0) {
		auto idx = index(el);
		auto led_idx = idx.light_idx + color_idx;
		if (led_idx < ledValues.size())
			ledValues[led_idx] = val;
	}

	constexpr static auto counts = ElementCount::count<INFO>();
	constexpr static auto indices = ElementCount::get_indices<INFO>();

	constexpr static auto index(Elem el) {
		auto element_idx = element_index(el);
		return indices[element_idx];
	}

public:
	float get_output(int output_id) const override {
		if (output_id < (int)outputValues.size())
			return outputValues[output_id];
		return 0.f;
	}

	void set_input(int input_id, float val) override {
		if (input_id < (int)inputValues.size())
			inputValues[input_id] = val;
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

	void mark_all_inputs_unpatched() override {
		std::fill(inputValues.begin(), inputValues.end(), std::nullopt);
	}

	void mark_input_unpatched(const int input_id) override {
		inputValues[input_id].reset();
	}

	void mark_input_patched(const int input_id) override {
		// do nothing here
		// value will be set by next update
	}

	void mark_all_outputs_unpatched() override {
		std::fill(outputPatched.begin(), outputPatched.end(), false);
	}

	void mark_output_unpatched(int output_id) override {
		outputPatched[output_id] = false;
	}

	void mark_output_patched(int output_id) override {
		outputPatched[output_id] = true;
	}

private:
	std::array<float, counts.num_params> paramValues{};
	std::array<std::optional<float>, counts.num_inputs> inputValues{0};
	std::array<float, counts.num_outputs> outputValues{};
	std::array<float, counts.num_lights> ledValues{};
	std::array<bool, counts.num_outputs> outputPatched{};
};

} // namespace MetaModule
