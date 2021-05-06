#pragma once
#include <cstdint>

namespace ScreenSimulator
{
struct SystemCache {
	static void invalidate_dcache() {}

	template<typename ptr>
	static void invalidate_dcache_by_addr(ptr addr)
	{}

	static void invalidate_dcache_by_range(void *addr, int32_t size) {}

	static void clean_dcache() {}

	static void clean_dcache_by_addr(void *addr) {}

	static void clean_dcache_by_range(void *addr, int32_t size) {}
};
} // namespace ScreenSimulator
