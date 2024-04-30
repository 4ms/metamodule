#pragma once
#include "conf/ramdisk_conf.hh"
#include "fs/asset_drive/asset_fs.hh"
#include "fs/asset_drive/untar.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "fs/fatfs/ramdisk_ops.hh"
#include "fs/fileio_t.hh"
#include "patch_file/file_storage_proxy.hh"
#include "plugin/Plugin.hpp"
#include "plugin_loader.hh"
#include <list>

namespace MetaModule
{

class PluginManager {
	FatFileIO &ramdisk;
	PluginFileLoader plugin_file_loader;
	enum class State { Ready, IsLoadingList, GotList, IsLoadingPlugin, DoneLoadingPlugin } state = State::Ready;

public:
	PluginManager(FileStorageProxy &file_storage_proxy, FatFileIO &ramdisk)
		: ramdisk{ramdisk}
		, plugin_file_loader{file_storage_proxy} {
	}

	void start_loading_plugin_list() {
		state = State::IsLoadingList;

		ramdisk.mount_disk();
		plugin_file_loader.start();
	}

	PluginFileList const *found_plugin_list() {
		return plugin_file_loader.found_plugin_list();
	}

	auto process_loading() {
		auto result = plugin_file_loader.process();

		if (result.state == PluginFileLoader::State::Success) {
			if (state == State::IsLoadingList) {
				state = State::GotList;
				//report back
			}

			if (state == State::IsLoadingPlugin) {
				state = State::DoneLoadingPlugin;
				// ramdisk.print_dir("/", 4);
			}
		}
		return result;
	}
};

} // namespace MetaModule
