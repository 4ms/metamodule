#pragma once
#include <string>

namespace MetaModule
{

struct Notification {
	std::string message;
	enum class Priority { Status, Info, Error } priority{};
	int duration_ms{2000};
};

} // namespace MetaModule
