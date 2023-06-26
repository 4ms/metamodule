#pragma once
#include "CoreModules/elements/elements.hh"
#include "element_counter.hh"
#include <array>

// TODO: we might not need this once we have named element access
// BUT-- it can save some processing to pre-calc range/offset instead of using min/max
namespace PotElementHelper
{

template<typename... Ts>
struct Overload : Ts... {
	using Ts::operator()...;
};
template<class... Ts>
Overload(Ts...) -> Overload<Ts...>;

struct ParamScale {
	float range;
	float offset;
};

template<typename Info>
consteval auto param_scales() {
	std::array<ParamScale, ElementCount::count<Info>().num_params> scales;

	auto CalcParamScales = Overload{
		//Default is 0->1
		[&scales](MetaModule::BaseElement el) {
		if (auto c = ElementCount::get_indices<Info>(el)) {
			if (c->param_idx < scales.size()) {
				scales[c->param_idx].range = 1;
				scales[c->param_idx].offset = 0;
			}
		}
		},

		// Pots set their range in the Elements array
		[&scales](MetaModule::Pot el) {
		if (auto c = ElementCount::get_indices<Info>(el)) {
			scales[c->param_idx].range = el.max_val - el.min_val;
			scales[c->param_idx].offset = el.min_val;
		}
	},

		 // Special-case: 3-pos switch is 0->2
		[&scales](MetaModule::Toggle3pos el) {
		if (auto c = ElementCount::get_indices<Info>(el)) {
			scales[c->param_idx].range = 2;
			scales[c->param_idx].offset = 0;
		}
	},
		};

	for (auto el : Info::Elements) {
		std::visit(CalcParamScales, el);
	}

	return scales;
}
}; // namespace PotElementHelper
