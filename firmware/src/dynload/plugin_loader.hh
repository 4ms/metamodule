#pragma once
#include "dynload/dynloader.hh"
#include "memory/ram_buffer.hh" //path must be exactly this, or else simulator build picks wrong file
#include "patch_file/file_storage_proxy.hh"
#include "plugin/Plugin.hpp"
#include "util/monotonic_allocator.hh"
#include <cstdint>
#include <deque>
#include <string>

namespace MetaModule
{

class PluginFileLoader {
public:
	enum class State {
		NotInit,
		Error,
		RequestList,
		WaitingForList,
		PrepareForReadingPlugin,
		RequestReadPlugin,
		LoadingPlugin,
		ProcessingPlugin,
		Success
	};

	struct Status {
		State state{State::NotInit};
		std::string name;
		std::string error_message;
	};

	struct LoadedPlugin {
		PluginFile fileinfo;
		rack::plugin::Plugin rack_plugin;
		std::vector<uint8_t> code;
	};

	PluginFileLoader(FileStorageProxy &file_storage)
		: file_storage{file_storage}
		, allocator{get_ram_buffer()} {
	}

	void start() {
		plugins.clear();
		allocator.reset();
		if (auto newmem = allocator.allocate(sizeof(PluginFileList))) {
			plugin_files = new (newmem) PluginFileList;
			status = {State::RequestList, "", ""};
		} else {
			pr_err("Could not allocate %zu bytes for plugin file list\n", sizeof(PluginFileList));
			status = {State::Error, "", "Out of memory, could not make plugin file list"};
		}
	}

	Status process() {
		if (!plugin_files)
			status.state = State::NotInit;

		switch (status.state) {
			case State::RequestList:
				if (file_storage.request_plugin_file_list(plugin_files))
					status.state = State::WaitingForList;
				break;

			case State::WaitingForList: {
				auto message = file_storage.get_message();

				if (message.message_type == IntercoreStorageMessage::PluginFileListFail) {
					status.state = State::Error;
					status.error_message = "Failed to get list of plugins";
				}

				if (message.message_type == IntercoreStorageMessage::PluginFileListOK) {
					pr_trace("Found %d plugins\n", plugin_files->size());
					status.state = State::PrepareForReadingPlugin;
					file_idx = 0;
				}

			} break;

			case State::PrepareForReadingPlugin: {
				auto &plugin = (*plugin_files)[file_idx];
				buffer = {allocator.allocate(plugin.file_size), plugin.file_size};
				if (buffer.data()) {
					status.state = State::RequestReadPlugin;
				} else {
					status.state = State::Error;
					status.error_message =
						"Failed to allocate " + std::to_string(plugin.file_size) + " bytes for plugin";
				}
			} break;

			case State::RequestReadPlugin: {
				auto &plugin = (*plugin_files)[file_idx];
				std::string path = std::string(plugin.dir_name) + "/" + std::string(plugin.plugin_name);
				if (file_storage.request_load_file(path, plugin.vol, {(char *)buffer.data(), buffer.size()}))
					status.state = State::LoadingPlugin;
			} break;

			case State::LoadingPlugin: {
				IntercoreStorageMessage msg{FileStorageProxy::None};
				while (msg.message_type == FileStorageProxy::None) {
					msg = file_storage.get_message();
				}
				if (msg.message_type == FileStorageProxy::LoadFileToRamFailed) {
					status.state = State::Error;
					status.error_message = "Failed to read from disk";
				} else if (msg.message_type == FileStorageProxy::LoadFileToRamSuccess) {
					status.state = State::ProcessingPlugin;
				} else {
					pr_warn("Unknown response %d, trying again\n", msg.message_type);
					//try again
					status.state = State::RequestReadPlugin;
				}

			} break;

			case State::ProcessingPlugin: {
				auto &plugin_file = (*plugin_files)[file_idx];

				// Strip .so
				auto pluginname = std::string{std::string_view{plugin_file.plugin_name}};
				pr_trace("Plugin file name: %s\n", pluginname.c_str());

				if (pluginname.ends_with(".so")) {
					pluginname = pluginname.substr(0, pluginname.length() - 3);
					pr_trace("Stripping .so => %s\n", pluginname.c_str());
				}

				// TODO: get slug from a plugin.json file inside the plugin dir

				auto &plugin = plugins.emplace_back();
				plugin.fileinfo = plugin_file;
				plugin.rack_plugin.slug = pluginname;

				pr_dbg("Loading plugin `%s` from vol %d: `%s/%s`, from buffer %p ++%zu\n",
					   plugin.rack_plugin.slug.c_str(),
					   plugin.fileinfo.vol,
					   plugin.fileinfo.dir_name.c_str(),
					   plugin.fileinfo.plugin_name.c_str(),
					   buffer.data(),
					   buffer.size());

				load_plugin_assets(plugin);
				load_plugin(plugin);

				file_idx++;

				if (file_idx >= plugin_files->size()) {
					status.state = State::Success;
				} else
					status.state = State::PrepareForReadingPlugin;
			} break;

			case State::NotInit:
				break;
			case State::Success:
				break;
			case State::Error:
				status.error_message.clear();
				break;
		}

		return status;
	}

	bool load_plugin(LoadedPlugin &plugin) {
		using InitPluginFunc = void(rack::plugin::Plugin *);

		DynLoader dynloader{buffer, plugin.code};

		if (!dynloader.load()) {
			pr_err("Could not load plugin\n");
			return false;
		}

		auto init = dynloader.find_init_func<InitPluginFunc>();
		if (!init) {
			pr_err("Could not init plugin\n");
			return false;
		}

		//TODO: trap exceptions, restore state, and return
		init(&plugin.rack_plugin);

		pr_info("Plugin loaded!\n");
		return true;
	}

	bool load_plugin_assets(LoadedPlugin &plugin) {
		pr_trace("Loading assets from vol %d: %s\n", plugin.fileinfo.vol, plugin.fileinfo.dir_name.c_str());

		file_storage.request_copy_dir_to_ramdisk(plugin.fileinfo.vol, plugin.fileinfo.dir_name);

		IntercoreStorageMessage msg{.message_type = FileStorageProxy::None};
		while (msg.message_type == FileStorageProxy::None) {
			msg = file_storage.get_message();
		}

		if (msg.message_type == FileStorageProxy::CopyPluginAssetsOK) {
			pr_info("Plugin assets loaded!\n");
			return true;
		} else if (msg.message_type == FileStorageProxy::CopyPluginAssetsFail) {
			pr_err("Failed to copy system plugin assets to ramdisk\n");
		} else {
			pr_err("Unknown response to request to copy assets to ramdisk: %u\n", msg.message_type);
		}

		return false;
	}

private:
	FileStorageProxy &file_storage;

	Status status{};
	unsigned file_idx = 0;

	MonotonicAllocator allocator;
	std::span<uint8_t> buffer;

	// Dynamically generated in non-cacheable RAM
	PluginFileList *plugin_files = nullptr;

	// TODO: plugins should live somewhere all UI can access, perhaps in main and passed by ref to PageContext
	std::deque<LoadedPlugin> plugins;
};

} // namespace MetaModule
