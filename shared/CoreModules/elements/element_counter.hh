#pragma once
#include "CoreModules/elements/elements.hh"
#include <numeric>

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
