#pragma once
#include "CoreModules/moduleFactory.hh"
#include "CoreModules/register_module.hh"
#include "dynload/json_parse.hh"
#include "fat_file_io.hh"
#include "fs/asset_drive/asset_fs.hh"
#include "fs/asset_drive/untar.hh"
#include <span>
#include <string_view>

#include "modules/blank.hh"
#include "modules/simple_vco.hh"

#ifdef SIMULATOR
#include "ext_plugin_builtin.hh"
#endif

namespace MetaModule
{

struct InternalPluginManager {
	FatFileIO &ramdisk;
	AssetFS &asset_fs;

#ifdef SIMULATOR
	std::list<rack::plugin::Plugin> internal_plugins;
#endif
	bool asset_fs_valid = true;

	InternalPluginManager(FatFileIO &ramdisk, AssetFS &asset_fs)
		: ramdisk{ramdisk}
		, asset_fs{asset_fs} {
		prepare_ramdisk();
		load_internal_assets();
		load_internal_plugins();
#ifdef SIMULATOR
		load_ext_builtin_plugins(internal_plugins);
#endif
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

		ramdisk.make_dir("/usr");
	}

	void load_internal_plugins() {

		// Load internal plugins

		// Native modules:
		register_module<Blank, BlankInfo>("InternalBuiltIns");
		register_module<DemoBuiltIns::SimpleVCO, DemoBuiltIns::SimpleVCOInfo>("InternalBuiltIns");

		parse_brand_jsons("built-ins/");
	}

	void parse_brand_jsons(std::string directory) {
		Plugin::Metadata metadata;
		std::vector<char> buffer;

		std::string filename = directory + "/plugin.json";
		auto sz = ramdisk.get_file_size(filename);
		if (sz > 0) {
			buffer.resize(sz);
			if (ramdisk.read_file(filename, buffer) > 0) {
				Plugin::parse_json(buffer, &metadata);
			}
		}

		filename = directory + "/plugin-mm.json";
		sz = ramdisk.get_file_size(filename);
		if (sz > 0) {
			buffer.resize(sz);
			if (ramdisk.read_file(filename, buffer) > 0) {
				Plugin::parse_mm_json(buffer, &metadata);
			}
		}

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
