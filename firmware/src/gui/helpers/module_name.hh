#pragma once
#include "CoreModules/moduleFactory.hh"
#include "patch/patch_data.hh"
#include <string>

namespace MetaModule
{
// FIXME: There are a lot of other place this is used, too, so change them to use this.

// The name shown for a module: its alias if it has one, otherwise the module's display name
inline std::string module_display_name(PatchData const &pd, uint16_t module_id) {
	if (module_id >= pd.module_slugs.size())
		return "?";

	auto alias = pd.get_module_alias(module_id);
	if (!alias.empty())
		return std::string{alias};

	return std::string{ModuleFactory::getModuleDisplayName(pd.module_slugs[module_id])};
}

} // namespace MetaModule
