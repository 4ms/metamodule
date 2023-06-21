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
constexpr auto param_scales() {
	std::array<ParamScale, ElementCount::count<Info>().num_params> scales;

	auto CalcParamScales = Overload{
		[](MetaModule::BaseElement) {}, //Ignore everything but pots

		[&scales](MetaModule::Pot el) {
		if (auto c = ElementCount::get_indices<Info>(el)) {
			scales[c->param_idx].range = el.max_val - el.min_val;
			scales[c->param_idx].offset = el.min_val;
		}
		},
	};

	for (auto el : Info::Elements) {
		std::visit(CalcParamScales, el);
	}

	return scales;
}
}; // namespace PotElementHelper
