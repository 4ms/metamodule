#pragma once
#include "VCV_adaptor/plugin/Plugin.hpp"
#include "dynload/dynloader.hh"
#include "fw_update/ram_buffer.hh" //path must be exactly this, or else simulator build picks wrong file
#include "patch_file/file_storage_proxy.hh"
#include <cstdint>
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
		Success
	};

	struct Status {
		State state{State::NotInit};
		std::string name;
		std::string error_message;
	};

	struct LoadedPlugin {
		std::string name;
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
				auto &plugin_file = (*plugin_files)[file_idx];

				// Strip .so
				auto pluginname = std::string{std::string_view{plugin_file.plugin_name}};
				pr_trace("Plugin file name: %s\n", pluginname.c_str());

				if (pluginname.ends_with(".so")) {
					pluginname = pluginname.substr(0, pluginname.length() - 3);
					pr_trace("Stripping .so => %s\n", pluginname.c_str());
				}

				// TODO: get slug from a plugin.json file inside the plugin dir
				auto plugin = plugins.emplace_back();
				plugin.name = pluginname;
				plugin.rack_plugin.slug = pluginname;

				pr_dbg("Loading plugin %s from vol %d:%s / %s, from buffer %p ++%zu\n",
					   plugin.name.c_str(),
					   plugin_file.vol,
					   plugin_file.dir_name.c_str(),
					   plugin_file.plugin_name.c_str(),
					   buffer.data(),
					   buffer.size());

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

	void load_plugin(LoadedPlugin &plugin) {
		using InitPluginFunc = void(rack::plugin::Plugin *);

		// ModuleFactory::setCurrentBrand(plugin.name);

		DynLoader dynloader{buffer, plugin.code};

		if (!dynloader.load()) {
			pr_err("Could not load plugin\n");
			return;
		}

		auto init = dynloader.find_init_func<InitPluginFunc>();
		if (!init) {
			pr_err("Could not init plugin\n");
			return;
		}

		init(&plugin.rack_plugin);

		// ModuleFactory::setCurrentBrand("");

		// now load the /res directory to...?
		pr_info("Plugin loaded!\n");
	}

private:
	FileStorageProxy &file_storage;

	Status status{};
	unsigned file_idx = 0;

	OneTimeArenaAllocator allocator;
	std::span<uint8_t> buffer;

	// Dynamically generated in non-cacheable RAM
	PluginFileList *plugin_files = nullptr;

	// TODO: plugins should live somewhere all UI can access, perhaps in main and passed by ref to PageContext
	std::vector<LoadedPlugin> plugins;
};

} // namespace MetaModule
