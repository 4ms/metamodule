#pragma once

class CoreProcessor;

namespace rack::engine
{
struct Module;
}

namespace MetaModule::RackModuleRegistry
{

// Tracks all live rack::engine::Module instances, so firmware code holding a
// CoreProcessor* can identify rack modules without RTTI (which is not
// guaranteed across .so plugin boundaries) and without changing the plugin
// ABI. Registration happens in rack::engine::Module's ctor/dtor, which are
// firmware-side symbols for all plugins, including ones built with older SDKs.
//
// Not thread-safe: register/unregister/lookup all happen in the GUI/loading
// context (same assumption as ModuleFactory registration).

void register_module(rack::engine::Module *module);
void unregister_module(rack::engine::Module *module);

// Returns the module as a rack::engine::Module, or nullptr if it is not one
rack::engine::Module *as_rack_module(CoreProcessor *module);

} // namespace MetaModule::RackModuleRegistry
