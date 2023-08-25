#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"
#include <cstdint>

namespace MetaModule
{

struct ModuleParam {
	const Element *el{nullptr};

	//Are type and id needed?
	enum class Type { None, Knob, Switch, InJack, OutJack, Light } type{Type::None};
	uint32_t id{};

	ModuleParam() = default;

	ModuleParam(const Element &element, ElementCount::Indices idx)
		: el{&element} {
		std::visit([&](auto &el) { set_type(el, idx); }, element);
	}

	void set_type(const BaseElement &el, ElementCount::Indices idx) {
		type = Type::None;
		id = 0;
	}
	void set_type(const Pot &el, ElementCount::Indices idx) {
		type = Type::Knob;
		id = idx.param_idx;
	}
	void set_type(const Switch &el, ElementCount::Indices idx) {
		type = Type::Switch;
		id = idx.param_idx;
	}
	void set_type(const JackInput &el, ElementCount::Indices idx) {
		type = Type::InJack;
		id = idx.input_idx;
	}
	void set_type(const JackOutput &el, ElementCount::Indices idx) {
		type = Type::OutJack;
		id = idx.output_idx;
	}
	void set_type(const LightElement &el, ElementCount::Indices idx) {
		type = Type::Light;
		id = idx.light_idx;
	}
};

} // namespace MetaModule
