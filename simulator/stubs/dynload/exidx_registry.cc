#include "dynload/exidx_registry.hh"

namespace MetaModule::ExidxRegistry
{

void register_range(uintptr_t code_start, uintptr_t code_end, uintptr_t exidx_addr, unsigned num_entries) {
}

void unregister_range(uintptr_t code_start) {
}

} // namespace MetaModule::ExidxRegistry
