#pragma once
#include <common.hpp>
#include <engine/Port.hpp>

namespace rack::engine
{

struct Module;

struct PortInfo {
	Module *module = nullptr;
	Port::Type type = Port::INPUT;
	int portId = -1;

	std::string name;

	std::string description;

	virtual ~PortInfo() = default;

	virtual std::string getName() {
		return name;
	}

	std::string getFullName() {
		return name;
	}

	virtual std::string getDescription() {
		return description;
	}
};

} // namespace rack::engine
