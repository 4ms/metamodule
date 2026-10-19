#include "dynload/exidx_registry.hh"

// STUB: no plugins on MP2 yet (see dynload/dynloader.hh). AArch64 also has no .ARM.exidx tables:
// plugin unwind info will be .eh_frame, registered with __register_frame_info() instead.

namespace MetaModule::ExidxRegistry
{

void register_range(uintptr_t code_start, uintptr_t code_end, uintptr_t exidx_addr, unsigned num_entries) {
}

void unregister_range(uintptr_t code_start) {
}

} // namespace MetaModule::ExidxRegistry
