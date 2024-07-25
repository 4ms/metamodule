#include "module_creator.hh"
namespace rack::plugin
{
struct Plugin;
}

namespace MetaModuleAirwindows
{
std::vector<ModuleCreator> modules;
}

#ifdef BUILD_DYN_PLUGIN
__attribute__((__visibility__("default")))
#else
namespace MetaModuleAirwindows
{
#endif

	void init(rack::plugin::Plugin *p) {

	for (unsigned reg_idx = 0; auto module : AirwinRegistry::registry) {
		MetaModuleAirwindows::modules.emplace_back(reg_idx);
		reg_idx++;
	}
}

#ifdef BUILD_DYN_PLUGIN
#else
}
#endif
