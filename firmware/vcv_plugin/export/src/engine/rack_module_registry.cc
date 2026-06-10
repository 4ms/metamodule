#include "vcv_plugin/internal/rack_module_registry.hh"
#include "CoreModules/CoreProcessor.hh"
#include <engine/Module.hpp>
#include <unordered_map>

namespace MetaModule::RackModuleRegistry
{

namespace
{
std::unordered_map<CoreProcessor *, rack::engine::Module *> &registry() {
	static std::unordered_map<CoreProcessor *, rack::engine::Module *> map;
	return map;
}
} // namespace

void register_module(rack::engine::Module *module) {
	registry().insert_or_assign(static_cast<CoreProcessor *>(module), module);
}

void unregister_module(rack::engine::Module *module) {
	registry().erase(static_cast<CoreProcessor *>(module));
}

rack::engine::Module *as_rack_module(CoreProcessor *module) {
	auto &map = registry();
	if (auto it = map.find(module); it != map.end())
		return it->second;
	return nullptr;
}

} // namespace MetaModule::RackModuleRegistry
