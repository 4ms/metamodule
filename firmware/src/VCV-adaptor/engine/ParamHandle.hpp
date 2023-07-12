#pragma once
#include <cstdint>
#include <string_view>
// #include <color.hpp>

namespace rack::engine
{
struct Module;

struct ParamHandle {
	int64_t moduleId = -1;
	int paramId = 0;
	Module *module = nullptr;
	std::string_view text;
	// NVGcolor color;
};

} // namespace rack::engine
