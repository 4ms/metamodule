#include "module_creator.hh"
namespace rack::plugin
{
struct Plugin;
}

namespace MetaModuleAirwindows
{
std::vector<ModuleCreator> created_modules;
}

#ifdef BUILD_DYN_PLUGIN
__attribute__((__visibility__("default")))
#else
namespace MetaModuleAirwindows
{
#endif

	void init(rack::plugin::Plugin *p) {

	AirwinConsolidatedBase::defaultSampleRate = 48000;

	for (unsigned reg_idx = 0; auto module : AirwinRegistry::registry) {
		MetaModuleAirwindows::created_modules.emplace_back(reg_idx);
		reg_idx++;
	}
}

#ifdef BUILD_DYN_PLUGIN
#else
}
#endif
