#pragma once
#include "dynload/json_parse.hh"
#include "dynload/register_metadata.hh"
#include "ext_plugin_builtin.hh"
#include "fat_file_io.hh"
#include "fs/asset_drive/asset_fs.hh"
#include "fs/asset_drive/untar.hh"
#include "gui/fonts/fonts_init.hh"
#include "load_internal_plugins.hh"
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
		load_internal_plugins(internal_plugins);
		// Ext-builtin brands must register their modules before the manifests are
		// parsed: parse_plugin_jsons() applies metadata (display names, element
		// groups) to modules that are already in the ModuleFactory.
		load_ext_builtin_plugins(internal_plugins);
		parse_plugin_jsons();
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

	void parse_plugin_jsons() {
		parse_jsons("4ms");
		for (auto &p : internal_plugins) {
			parse_jsons(p.getBrand());
		}
	}

	void parse_jsons(std::string const &plugin_name) {
		Plugin::Metadata metadata;
		std::vector<char> buffer;

		std::string filename = plugin_name + "/plugin.json";
		auto sz = ramdisk.get_file_size(filename);
		if (sz > 0) {
			buffer.resize(sz);
			if (ramdisk.read_file(filename, buffer) > 0) {
				Plugin::parse_json(buffer, &metadata);
			}
		}

		filename = plugin_name + "/plugin-mm.json";
		sz = ramdisk.get_file_size(filename);
		if (sz > 0) {
			buffer.resize(sz);
			if (ramdisk.read_file(filename, buffer) > 0) {
				Plugin::parse_mm_json(buffer, &metadata);
			}
		}

		Plugin::register_metadata(metadata);
	}
};
} // namespace MetaModule
