#pragma once
#include "CoreModules/elements.hh"
#include <array>

template<typename Info>
struct ElementCount {

	template<typename... Ts>
	struct Overload : Ts... {
		using Ts::operator()...;
	};
	template<class... Ts>
	Overload(Ts...) -> Overload<Ts...>;

	struct Counts {
		size_t num_params = 0;
		size_t num_pots = 0;
		size_t num_switches = 0;
		size_t num_inputs = 0;
		size_t num_outputs = 0;
		size_t num_lights = 0;
	};

	static constexpr Counts count() {
		using namespace MetaModule;

		Counts c;

		// clang-format off
		auto CountParams = Overload{
			[](BaseElement) {}, //default: ignore
			[&c](Pot) { c.num_params++; c.num_pots++;},
			[&c](Switch) { c.num_params++; c.num_switches++;},
			[&c](MonoLight) { c.num_lights++; },
			[&c](JackInput) { c.num_inputs++; },
			[&c](JackOutput) { c.num_outputs++; },
			[&c](LEDEncoder) { c.num_lights += 3; c.num_params++; },
			[&c](LatchingButtonMonoLight) { c.num_lights++; c.num_params++; c.num_switches++; },
			[&c](MomentaryButtonRGB) { c.num_lights+=3; c.num_params++; c.num_switches++;},
			[&c](DualLight) { c.num_lights+=2; },
			[&c](MediumLight<RedGreenBlueLight>) { c.num_lights+=3; },
		};
		// clang-format on

		for (auto el : Info::Elements) {
			std::visit(CountParams, el);
		}

		return c;
	}

	struct ParamScale {
		float range;
		float offset;
	};

	static constexpr auto param_scales() {
		std::array<ParamScale, count().num_params> scales;

		auto CalcParamScales = Overload{
			[](MetaModule::BaseElement) {}, //default: ignore
			[&scales](MetaModule::Pot el) {
			if (el.idx < scales.size()) {
				scales[el.idx].range = el.max_val - el.min_val;
				scales[el.idx].offset = el.min_val;
			}
			},
		};

		for (auto el : Info::Elements)
			std::visit(CalcParamScales, el);

		return scales;
	}
};
