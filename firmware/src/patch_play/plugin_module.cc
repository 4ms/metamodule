#include "plugin_module.hh"

#include "engine/Module.hpp"

namespace MetaModule
{

static rack::engine::Module *get_rack_plugin_module(std::unique_ptr<CoreProcessor> &module) {
	return dynamic_cast<rack::engine::Module *>(module.get());
}

void plugin_module_deinit(std::unique_ptr<CoreProcessor> &module) {
	if (auto rack_module = get_rack_plugin_module(module)) {
		rack::engine::Module::RemoveEvent rm{};
		rack_module->onRemove(rm);
	}
}

} // namespace MetaModule
