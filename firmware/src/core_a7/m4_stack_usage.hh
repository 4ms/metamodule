#pragma once
#include "ld.h"
#include <cstdint>

namespace MetaModule
{

// The M4's Reset_Handler fills the stack with M4_STACK_CANARY
//
// Caveat: the scan stops at the first non-canary word, so a live stack word that
// happens to equal the canary value is counted as used, so it's possible but unlikely
// it's under-reporting free space. It won't over-report free space.
struct M4StackUsage {
	uint32_t unused;
	uint32_t used;
	uint32_t total;
};

inline M4StackUsage m4_stack_usage() {
	auto const *stack = reinterpret_cast<uint32_t const volatile *>(M4_STACK_A7);
	const uint32_t num_words = M4_STACK_SZ / sizeof(uint32_t);

	uint32_t intact = 0;
	while (intact < num_words && stack[intact] == M4_STACK_CANARY)
		intact++;

	const uint32_t unused = intact * sizeof(uint32_t);
	return {.unused = unused, .used = M4_STACK_SZ - unused, .total = M4_STACK_SZ};
}

} // namespace MetaModule
