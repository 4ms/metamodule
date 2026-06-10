#include "vcv_plugin/internal/rack_module_registry.hh"

// Test stub: the test build has no rack::engine::Module instances,
// so nothing is ever a rack module.

namespace MetaModule::RackModuleRegistry
{

void register_module(rack::engine::Module *) {
}

void unregister_module(rack::engine::Module *) {
}

rack::engine::Module *as_rack_module(CoreProcessor *) {
	return nullptr;
}

} // namespace MetaModule::RackModuleRegistry
