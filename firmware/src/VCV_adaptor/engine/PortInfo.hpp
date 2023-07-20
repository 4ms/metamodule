#pragma once
#include "VCV_adaptor/common.hpp"
#include "VCV_adaptor/engine/Port.hpp"
#include <string_view>

namespace rack::engine
{

struct Module;

struct PortInfo {
	Module *module = nullptr;
	Port::Type type = Port::INPUT;
	int portId = -1;

	std::string_view name;
	std::string_view description;

	std::string_view getName() {
		return "";
	}
	std::string_view getFullName() {
		return "";
	}
	std::string_view getDescription() {
		return "";
	}
};

} // namespace rack::engine
