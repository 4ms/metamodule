#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"
#include <cstdint>

namespace MetaModule
{

struct ModuleParam {
	enum class Type { None, Knob, Switch, InJack, OutJack, Light } type;
	uint32_t id;

	ModuleParam()
		: type{Type::None}
		, id{} {
	}
	ModuleParam(const BaseElement &el, ElementCount::Indices idx)
		: type{Type::Knob}
		, id{idx.param_idx} {
	}
	// ModuleParam(const Pot &el, ElementCount::Indices idx)
	// 	: type{Type::Knob}
	// 	, id{idx.param_idx} {
	// }
	ModuleParam(const Switch &el, ElementCount::Indices idx)
		: type{Type::Switch}
		, id{idx.param_idx} {
	}
	ModuleParam(const JackInput &el, ElementCount::Indices idx)
		: type{Type::InJack}
		, id{idx.input_idx} {
	}
	ModuleParam(const JackOutput &el, ElementCount::Indices idx)
		: type{Type::OutJack}
		, id{idx.output_idx} {
	}
	ModuleParam(const LightElement &el, ElementCount::Indices idx)
		: type{Type::OutJack}
		, id{idx.light_idx} {
	}
};

} // namespace MetaModule
