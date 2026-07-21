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

// All memory that plugin code allocates lives in a dedicated arena. Plugins
// reach malloc/new only through imports that the dynloader rebinds
// (allocator_redirect) to the mm_plugin_* wrappers, which route here.
// Separating ownership by region means a plugin OOM can never exhaust or
// fragment the firmware heap, arena usage is observable, and a dead plugin's
// memory can be reclaimed wholesale by resetting the arena instead of
// trusting per-block accounting.
//
// The firmware heap and the arena share the A7 heap region [_sheap, _eheap)
// with a dynamic boundary: the firmware heap grows up from _sheap via sbrk,
// and the arena claims slabs downward from _eheap as needed (returning them
// when they drain). Neither side has a fixed size; slab claims leave a small
// guaranteed headroom above the firmware heap's high-water mark.
//
// Ownership crosses the boundary in both directions in normal C++ (a string
// allocated by plugin code, freed by firmware's ~string, and vice versa), so
// every free/realloc dispatches by address: the firmware links with
// --wrap=free/_free_r/realloc/_realloc_r so all its call sites reach the
// __wrap_* dispatchers in plugin_arena.cc, and plugin imports of those
// symbols are rebound to the same dispatchers.

// True if ptr is inside the arena region (valid before init; pure address math)
bool contains(void const *ptr);

// Allocation API. Thread/ISR-safe (guarded by its own retargeted lock, same
// scheme as the newlib malloc lock). alloc() returns nullptr when the shared
// pool is exhausted.
void *alloc(size_t size);
void *alloc_aligned(size_t align, size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);

// Stats for sysinfo / OOM reports. claimed_bytes() is the arena's current
// share of the heap region (grows and shrinks with slab claims/returns).
size_t used_bytes();
size_t peak_bytes();
size_t claimed_bytes();

// Returns the arena-backed wrapper for an allocator symbol a plugin imports
// ("malloc", "_malloc_r", "_Znwj", ...), or nullptr if the name is not an
// allocator. The dynloader applies this to the host symbol table.
void *allocator_redirect(std::string_view name);

#endif // SIMULATOR

} // namespace MetaModule::PluginArena
