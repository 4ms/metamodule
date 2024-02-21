#pragma once

#include <string>

namespace MetaModule
{

struct Result {
	bool success = true;
	std::string error_string{};

	operator bool() const {
		return success;
	}
};

} // namespace MetaModule
