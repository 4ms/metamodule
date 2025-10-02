#pragma once
#include "CoreModules/moduleFactory.hh"
#include "delay.hh"
#include "dynload/plugin_manager.hh"
#include "dynload/preload_plugins.hh"
#include "lvgl.h"
#include "patch/patch_data.hh"
#include <string>
#include <vector>

namespace MetaModule
{

struct MissingPluginAutoload {

	MissingPluginAutoload(PluginManager &plugin_manager)
		: plugin_manager{plugin_manager} {
	}

	// Scans patch for missing modules, and creates a list of unique brands to load
	void scan(PatchData *patch) {
		brands.clear();
		modules.clear();
		skipped.clear();

		if (!patch) {
			pr_err("MissingPluginAutoload got null patch\n");
			return;
		}

		for (std::string_view slug : patch->module_slugs) {
			if (!ModuleFactory::isValidSlug(slug)) {

				pr_info("Missing module: %.*s\n", slug.size(), slug.data());
				modules.emplace_back(slug);

				if (auto colon = slug.find_first_of(':'); colon != slug.npos) {
					auto brand = std::string(slug.substr(0, colon));

					if (ModuleFactory::isValidBrand(brand)) {
						// Brand plugin is loaded, but module is just not known.
						// We could unload the plugin and scan for newer versions,
						// but for now we just ignore this (users shouldn't have multiple versions present)
						pr_info("Brand is already loaded, ignoring this\n");
						skipped.emplace_back(slug);

					} else {

						if (std::ranges::find(brands, brand) == brands.end())
							brands.push_back(brand);
					}
				}
			}
		}
	}

	std::vector<std::string> &missing_modules() {
		return modules;
	}

	std::vector<std::string> &skipped_modules() {
		return modules;
	}

	std::vector<std::string> &missing_brands() {
		return brands;
	}

	bool is_processing() {
		return processing;
	}

	void start_loading_missing() {
		loader = std::make_unique<PreLoader>(plugin_manager, brands);
		processing = true;
	}

	PreLoader::Status process_loading() {
		if (!is_processing())
			return {PreLoader::State::NotStarted, ""};

		auto status = loader->process();
#ifdef SIMULATOR
		delay_ms(200);
#endif

		if (status.state == PreLoader::State::Done || status.state == PreLoader::State::Error) {
			processing = false;
		}

		return status;
	}

private:
	PluginManager &plugin_manager;
	std::unique_ptr<PreLoader> loader;

	std::vector<std::string> brands;
	std::vector<std::string> modules;

	std::vector<std::string> skipped;

	bool processing = false;
};

} // namespace MetaModule
