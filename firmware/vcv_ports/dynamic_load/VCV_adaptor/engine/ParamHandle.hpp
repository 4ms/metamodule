#pragma once
#include "VCV_adaptor/nanovg.h"
#include <cstdint>
#include <string_view>

namespace rack::engine
{
struct Module;

struct ParamHandle {
	int64_t moduleId = -1;
	int paramId = 0;
	Module *module = nullptr;
	std::string_view text;
	NVGcolor color;
};

} // namespace rack::engine
