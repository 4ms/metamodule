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
		Idle,
		GettingList,
		PrepareReadPlugin,
		RequestReadPlugin,
		LoadingPlugin,
		Success
	};

	struct Status {
		State state{State::Idle};
		std::string name;
		std::string error_message;
	};

	PluginFileLoader(FileStorageProxy &file_storage)
		: file_storage{file_storage}
		, allocator{get_ram_buffer()} {
	}

	void start(PluginFileList &plugin_file_list) {
		status = {State::Idle, "", ""};
		plugin_files = &plugin_file_list;
		allocator.reset();
	}

	Status process() {
		if (!plugin_files || plugin_files->size() == 0)
			return {State::NotInit};

		switch (status.state) {
			case State::Idle:
				if (file_storage.request_plugin_file_list(plugin_files))
					status.state = State::GettingList;
				break;

			case State::GettingList: {
				auto message = file_storage.get_message();

				if (message.message_type == IntercoreStorageMessage::PluginFileListFail) {
					status.state = State::Error;
					status.error_message = "Failed to get list of plugins";
				}

				if (message.message_type == IntercoreStorageMessage::PluginFileListOK) {
					status.state = State::PrepareReadPlugin;
					file_idx = 0;
				}

			} break;

			case State::PrepareReadPlugin: {
				auto plugin = (*plugin_files)[file_idx];
				buffer = {(char *)allocator.allocate(plugin.file_size), plugin.file_size};
				if (buffer.data()) {
					status.state = State::RequestReadPlugin;
				} else {
					status.state = State::Error;
					status.error_message =
						"Failed to allocate " + std::to_string(plugin.file_size) + " bytes for plugin";
				}
			} break;

			case State::RequestReadPlugin: {
				auto plugin = (*plugin_files)[file_idx];
				std::string path = plugin.dir_name + "/" + plugin.plugin_name;
				if (file_storage.request_load_file(path, plugin.vol, buffer))
					status.state = State::LoadingPlugin;
			} break;

			case State::LoadingPlugin: {
				auto plugin = (*plugin_files)[file_idx];
				pr_dbg("Loading plugin data from vol %d:%s/%s, from buffer %p ++%zu\n",
					   plugin.vol,
					   plugin.dir_name.c_str(),
					   plugin.plugin_name.c_str(),
					   buffer.data(),
					   buffer.size());

				DynLoader dynloader{buffer};
				dynloader.load();
				file_idx++;

				if (file_idx >= plugin_files->size()) {
					status.state = State::Success;
				} else
					status.state = State::PrepareReadPlugin;
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

	Status status;
	unsigned file_idx = 0;

	OneTimeArenaAllocator allocator;
	std::span<char> buffer;
	PluginFileList *plugin_files{};
};

} // namespace MetaModule
