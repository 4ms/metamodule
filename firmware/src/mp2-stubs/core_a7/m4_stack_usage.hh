#pragma once
#include <cstdint>

// STUB: stands in for src/core_a7/m4_stack_usage.hh (the M4's stack usage, shown on the System
// Info page). FIXME: report the M33's stack usage.

namespace MetaModule
{

struct M4StackUsage {
	uint32_t unused;
	uint32_t used;
	uint32_t total;
};

inline M4StackUsage m4_stack_usage() {
	return {};
}

} // namespace MetaModule
