#pragma once
#include "fw_update/ram_buffer.hh" //path must be exactly this, or else simulator build picks wrong file
#include "patch_file/file_storage_proxy.hh"
#include <cstdint>
#include <string>

namespace MetaModule
{

class PluginFileLoader {
public:
	enum class State { NotInit, Error, Idle, GettingList, ReadingPlugin, LoadingPlugin, Success };

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
	}

	Status process() {
		if (!plugin_files)
			return {State::NotInit};

		switch (status.state) {
			case State::Idle:
				if (file_storage.request_plugin_file_list(plugin_files))
					status.state = State::GettingList;
				else {
					status.state = State::Error;
					status.error_message = "Failed to request plugin list";
				}
				status.state = State::GettingList;
				break;

			case State::GettingList: {
				auto message = file_storage.get_message();

				if (message.message_type == IntercoreStorageMessage::PluginFileListFail) {
					status.state = State::Error;
					status.error_message = "Failed to get list of plugins";
				}

				if (message.message_type == IntercoreStorageMessage::PluginFileListOK) {
					status.state = State::ReadingPlugin;
					file_idx = 0;
				}

			} break;

			case State::ReadingPlugin: {
				if (file_idx >= plugin_files->size()) {
					status.state = State::Success;
					break;
				}
				auto plugin = (*plugin_files)[file_idx];
				std::string path = "metamodule-plugins/" + plugin.dir_name + "/" + plugin.plugin_name;
				auto buffer = allocator.allocate(plugin.file_size);
				if (buffer) {
					auto ok = file_storage.request_load_file(path, plugin.vol, {(char *)buffer, plugin.file_size});
					if (ok)
						status.state = State::LoadingPlugin;
				} else {
					status.state = State::Error;
					status.error_message =
						"Failed to allocate " + std::to_string(plugin.file_size) + " bytes for plugin";
				}
			} break;

			case State::LoadingPlugin: {
				auto plugin = (*plugin_files)[file_idx];
				pr_dbg("Loading plugin from vol %d:metamodule-plugins/%s/%s\n",
					   plugin.vol,
					   plugin.dir_name.c_str(),
					   plugin.plugin_name.c_str());
				//TODO: use DynLoader
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
	PluginFileList *plugin_files{};
};

} // namespace MetaModule
