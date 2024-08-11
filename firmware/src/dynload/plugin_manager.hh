#pragma once
#include "fs/fatfs/fat_file_io.hh"
#include "fs/fatfs/ramdisk_ops.hh"
#include "patch_file/file_storage_proxy.hh"
#include "plugin_loader.hh"

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
	}

	void unload_plugin(std::string_view name) {
		//TODO:
		// ramdisk.remove_recursive(plugin.fileinfo.plugin_name)
		loaded_plugin_list.remove_if([&](LoadedPlugin &plugin) { return (plugin.fileinfo.plugin_name == name); });
	}

	auto process_loading() {
		return plugin_file_loader.process(loaded_plugin_list);
	}

	LoadedPluginList const &loaded_plugins() {
		return loaded_plugin_list;
	}

private:
	PluginFileLoader plugin_file_loader;
	LoadedPluginList loaded_plugin_list;
	FatFileIO &ramdisk;
};

} // namespace MetaModule
