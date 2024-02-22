#pragma once
#include "fw_update/ram_buffer.hh" //path must be exactly this, or else simulator build picks wrong file
#include "patch_file/file_storage_proxy.hh"
#include <cstdint>
#include <string>

#include "dynload/dynloader.hh"

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

	PluginFileLoader(FileStorageProxy &file_storage)
		: file_storage{file_storage}
		, allocator{get_ram_buffer()} {
	}

	void start() {
		plugin_code.clear();
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
				auto &plugin = (*plugin_files)[file_idx];
				auto code = plugin_code.emplace_back(plugin.plugin_name.c_str());

				pr_dbg("Loading plugin data from vol %d:%s/%s, from buffer %p ++%zu\n",
					   plugin.vol,
					   plugin.dir_name.c_str(),
					   plugin.plugin_name.c_str(),
					   buffer.data(),
					   buffer.size());

				DynLoader dynloader{buffer, code.code};
				auto ok = dynloader.load();
				if (ok)
					pr_info("Plugin loaded!\n");
				else
					pr_err("Could not load plugin\n");

				file_idx++;

				if (file_idx >= plugin_files->size()) {
					status.state = State::Success;
				} else
					status.state = State::PrepareForReadingPlugin;
			} break;

			case State::NotInit:
			case State::Error:
			case State::Success:
				break;
		}

		return status;
	}

private:
	FileStorageProxy &file_storage;

	Status status{};
	unsigned file_idx = 0;

	OneTimeArenaAllocator allocator;
	std::span<uint8_t> buffer;

	// Dynamically generated in non-cacheable RAM
	PluginFileList *plugin_files = nullptr;

	struct LoadedPlugin {
		std::string name;
		std::vector<uint8_t> code;
	};
	std::vector<LoadedPlugin> plugin_code;
};

} // namespace MetaModule
