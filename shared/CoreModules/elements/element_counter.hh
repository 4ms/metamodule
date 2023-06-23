#pragma once
#include "CoreModules/elements/elements.hh"
#include <array>
#include <numeric>
#include <optional>
#include <cstdint>
#include <algorithm>

namespace ElementCount
{

struct Counts {
	size_t num_params = 0;
	size_t num_lights = 0;
	size_t num_inputs = 0;
	size_t num_outputs = 0;

	constexpr Counts operator+(const Counts rhs) {
		return {num_params + rhs.num_params,
				num_lights + rhs.num_lights,
				num_inputs + rhs.num_inputs,
				num_outputs + rhs.num_outputs};
	}
};

struct Indices {
	uint8_t param_idx = 0;
	uint8_t light_idx = 0;
	uint8_t input_idx = 0;
	uint8_t output_idx = 0;

	// Indices + Counts -> Indices
	constexpr Indices operator+(const Counts rhs) {
		return {static_cast<uint8_t>(param_idx + rhs.num_params),
				static_cast<uint8_t>(light_idx + rhs.num_lights),
				static_cast<uint8_t>(input_idx + rhs.num_inputs),
				static_cast<uint8_t>(output_idx + rhs.num_outputs)};
	}
};

constexpr bool operator==(MetaModule::BaseElement a, MetaModule::BaseElement b) {
	// We assume all elements have distinct coordinates and/or names
	// FIXME: This will fail if two elements have different type but identical elements
	return a.x_mm == b.x_mm && a.y_mm == b.y_mm && a.short_name == b.short_name && a.long_name == b.long_name;
}

constexpr Counts count(auto e) {
	return Counts{e.NumParams, e.NumLights, e.NumInputs, e.NumOutputs};
}

constexpr Counts count(MetaModule::Element element) {
	return std::visit([](auto e) { return count(e); }, element);
}

template<typename Info>
constexpr Counts count() {
	return std::accumulate(Info::Elements.begin(), Info::Elements.end(), Counts{}, [](auto total, auto element) {
		return total + count(element);
	});
}

template<typename Info>
constexpr std::optional<size_t> get_element_id(const MetaModule::BaseElement& element) {

	// find iterator into the elements array that matches the given element reference
	auto match = std::find_if(Info::Elements.begin(), Info::Elements.end(),
		[&element](const auto& candidate)
		{
			// cast refernce to reference of base class
			const auto& candidate_base = std::visit([](auto& c)
			{
				return static_cast<const MetaModule::BaseElement&>(c);
			} , candidate);

			return candidate_base == element;
		});

	if (match != Info::Elements.end())
	{
		return std::distance(Info::Elements.begin(), match);
	}
	else
	{
		return std::nullopt;
	}
}

template<typename Info>
constexpr std::optional<Indices> get_indices(const MetaModule::BaseElement& element) {

	// try to get an id for the given element	
	if (auto this_element_id = get_element_id<Info>(element); this_element_id)
	{
		auto this_start_iterator = Info::Elements.begin();
		auto this_end_iterator   = this_start_iterator + *this_element_id;

		// sum up indices up to the given element
		auto idx = std::accumulate(this_start_iterator, this_end_iterator, Indices(), [](auto sum, auto el)
		{
			return sum + count(el);
		});

		return idx;
	}
	return std::nullopt;
}


}; // namespace ElementCount
