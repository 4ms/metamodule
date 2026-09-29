#pragma once
#include "CoreModules/moduleFactory.hh"
#include "dynload/json_parse.hh"
#include "dynload/register_metadata.hh"
#include "gui/pages/module_view/element_layout.hh"
#include "settings.hh"
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace MetaModule::Headless
{

// Checks a plugin's element groups, order, and names (from plugin-mm.json) by resolving
// them exactly as the module view does, with ElementLayout. The plugin must be built into
// the simulator as an ext-plugin, so its modules are registered.
// Returns the process exit code: 0 if there were no errors.
inline int check_element_layout(MetaModuleSim::Settings const &settings) {
	auto read = [](std::string const &path, std::vector<char> &contents) {
		std::ifstream file{path, std::ios::binary};
		if (!file)
			return false;
		std::stringstream ss;
		ss << file.rdbuf();
		auto str = ss.str();
		contents.assign(str.begin(), str.end());
		return true;
	};

	Plugin::Metadata metadata;
	std::vector<char> buffer;

	if (settings.plugin_json.size()) {
		if (!read(settings.plugin_json, buffer)) {
			printf("Error: cannot read %s\n", settings.plugin_json.c_str());
			return 1;
		}
		Plugin::parse_json(buffer, &metadata);
	}

	if (!read(settings.plugin_mm_json, buffer)) {
		printf("Error: cannot read plugin-mm.json: '%s'\n", settings.plugin_mm_json.c_str());
		return 1;
	}
	if (!Plugin::parse_mm_json(buffer, &metadata)) {
		printf("Error: cannot parse %s\n", settings.plugin_mm_json.c_str());
		return 1;
	}

	auto const &brand = metadata.brand_slug;
	if (brand.empty()) {
		printf("Error: no brand slug in plugin.json or plugin-mm.json\n");
		return 1;
	}

	auto all_slugs = ModuleFactory::getAllModuleSlugs(brand);
	if (all_slugs.empty()) {
		printf("Error: no modules are registered for brand '%s'. Is the plugin built in as an ext-plugin, with this "
			   "brand slug?\n",
			   brand.c_str());
		return 1;
	}

	Plugin::register_metadata(metadata);

	std::vector<std::string> slugs;
	if (settings.modules.empty()) {
		for (auto slug : all_slugs)
			slugs.emplace_back(slug);
	} else {
		slugs = settings.modules;
	}

	unsigned num_errors = 0;
	unsigned num_modules_with_errors = 0;

	for (auto const &slug : slugs) {
		if (std::ranges::find(all_slugs, slug) == all_slugs.end()) {
			printf("%s: Error: no module with this slug in brand '%s'\n", slug.c_str(), brand.c_str());
			num_errors++;
			num_modules_with_errors++;
			continue;
		}

		auto combined_slug = brand + ":" + slug;

		// A VCV-ported module's element names aren't final until it's been created
		auto module = ModuleFactory::create(combined_slug);
		if (!module)
			printf("%s: Warning: could not create module, element names might not be final\n", slug.c_str());

		ElementLayout layout;
		layout.build(combined_slug, nondrawn_elements(combined_slug));

		for (auto const &error : layout.errors)
			printf("%s: Error: %s\n", slug.c_str(), error.c_str());

		if (layout.errors.size()) {
			num_errors += layout.errors.size();
			num_modules_with_errors++;
		} else {
			printf("%s: OK\n", slug.c_str());
		}
	}

	printf("Checked %zu module(s) of %s: %u error(s) in %u module(s)\n",
		   slugs.size(),
		   brand.c_str(),
		   num_errors,
		   num_modules_with_errors);

	return num_errors ? 1 : 0;
}

} // namespace MetaModule::Headless
