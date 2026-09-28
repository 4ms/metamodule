#pragma once
#include "CoreModules/moduleFactory.hh"
#include "dynload/json_parse.hh"

namespace MetaModule::Plugin
{

// Apply a plugin's metadata (from plugin.json and plugin-mm.json) to its modules, which
// must already be registered in the ModuleFactory.
// Used for plugins loaded at runtime, for built-in brands, and by the headless simulator,
// so they all end up with the same display names, groups, order, and element names.
inline void register_metadata(Metadata const &metadata) {
	if (metadata.display_name.length())
		ModuleFactory::setBrandDisplayName(metadata.brand_slug, metadata.display_name);

	for (auto const &alias : metadata.brand_aliases)
		ModuleFactory::registerBrandAlias(metadata.brand_slug, alias);

	for (auto const &alias : metadata.module_display_names) {
		if (!alias.slug.length())
			continue;

		if (alias.display_name.length())
			ModuleFactory::setModuleDisplayName(metadata.brand_slug + ":" + alias.slug, alias.display_name);

		if (alias.element_groups.size())
			ModuleFactory::setElementGroups(metadata.brand_slug, alias.slug, alias.element_groups);

		if (alias.element_order.size())
			ModuleFactory::setElementOrder(metadata.brand_slug, alias.slug, alias.element_order);

		if (alias.element_names.size())
			ModuleFactory::setElementNames(metadata.brand_slug, alias.slug, alias.element_names);
	}

	for (auto const &m : metadata.module_extras) {
		if (!m.slug.empty()) {
			if (!m.description.empty())
				ModuleFactory::setModuleDescription(metadata.brand_slug + ":" + m.slug, m.description);
			if (m.tags.size() > 0)
				ModuleFactory::setModuleTags(metadata.brand_slug + ":" + m.slug, m.tags);
		}
	}
}

} // namespace MetaModule::Plugin
