#pragma once
#include "fs/fatfs/fat_file_io.hh"
#include "fs/fatfs/ramdisk_ops.hh"
#include "patch_file/file_storage_proxy.hh"
#include "plugin_loader.hh"
#include "user_settings/plugin_autoload_settings.hh"

namespace MetaModule
{

class PluginManager {

public:
	PluginManager(FileStorageProxy &file_storage_proxy, FatFileIO &ramdisk)
		: plugin_file_loader{file_storage_proxy, ramdisk}
		, ramdisk{ramdisk} {
	}

	void start_loading_plugin_list() {
		ramdisk.mount_disk();
		plugin_file_loader.start();
	}

	PluginFileList const *found_plugin_list() {
		return plugin_file_loader.found_plugin_list();
	}

	void load_plugin(unsigned idx) {
		plugin_file_loader.load_plugin(idx);
		ramdisk.debug_print_disk_info();
	}

	void unload_plugin(std::string_view name) {
		//TODO:
		// ramdisk.remove_recursive(plugin.fileinfo.plugin_name)
		loaded_plugin_list.remove_if([&](LoadedPlugin &plugin) { return (plugin.fileinfo.plugin_name == name); });
		ramdisk.debug_print_disk_info();
	}

	auto process_loading() {
		return plugin_file_loader.process(loaded_plugin_list);
	}

	LoadedPluginList const &loaded_plugins() {
		return loaded_plugin_list;
	}

	void autoload_plugins(PluginAutoloadSettings const &plugin_settings) {
		pr_info("Autoload: Starting...\n");

		if (plugin_settings.slug.size() == 0) {
			pr_info("Autoload: No plugins to load\n");
			return;
		}

		start_loading_plugin_list();
		auto result = process_loading();
		while (result.state != PluginFileLoader::State::GotList && result.state != PluginFileLoader::State::Error) {
			result = process_loading();
		}

		if (result.error_message.length()) {
			pr_err("Autoload: Error: %s\n", result.error_message.c_str());
			return;
		}

		const auto found_plugins = found_plugin_list();
		for (const auto &s : plugin_settings.slug) {
			pr_info("Autoload: Looking for plugin: %s\n", s.c_str());

			const auto match = std::find_if(found_plugins->begin(), found_plugins->end(), [s](PluginFile const &f) {
				return f.plugin_name == std::string_view(s);
			});

			if (match == found_plugins->end()) {
				pr_info("Autoload: Can't find plugin: %s\n", s.c_str());
				continue;
			}
			const auto idx = std::distance(found_plugins->begin(), match);
			load_plugin(idx);
			result = process_loading();
			while (result.state != PluginFileLoader::State::Success && result.state != PluginFileLoader::State::Error) {
				result = process_loading();
			}
			if (result.error_message.length()) {
				pr_err("Autoload: Error: %s\n", result.error_message.c_str());
				continue;
			}
			pr_info("Autoload: Loaded plugin: %s\n", s.c_str());
		}

		pr_info("Autoload: Complete\n");
	}

private:
	PluginFileLoader plugin_file_loader;
	LoadedPluginList loaded_plugin_list;
	FatFileIO &ramdisk;
};

} // namespace MetaModule
