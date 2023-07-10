#pragma once
#include "VCV-adaptor/port.hpp"
#include <string_view>

namespace rack
{

struct Module;

struct PortInfo {
	Module *module = nullptr;
	Port::Type type = Port::INPUT;
	int portId = -1;
	std::string_view name;
	std::string_view description;
};

} // namespace rack
