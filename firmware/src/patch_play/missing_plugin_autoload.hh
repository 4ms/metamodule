#pragma once
#include "CoreModules/moduleFactory.hh"
#include "dynload/plugin_manager.hh"
#include "patch/patch_data.hh"
#include <set>

namespace MetaModule
{

struct MissingPluginAutoload {
	MissingPluginAutoload(PluginManager &plugin_manager)
		: plugin_manager{plugin_manager} {
	}

	// Scans patch for missing modules, and creates a list of unique brands to load
	bool scan(PatchData *patch) {
		missing_brands.clear();

		if (!patch)
			return false;

		for (std::string_view slug : patch->module_slugs) {
			if (!ModuleFactory::isValidSlug(slug)) {
				pr_info("Missing module: %.*s\n", slug.size(), slug.data());

				if (auto colon = slug.find_first_of(':'); colon != slug.npos) {
					auto [_, ok] = missing_brands.insert(slug.substr(0, colon));
					if (ok)
						pr_info("Will look for brand %.*s\n", colon, slug.substr(0, colon));
				}
			}
		}

		return missing_brands.size() > 0;
	}

	void ask_to_load() {
	}

	void load_missing() {
		for (const auto &brand : missing_brands) {
		}
	}

private:
	PluginManager &plugin_manager;

	std::set<std::string_view> missing_brands;
};

} // namespace MetaModule
