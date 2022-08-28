#pragma once
#include <cstdint>

struct ModuleControl {
	enum class Type { Knob, Switch, InJack, OutJack } type;
	uint32_t id;
};
