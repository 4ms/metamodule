#pragma once
#include <cstdint>

struct ModuleParam {
	enum class Type { Knob, Switch, InJack, OutJack } type{Type::OutJack};
	uint32_t id;
};
