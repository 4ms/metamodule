#pragma once
#include "ryml.hpp"
#include "ryml_init.hh"
#include "ryml_std.hpp"
#include <algorithm>
#include <span>
#include <string>

namespace MetaModule::Plugin
{

struct Metadata {
	// The name displayed on the screen to users
	std::string display_name;

	// The slug used when saving a patch, and to find modules in this plugin when loading patches.
	std::string brand_slug;

	// When loading a patch, consider use of these names as equivalent to using the brand_slug
	std::vector<std::string> brand_aliases;

	struct ModuleDisplayName {
		std::string slug;
		std::string display_name;
	};
	std::vector<ModuleDisplayName> module_aliases;
};

inline bool parse_json(std::span<char> file_data, Metadata *metadata) {
	RymlInit::init_once();

	// ryml has issues with tabs in json sometimes:
	std::ranges::replace(file_data, '\t', ' ');

	ryml::Tree tree = ryml::parse_in_place(ryml::substr(file_data.data(), file_data.size()));

	if (tree.num_children(0) == 0)
		return false;

	ryml::ConstNodeRef root = tree.rootref();

	if (root.has_child("slug")) {
		root["slug"] >> metadata->brand_slug;
	}

	if (root.has_child("name")) {
		root["name"] >> metadata->display_name;
	}

	// `brand` overrides `name`: https://vcvrack.com/manual/Manifest#brand
	if (root.has_child("brand")) {
		root["brand"] >> metadata->display_name;
	}

	return true;
}

static bool read(ryml::ConstNodeRef const &n, Metadata::ModuleDisplayName *s) {
	if (!n.is_map())
		return false;

	if (n.has_child("slug") && n.has_child("displayName")) {
		n["slug"] >> s->slug;
		n["displayName"] >> s->display_name;
	}
	return true;
}

inline bool parse_mm_json(std::span<char> file_data, Metadata *metadata) {
	RymlInit::init_once();

	// ryml has issues with tabs in json sometimes:
	std::ranges::replace(file_data, '\t', ' ');

	ryml::Tree tree = ryml::parse_in_place(ryml::substr(file_data.data(), file_data.size()));

	if (tree.num_children(0) == 0)
		return false;

	ryml::ConstNodeRef root = tree.rootref();

	if (root.has_child("MetaModuleBrandSlug")) {
		root["MetaModuleBrandSlug"] >> metadata->brand_slug;
	}

	// `MetaModuleBrandName` overrides plugin.json's `brand` and `name`
	if (root.has_child("MetaModuleBrandName")) {
		root["MetaModuleBrandName"] >> metadata->display_name;
	}

	if (root.has_child("MetaModuleBrandAliases")) {
		root["MetaModuleBrandAliases"] >> metadata->brand_aliases;
	}

	if (root.has_child("MetaModuleIncludedModules")) {
		root["MetaModuleIncludedModules"] >> metadata->module_aliases;
	}

	return true;
}

} // namespace MetaModule::Plugin
