#pragma once
#include "CoreModules/moduleFactory.hh"
#include "CoreModules/register_module.hh"
#include "dynload/json_parse.hh"
#include "ext_plugin_builtin.hh"
#include "fat_file_io.hh"
#include "fs/asset_drive/asset_fs.hh"
#include "fs/asset_drive/untar.hh"
#include "gui/fonts/fonts_init.hh"
#include "internal_plugins.hh"
#include "plugin/Plugin.hpp"
#include <context.hpp>
#include <list>
#include <span>
#include <string_view>

namespace MetaModule
{

struct InternalPluginManager {
	FatFileIO &ramdisk;
	AssetFS &asset_fs;

	std::list<rack::plugin::Plugin> internal_plugins;
	bool asset_fs_valid = true;

	InternalPluginManager(FatFileIO &ramdisk, AssetFS &asset_fs)
		: ramdisk{ramdisk}
		, asset_fs{asset_fs} {
		prepare_ramdisk();
		load_internal_assets();
		load_internal_plugins();
		load_ext_builtin_plugins(internal_plugins);
		ModuleFactory::setBrandDisplayName("4msCompany", "4ms");
	}

	void prepare_ramdisk() {
		if (!ramdisk.format_disk()) {
			pr_err("Could not format RamDisk, no assets can be loaded!\n");
			return;
		} else
			pr_dbg("RamDisk formatted and mounted\n");
	}

	void load_internal_assets() {
		auto raw_image = asset_fs.read_image();
		auto asset_tar = Tar::Archive(raw_image);
		// asset_tar.print_contents();

		if (asset_tar.is_valid()) {
			// asset_tar.print_info();
			asset_fs_valid = true;
		} else {
			pr_err("Internal Assets tar file is not valid\n");
			asset_fs_valid = false;
		}

		auto ramdisk_writer = [&](const std::string_view filename, std::span<const char> buffer) -> uint32_t {
			return ramdisk.write_file(filename, buffer);
		};

		asset_tar.extract_files(ramdisk_writer);

		ramdisk.debug_print_disk_info();

		Fonts::init_fonts(ramdisk);

		ramdisk.make_dir("/usr");
	}

	void load_internal_plugins() {
		rack::contextSet(nullptr);

		// Load internal plugins

		// Native modules:
		// register_module<YourModuleClass, YourModuleInfoClass>("MyBrandSlug");
		// parse_metadata(yourModuleJsonStringView, yourModuleMMJsonStringView);

		// VCV Ports:
		// pluginInstance = &internal_plugins.emplace_back("YourInternalBrandHere");
		// pluginInstance->addModel(yourModuleName);
		// parse_metadata(yourModuleJson, yourModuleMMJson);
	}

	void parse_metadata(std::string_view plugin_json, std::string_view plugin_mm_json) {
		Plugin::Metadata metadata;

		std::string json_working_data{plugin_json};
		Plugin::parse_json(json_working_data, &metadata);

		std::string mm_json_working_data{plugin_json};
		Plugin::parse_mm_json(mm_json_working_data, &metadata);

		ModuleFactory::setBrandDisplayName(metadata.brand_slug, metadata.display_name);

		for (auto const &alias : metadata.brand_aliases)
			ModuleFactory::registerBrandAlias(metadata.brand_slug, alias);

		for (auto const &alias : metadata.module_display_names) {
			if (alias.display_name.length() && alias.slug.length()) {
				ModuleFactory::setModuleDisplayName(metadata.brand_slug + ":" + alias.slug, alias.display_name);
			}
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
};
} // namespace MetaModule
