#pragma once
#include "CoreModules/elements/elements.hh"
#include "element_counter.hh"
#include <array>

// TODO: we might not need this once we have named element access
// BUT-- it can save some processing to pre-calc range/offset instead of using min/max
template<typename Info>
struct PotElementHelper {

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

	static constexpr auto get_pot_ranges() {
		std::array<ParamScale, ElementCount<Info>::count().num_params> scales;

		auto CalcParamScales = Overload{
			[](MetaModule::BaseElement) {}, //Ignore everything but pots
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
