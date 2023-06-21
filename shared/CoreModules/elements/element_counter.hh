#pragma once
#include "CoreModules/elements/elements.hh"
#include <numeric>
#include <optional>

template<typename Info>
struct ElementCount {

	struct Counts {
		size_t num_params = 0;
		size_t num_lights = 0;
		size_t num_inputs = 0;
		size_t num_outputs = 0;
	};

	static constexpr Counts count() {
		Counts c;

		c.num_params = std::accumulate(Info::Elements.begin(), Info::Elements.end(), 0, [](auto left, auto right) {
			return left + std::visit([](auto el) { return el.NumParams; }, right);
		});

		c.num_lights = std::accumulate(Info::Elements.begin(), Info::Elements.end(), 0, [](auto left, auto right) {
			return left + std::visit([](auto el) { return el.NumLights; }, right);
		});

		c.num_inputs = std::accumulate(Info::Elements.begin(), Info::Elements.end(), 0, [](auto left, auto right) {
			return left + std::visit([](auto el) { return el.NumInputs; }, right);
		});

		c.num_outputs = std::accumulate(Info::Elements.begin(), Info::Elements.end(), 0, [](auto left, auto right) {
			return left + std::visit([](auto el) { return el.NumOutputs; }, right);
		});

		return c;
	}
};

template<typename Info>
struct ElementId {

	static constexpr size_t get_element_id(MetaModule::BaseElement element) {

		for (unsigned i = 0; auto el : Info::Elements) {
			// We assume all elements have distinct coordinates and/or name
			bool is_same = std::visit(
				[element](auto e) {
				return element.x_mm == e.x_mm && element.y_mm == e.y_mm && element.short_name == e.short_name &&
					   element.long_name == e.long_name;
				},
				el);

			if (is_same)
				return i;

			i++;
		}
		return 0;
	}
};

template<typename Info>
static constexpr std::optional<typename ElementCount<Info>::Counts> get_param_id(MetaModule::BaseElement element) {
	size_t light_idx = 0;
	for (size_t param_idx = 0; auto el : Info::Elements) {
		bool is_same = std::visit(
			[element](auto e) {
			return element.x_mm == e.x_mm && element.y_mm == e.y_mm && element.short_name == e.short_name &&
				   element.long_name == e.long_name;
			},
			el);

		auto num_params = std::visit([](auto e) { return e.NumParams; }, el);

		if (is_same) {
			if (num_params)
				return {{param_idx, light_idx}};
			else
				return {};
		}

		param_idx += num_params;
	}
	return {};
}
