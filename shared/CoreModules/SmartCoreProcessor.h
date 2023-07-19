#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/param_scales.hh"
#include "CoreModules/elements/element_state_conversion.hh"
#include <array>
#include <optional>

template<typename INFO>
class SmartCoreProcessor : public CoreProcessor {
	using Elem = typename INFO::Elem;

public:
	SmartCoreProcessor() = default;

protected:
	template <typename INFO::Elem EL>
	void setOutput(float val) requires (ElementCount::count(INFO::Elements[std::size_t(EL)]).num_outputs == 1)
	{
		auto idx = index(EL);
		outputValues[idx.output_idx] = val;
	}

	template <typename INFO::Elem EL>
	std::optional<float> getInput() requires (ElementCount::count(INFO::Elements[std::size_t(EL)]).num_inputs == 1)
	{
		auto idx = index(EL);
		auto result = inputValues[idx.input_idx];
		inputValues[idx.input_idx].reset();
		return result;
	}

	template <typename INFO::Elem EL>
	auto getState() requires (ElementCount::count(INFO::Elements[std::size_t(EL)]).num_params != 0)
	{
		// get back the typed element from the list of elements
		constexpr auto elementID = static_cast<size_t>(EL);
		constexpr auto& elementRef = INFO::Elements[elementID];

		// read raw value
		auto rawValue = getParamRaw(EL);

		// construct element of same type as the element the enum points to
		constexpr auto variantIndex = elementRef.index();
		std::variant_alternative_t<variantIndex,MetaModule::Element> DummyElement;

		// call conversion function for that type of element
		auto result = MetaModule::StateConversion::convertState(DummyElement, rawValue);

		return result;
	}

	template <typename INFO::Elem EL, typename VAL>
	void setLED(const VAL& value)  requires (ElementCount::count(INFO::Elements[std::size_t(EL)]).num_lights != 0)
	{

		// get back the typed element from the list of elements
		constexpr auto elementID = static_cast<size_t>(EL);
		constexpr auto& elementRef = INFO::Elements[elementID];

		// construct element of same type as the element the enum points to
		constexpr auto variantIndex = elementRef.index();
		std::variant_alternative_t<variantIndex,MetaModule::Element> DummyElement;

		// call conversion function for that type of element
		auto rawValues = MetaModule::StateConversion::convertLED(DummyElement, value);

		for (std::size_t i=0; i<rawValues.size(); i++)
		{
			setLEDRaw(EL, rawValues[i], i);
		}
	}

private:
	float getParamRaw(Elem el, std::size_t local_index=0) {
		auto idx = index(el);
		auto param_id = idx.param_idx + local_index;
		return paramValues.at(param_id);
	}

	void setLEDRaw(Elem el, float val, size_t color_idx=0) {
		auto idx = index(el);
		auto led_idx = idx.light_idx + color_idx;
		ledValues.at(led_idx) = val;
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
