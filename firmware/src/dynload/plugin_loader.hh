#pragma once
#include "dynload/dynloader.hh"
#include "dynload/json_parse.hh"
#include "dynload/loaded_plugin.hh"
#include "fat_file_io.hh"
#include "fs/asset_drive/untar.hh"
#include "memory/ram_buffer.hh" //path must be exactly this, or else simulator build picks wrong file
#include "metamodule-plugin-sdk/version.hh"
#include "patch_file/file_storage_proxy.hh"
#include "plugin/Plugin.hpp"
#include "util/monotonic_allocator.hh"
#include "util/version_tools.hh"
#include <cstdint>
#include <deque>
#include <string>

extern rack::plugin::Plugin *pluginInstance;

namespace MetaModule
{

class PluginFileLoader {
public:
	enum class State {
		NotInit,
		Error,
		Idle,
		RequestList,
		WaitingForList,
		GotList,
		PrepareForReadingPlugin,
		RequestReadPlugin,
		LoadingPlugin,
		UntarPlugin,
		ProcessingPlugin,
		Success
	};

	struct Status {
		State state{State::NotInit};
		std::string name;
		std::string error_message;
	};

	PluginFileLoader(FileStorageProxy &file_storage, FatFileIO &ramdisk)
		: file_storage{file_storage}
		, ramdisk{ramdisk}
		, allocator{get_ram_buffer()} {
	}

	void start() {
		allocator.reset();
		if (auto newmem = allocator.allocate(sizeof(PluginFileList))) {
			plugin_file_list = new (newmem) PluginFileList;
			status = {State::RequestList, "", ""};
		} else {
			pr_err("Could not allocate %zu bytes for plugin file list\n", sizeof(PluginFileList)); //4164B
			status = {State::Error, "", "Out of memory, could not make plugin file list"};
		}
	}

	void load_plugin(unsigned idx) {
		if (idx < plugin_files.size()) {
			status.state = State::PrepareForReadingPlugin;
			file_idx = idx;
		} else {
			pr_err("Cannot load plugin with idx %u, only have %zu plugins\n", idx, plugin_files.size());
		}
	}

	PluginFileList const *found_plugin_list() {
		status.state = State::Idle;
		return &plugin_files;
	}

	Status process(LoadedPluginList &loaded_plugins) {
		if (!plugin_file_list)
			status.state = State::NotInit;

		switch (status.state) {

			case State::RequestList:
				if (file_storage.request_plugin_file_list(plugin_file_list)) {
					status.state = State::WaitingForList;
				}
				break;

			case State::WaitingForList: {
				auto message = file_storage.get_message();

				if (message.message_type == IntercoreStorageMessage::PluginFileListFail) {
					status.state = State::Error;
					status.error_message = "No plugins found on USB or SD Card";
				}

				if (message.message_type == IntercoreStorageMessage::PluginFileListOK) {
					plugin_files = *plugin_file_list; //make local copy
					pr_trace("Found %d plugins\n", plugin_files.size());

					parse_versions();
					status.state = State::GotList;
					file_idx = 0;
				}

			} break;

				//////////////////

			case State::PrepareForReadingPlugin: {
				auto &plugin = plugin_files[file_idx];
				allocator.reset();
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
				auto &plugin = plugin_files[file_idx];
				if (file_storage.request_load_file(
						plugin.full_path, plugin.vol, {(char *)buffer.data(), buffer.size()}))
					status.state = State::LoadingPlugin;
			} break;

			case State::LoadingPlugin: {
				auto msg = file_storage.get_message();

				if (msg.message_type == FileStorageProxy::LoadFileFailed) {
					status.state = State::Error;
					status.error_message = "Failed to read from disk";

				} else if (msg.message_type == FileStorageProxy::LoadFileOK) {
					status.state = State::UntarPlugin;

				} else if (msg.message_type != FileStorageProxy::None) {
					pr_warn("Unknown response %d, trying again\n", msg.message_type);
					//try again
					status.state = State::RequestReadPlugin;
				}

			} break;

			case State::UntarPlugin: {
				auto &plugin_file = plugin_files[file_idx];
				std::string_view plugin_name = plugin_file.plugin_name;

				auto plugin_tar = Tar::Archive({(char *)buffer.data(), buffer.size()});
				// plugin_tar.print_info();

				so_buffer.clear();
				json_buffer.clear();
				files_copied_to_ramdisk.clear();

				std::string plugin_vers;

				auto ramdisk_writer = [&](const std::string_view filename, std::span<const char> buffer) -> uint32_t {
					if (filename.ends_with(".png")) {
						if (!ramdisk.file_exists(filename)) {
							pr_trace("Copying file to ramdisk: %s\n", filename.data());
							files_copied_to_ramdisk.emplace_back(filename);
							return ramdisk.write_file(filename, buffer);
						} else {
							pr_trace("File exists, skipping: %s\n", filename.data());
							return 0;
						}

					} else if (filename.ends_with(".so") && filename.starts_with(plugin_name)) {
						so_buffer.assign(buffer.begin(), buffer.end());
						pr_trace("Found plugin binary file: %s\n", filename.data());
						return buffer.size();

					} else if (filename.ends_with("plugin.json")) {
						json_buffer.assign(buffer.begin(), buffer.end());
						return buffer.size();

					} else if (filename.contains("/SDK-")) {
						//TODO: check version matches
						plugin_vers = filename;
						return buffer.size();

					} else {
						pr_trace("Skip file: %s\n", filename.data());
						return 0;
					}
				};

				bool all_ok = plugin_tar.extract_files(ramdisk_writer);
				if (!all_ok) {
					pr_warn("Skipped loading some files in plugin dir (did not end in .png)\n");
					// status.error_message = "Warning: Failed to load some files";
				}
				if (plugin_vers.length() == 0) {
					status.error_message = "Warning: Plugin missing version file.";
				}
				if (so_buffer.size() == 0) {
					status.error_message = "Error: no plugin binary found. Plugin is corrupted?";
				}

				auto fw_version = sdk_version();
				auto plugin_version = VersionUtil::parse_version(plugin_vers);
				if (fw_version.major != plugin_version.major || fw_version.minor < plugin_version.minor) {
					std::string fw_vers = std::to_string(fw_version.major) + "." + std::to_string(fw_version.minor);
					status.error_message = "Plugin version is " + plugin_vers + ", but firmware version is " + fw_vers;
					status.state = State::Error;
				} else
					status.state = State::ProcessingPlugin;

			} break;

			case State::ProcessingPlugin: {
				auto &plugin_file = plugin_files[file_idx];
				auto &plugin = loaded_plugins.emplace_back();
				plugin.fileinfo = plugin_file;

				auto plugin_json = Plugin::parse_json(json_buffer);
				plugin.rack_plugin.slug = plugin_json.slug.length() ? plugin_json.slug : plugin_file.plugin_name;
				plugin.rack_plugin.name = plugin_json.name.length() ? plugin_json.name : plugin_file.plugin_name;

				plugin.loaded_files = std::move(files_copied_to_ramdisk);

				if (load_plugin(plugin))
					status.state = State::Success;
				else {
					status.state = State::Error;
					// Cleanup files we copied to the ramdisk
					for (auto const &file : plugin.loaded_files) {
						ramdisk.delete_file(file);
					}
					loaded_plugins.pop_back();
				}

			} break;

			case State::NotInit:
				break;
			case State::GotList:
				status.state = State::Idle;
				break;
			case State::Idle:
				break;
			case State::Success:
				break;
			case State::Error:
				status.error_message.clear();
				break;
		}

		return status;
	}

