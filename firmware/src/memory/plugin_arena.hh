#pragma once
#include <cstddef>
#include <string_view>

namespace MetaModule::PluginArena
{

#if defined(SIMULATOR)

// Hosted builds: plugins share the host allocator; no arena exists
inline bool contains(void const *) {
	return false;
}
inline void *allocator_redirect(std::string_view) {
	return nullptr;
}

#else

// All memory that plugin code allocates lives in a dedicated arena carved off
// the top of the A7 heap (sbrk stops short of it -- see sbrk.cc). Plugins
// reach malloc/free/new/delete only through imports that the dynloader
// rebinds to the mm_plugin_* wrappers (alloc_rescue redirects), which route
// here. Separating ownership by region means a plugin OOM can never exhaust
// or fragment the firmware heap, arena usage is observable, and (stage 2) a
// failed patch can be reclaimed wholesale by resetting the arena instead of
// trusting per-block accounting.
//
// Ownership crosses the boundary in both directions in normal C++ (a string
// allocated by plugin code, freed by firmware's ~string, and vice versa), so
// every free path dispatches by address: firmware's operator delete routes
// arena pointers here, and the plugin free wrappers route firmware-heap
// pointers to newlib free().

// Bytes reserved for the arena, taken from the top of the 290 MB A7 heap.
// Tune against the sysinfo page: firmware heap keeps the remainder.
inline constexpr size_t Size = 160 * 1024 * 1024;

// True if ptr is inside the arena region (valid before init; pure address math)
bool contains(void const *ptr);

// Allocation API. Thread/ISR-safe (guarded by its own retargeted lock, same
// scheme as the newlib malloc lock). alloc() returns nullptr when the arena
// is exhausted.
void *alloc(size_t size);
void *alloc_aligned(size_t align, size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);

// Stats for sysinfo / OOM reports
size_t used_bytes();
size_t peak_bytes();
inline constexpr size_t total_bytes() {
	return Size;
}

// Returns the arena-backed wrapper for an allocator symbol a plugin imports
// ("malloc", "_malloc_r", "_Znwj", ...), or nullptr if the name is not an
// allocator. The dynloader applies this to the host symbol table.
void *allocator_redirect(std::string_view name);

#endif // SIMULATOR

} // namespace MetaModule::PluginArena
