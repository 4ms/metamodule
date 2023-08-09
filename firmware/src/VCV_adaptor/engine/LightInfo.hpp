#pragma once
#include "VCV_adaptor/common.hpp"

namespace rack::engine
{

struct Module;

struct LightInfo {
	Module *module = nullptr;
	int lightId = -1;
	std::string_view name;
	std::string_view description;

	virtual ~LightInfo() = default;
	virtual std::string_view getName() {
		return "";
	}
	virtual std::string_view getDescription() {
		return "";
	}
};

} // namespace rack::engine
