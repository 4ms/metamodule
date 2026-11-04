#pragma once
#include "CoreModules/moduleFactory.hh"
#include "util/string_compare.hh"
#include <span>
#include <string>
#include <string_view>
#include <utility>

namespace MetaModule::PluginModuleSlugs
{

// A plugin's modules are described by a list of slugs, each one either:
//   - a brand, e.g. "Befaco": every module in the brand (a brand the plugin created), or
//   - a combined slug, e.g. "Befaco:EvenVCO": a single module (one the plugin added
//     to a brand that already existed, such as another plugin's or a built-in brand)

inline std::pair<std::string_view, std::string_view> split(std::string_view slug) {
	if (auto colon = slug.find(':'); colon != std::string_view::npos)
		return {slug.substr(0, colon), slug.substr(colon + 1)};
	return {slug, {}};
}

// Whether a module in a patch (combined slug "Brand:Module") is one of the plugin's modules.
// Brands are compared like ModuleFactory looks them up: resolving aliases, and case-insensitively.
inline bool module_is_from_plugin(std::string_view patch_module_slug, std::string_view plugin_slug) {
	auto [patch_brand, patch_module] = split(patch_module_slug);
	auto [plugin_brand, plugin_module] = split(plugin_slug);

	if (!equal_ci(ModuleFactory::cleanupBrandName(patch_brand), ModuleFactory::cleanupBrandName(plugin_brand)))
		return false;

	return plugin_module.empty() || plugin_module == patch_module;
}

inline bool module_is_from_plugin(std::string_view patch_module_slug, std::span<const std::string> plugin_slugs) {
	for (auto const &plugin_slug : plugin_slugs) {
		if (module_is_from_plugin(patch_module_slug, plugin_slug))
			return true;
	}
	return false;
}

// Removes the plugin's modules from the ModuleFactory. Returns the number of brands
// and modules removed.
// This destroys each module's CreateModuleFunc, whose type-erasure manager may live
// in the plugin's code: call it while the plugin's code is still loaded.
inline unsigned unregister(std::span<const std::string> plugin_slugs) {
	unsigned num_removed = 0;

	for (auto const &slug : plugin_slugs) {
		auto [brand, module] = split(slug);
		bool removed = module.empty() ? ModuleFactory::unregisterBrand(brand) :
										ModuleFactory::unregisterModule(brand, module);
		if (removed)
			num_removed++;
	}

	return num_removed;
}

} // namespace MetaModule::PluginModuleSlugs
