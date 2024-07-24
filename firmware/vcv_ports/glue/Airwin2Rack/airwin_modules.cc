#include "module_creator.hh"
namespace rack::plugin
{
struct Plugin;
}

namespace MetaModuleAirwindows
{
std::vector<ModuleCreator> modules;
}

__attribute__((__visibility__("default"))) void init(rack::plugin::Plugin *p) {

	for (unsigned reg_idx = 0; auto module : AirwinRegistry::registry) {
		MetaModuleAirwindows::modules.emplace_back(reg_idx);
		reg_idx++;
	}
}
