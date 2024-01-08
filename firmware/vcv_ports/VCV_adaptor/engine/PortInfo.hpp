#pragma once
#include "VCV_adaptor/common.hpp"
#include "VCV_adaptor/engine/Port.hpp"
#include <string>

namespace rack::engine
{

struct Module;

struct PortInfo {
	Module *module = nullptr;
	Port::Type type = Port::INPUT;
	int portId = -1;

	std::string name;
	std::string description;

	std::string getName() {
		return name;
	}
	std::string getFullName() {
		return name;
	}
	std::string getDescription() {
		return description;
	}
};

} // namespace rack::engine
