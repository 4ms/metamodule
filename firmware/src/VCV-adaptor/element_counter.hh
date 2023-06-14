#pragma once
#include "CoreModules/elements.hh"

template<typename Info>
struct ElementCount {

	template<typename... Ts>
	struct Overload : Ts... {
		using Ts::operator()...;
	};

	struct Counts {
		size_t num_params = 0;
		size_t num_inputs = 0;
		size_t num_outputs = 0;
		size_t num_lights = 0;
	};

	static constexpr Counts count() {
		Counts c;

		auto CountParams = Overload{
			[](MetaModule::BaseElement) {}, //default: ignore

			[&c](MetaModule::Pot) { c.num_params++; },
			[&c](MetaModule::Switch) { c.num_params++; },
			[&c](MetaModule::Light) { c.num_lights++; },
			[&c](MetaModule::JackInput) { c.num_inputs++; },
			[&c](MetaModule::JackOutput) { c.num_outputs++; },
			[&c](MetaModule::LEDEncoder) {
			c.num_lights += 3;
			c.num_params++;
			},
		};

		for (auto e : Info::Elements)
			std::visit(CountParams, e);

		return {c.num_params, c.num_inputs, c.num_outputs, c.num_lights};
	}
};
