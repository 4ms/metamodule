#pragma once
#include "CoreModules/elements/elements.hh"
#include <cstdint>

namespace MetaModule
{

struct ModuleParam {
	enum class Type { Knob, Switch, InJack, OutJack } type{Type::OutJack};
	uint32_t id;

	static auto get_type(const BaseElement &) {
		return Type::Knob;
	}

	static auto get_type(const Pot &) {
		return Type::Knob;
	}

	static auto get_type(const Switch &) {
		return Type::Switch;
	}

	static auto get_type(const JackInput &) {
		return Type::InJack;
	}

	static auto get_type(const JackOutput &) {
		return Type::OutJack;
	}
};

} // namespace MetaModule
