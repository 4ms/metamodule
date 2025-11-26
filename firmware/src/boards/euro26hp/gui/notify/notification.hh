#pragma once
#include "util/static_string.hh"

namespace MetaModule
{

struct Notification {
	StaticString<255> message;
	enum class Priority { Status, Info, Error } priority{};
	int duration_ms{2000};
};

} // namespace MetaModule
