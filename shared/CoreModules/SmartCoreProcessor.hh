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

		// construct element of same type as the element the enum points to
		constexpr auto variantIndex = elementRef.index();
		std::variant_alternative_t<variantIndex, Element> DummyElement;

		// read raw value
		std::array<float, DummyElement.NumParams> rawValues;
		for (std::size_t i = 0; i < rawValues.size(); i++) {
			rawValues[i] = getParamRaw(EL, i);
		}

		// call conversion function for that type of element
		// use shortcut for special but common case of single parameter elements
		// in order to keep the conversion functions simple
		if constexpr (rawValues.size() == 1) {
			return MetaModule::StateConversion::convertState(DummyElement, rawValues[0]);
		} else {
			return MetaModule::StateConversion::convertState(DummyElement, rawValues);
		}
	}

	template<Elem EL, typename VAL>
	void setLED(const VAL &value) requires(count(EL).num_lights > 0)
	{
		// get back the typed element from the list of elements
		constexpr auto elementID = static_cast<size_t>(EL);
		constexpr auto &elementRef = INFO::Elements[elementID];

		// construct element of same type as the element the enum points to
		constexpr auto variantIndex = elementRef.index();
		std::variant_alternative_t<variantIndex, Element> DummyElement;

		// call conversion function for that type of element
		auto rawValues = StateConversion::convertLED(DummyElement, value);

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

protected:
	float get_output(int output_id) const override {
		if (output_id < (int)outputValues.size())
			return outputValues[output_id]; // Note: this undoes what CommModule does
		return 0.f;
	}

	void set_input(int input_id, float val) override {
		if (input_id < (int)inputValues.size())
			inputValues[input_id] = val; // Note: this undoes what CommModule does
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
	constexpr static auto counts = ElementCount::count<INFO>();
	constexpr static auto indices = ElementCount::get_indices<INFO>();

	constexpr static auto index(Elem el) {
		auto element_idx = element_index(el);
		return indices[element_idx];
	}

	std::array<float, counts.num_params> paramValues;
	std::array<std::optional<float>, counts.num_inputs> inputValues;
	std::array<float, counts.num_outputs> outputValues;
	std::array<float, counts.num_lights> ledValues;
};

} // namespace MetaModule
