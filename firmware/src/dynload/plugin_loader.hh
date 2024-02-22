#pragma once
#include "fw_update/ram_buffer.hh" //path must be exactly this, or else simulator build picks wrong file
#include "patch_file/file_storage_proxy.hh"
#include <cstdint>
#include <string>

namespace MetaModule
{

class PluginFileLoader {
public:
	enum class State { NotInit, Error, Idle, GettingList, LoadingPlugins, Success };

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
					status.state = State::LoadingPlugins;
				}

			} break;

			case State::LoadingPlugins: {
				//TODO: parse one at a time and report success/error
				for (auto &file : *plugin_files) {
					pr_dbg("Loading plugin from vol %d:metamodule-plugins/%s/%s\n",
						   file.vol,
						   file.dir_name.c_str(),
						   file.plugin_name.c_str());
					//TODO: use DynLoader
				}
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

	OneTimeArenaAllocator allocator;
	PluginFileList *plugin_files{};
};

} // namespace MetaModule