	void parse_versions() {
		for (auto &plugin : plugin_files) {
			auto name = std::string_view{plugin.plugin_name};
			pr_dbg("Finding version for %s\n", name.data());

			if (auto v = name.find("-v"); v != std::string_view::npos) {
				// drop version from plugin name
				plugin.plugin_name = name.substr(0, v);

				std::string_view vers = name.substr(v + 2);
				auto version = VersionUtil::parse_version(vers);
				printf(
					"%s => %s => %u.%u.%u\n", name.data(), vers.data(), version.major, version.minor, version.revision);
			} else {
				pr_dbg("No version found\n");
				plugin.version = "1.0.0";
				plugin.sdk_major_version = 1;
				plugin.sdk_minor_version = 0;
			}
		}
	}

	bool load_plugin(LoadedPlugin &plugin) {
		using InitPluginFunc = void(rack::plugin::Plugin *);

		DynLoader dynloader{so_buffer, plugin.code};

		if (auto err_msg = dynloader.load(); err_msg != "") {
			status.error_message = err_msg;
			pr_err("Could not load plugin\n");
			return false;
		}

		auto plugin_sdk_version = dynloader.get_sdk_version();
		if (!plugin_sdk_version.has_value()) {
			pr_err("Plugin uses SDK < 0.15.0, or is not valid: not sdk_version() symbol found\n");
			status.error_message = "Plugin's SDK is older than 0.14, or is corrupted.";
			return false;
		}

		auto firmware_sdk_version = sdk_version();
		if (!firmware_sdk_version.can_host_version(*plugin_sdk_version)) {
			pr_err("Plugin and firmware version mismatch: %d.%d vs %d.%d\n",
				   plugin_sdk_version->major,
				   plugin_sdk_version->minor,
				   firmware_sdk_version.major,
				   firmware_sdk_version.minor);
			return false;
		}

		auto init = dynloader.find_init_func<InitPluginFunc>();
		if (!init) {
			status.error_message = "No init function found";
			pr_err("Could not init plugin\n");
			return false;
		}

		pluginInstance = &plugin.rack_plugin;
		//TODO: trap exceptions, restore state, and return
		init(&plugin.rack_plugin);

		pr_info("Plugin loaded!\n");
		status.error_message = "";
		return true;
	}

private:
	FileStorageProxy &file_storage;
	FatFileIO &ramdisk;

	Status status{};
	unsigned file_idx = 0;

	MonotonicAllocator allocator;
	std::span<uint8_t> buffer;
	std::vector<uint8_t> so_buffer;
	std::vector<char> json_buffer;
	std::vector<std::string> files_copied_to_ramdisk;

	// Dynamically allocated in non-cacheable RAM
	// Used to transfer from M4 to A7 core
	PluginFileList *plugin_file_list = nullptr;

	PluginFileList plugin_files;
};

} // namespace MetaModule
