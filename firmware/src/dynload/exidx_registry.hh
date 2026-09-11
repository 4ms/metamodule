#pragma once
#include <cstdint>

// Registry of ARM exception-index (.ARM.exidx) tables for loaded plugins.
//
// libgcc's unwinder declares __gnu_Unwind_Find_exidx as a weak symbol and,
// when it is defined, calls it for every frame instead of using its baked-in
// __exidx_start/__exidx_end fallback. exidx_registry.cc defines it strongly:
// the firmware's unwinder becomes aware of every loaded plugin's unwind
// table, so an exception can unwind through plugin frames. Plugins built
// with SDK >= 2.3 contain a shim routing their own unwinder here as well
// (via the mm_host_find_exidx export), which is what allows exceptions to
// cross the plugin/host boundary in either direction.

namespace MetaModule::ExidxRegistry
{

// Register the unwind table of a loaded plugin, covering code addresses
// [code_start, code_end). Replaces any existing entry with the same
// code_start.
void register_range(uintptr_t code_start, uintptr_t code_end, uintptr_t exidx_addr, unsigned num_entries);

// Remove the entry starting at code_start.
void unregister_range(uintptr_t code_start);

} // namespace MetaModule::ExidxRegistry
