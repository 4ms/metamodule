#pragma once
#include "dynload/dynloader.hh"
#include "dynload/json_parse.hh"
#include "dynload/loaded_plugin.hh"
#include "dynload/plugin_file_load_states.hh"
#include "dynload/version_sort.hh"
#include "fat_file_io.hh"
#include "memory/ram_buffer.hh" //path must be exactly this, or else simulator build picks wrong file
#include "metamodule-plugin-sdk/version.hh"
#include "patch_file/file_storage_proxy.hh"
#include "plugin/Plugin.hpp"
#include "system/abort_rescue.hh"
#include "untar_contents.hh"
#include "util/monotonic_allocator.hh"
#include "util/version_tools.hh"
#include <algorithm>
#include <cstdint>
#include <string>

extern rack::plugin::Plugin *pluginInstance;

namespace MetaModule
{

class PluginFileLoader {
public:
	using State = PluginFileLoaderState;

	struct Status {
		State state{State::NotInit};
		std::string name;
		std::string error_message;
	};

	PluginFileLoader(FileStorageProxy &file_storage, FatFileIO &ramdisk)
		: file_storage{file_storage}
		, ramdisk{ramdisk}
		, allocator{get_ram_buffer()}
		, contents{ramdisk} {
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

	StaticString<255> plugin_name(unsigned idx) {
		if (idx < plugin_files.size())
			return plugin_files[idx].plugin_name;
		else
			return "";
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

					std::ranges::sort(plugin_files, alpha_then_newest_version);

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
					status.state = State::InvalidPlugin;
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
				auto [result, err] = contents.untar_contents(buffer, plugin_file);

				if (result == PluginFileLoaderState::RamDiskFull) {
					status.state = State::RamDiskFull;
					status.error_message = err;

				} else if (result == PluginFileLoaderState::InvalidPlugin) {
					status.state = State::InvalidPlugin;
					status.error_message = err;

				} else {
					status.state = State::ProcessingPlugin;
				}

			} break;

			case State::ProcessingPlugin: {
				auto num_loaded_before = loaded_plugins.size();
				bool plugin_inited = false;
				try {
					auto &plugin_file = plugin_files[file_idx];
					auto &plugin = loaded_plugins.emplace_back();
					plugin.fileinfo = plugin_file;

					pr_info("Put plugin in loaded list: %s\n", plugin.fileinfo.plugin_name.c_str());

					// set slug and display name
					auto metadata = get_plugin_metadata();
					std::string fallback_name = plugin_file.plugin_name;
					if (metadata.brand_slug.length() == 0)
						metadata.brand_slug = fallback_name;
					plugin.rack_plugin.slug = metadata.brand_slug;
					plugin.rack_plugin.name = metadata.display_name.length() ? metadata.display_name : fallback_name;

					plugin.loaded_files = std::move(contents.files_copied_to_ramdisk);

					if (load_plugin(plugin)) {
						plugin_inited = true;

						if (metadata.display_name.length())
							ModuleFactory::setBrandDisplayName(metadata.brand_slug, metadata.display_name);

						for (auto const &alias : metadata.brand_aliases)
							ModuleFactory::registerBrandAlias(metadata.brand_slug, alias);

						for (auto const &alias : metadata.module_display_names) {
							if (alias.display_name.length() && alias.slug.length()) {
								ModuleFactory::setModuleDisplayName(metadata.brand_slug + ":" + alias.slug,
																	alias.display_name);
							}
						}

						for (auto const &m : metadata.module_extras) {
							if (!m.slug.empty()) {
								if (!m.description.empty())
									ModuleFactory::setModuleDescription(metadata.brand_slug + ":" + m.slug,
																		m.description);
								if (m.tags.size() > 0)
									ModuleFactory::setModuleTags(metadata.brand_slug + ":" + m.slug, m.tags);
							}
						}

						status.state = State::Success;
					} else {
						status.state = State::InvalidPlugin;
						// Cleanup files we copied to the ramdisk
						for (auto const &file : plugin.loaded_files) {
							ramdisk.delete_file(file);
						}
						loaded_plugins.pop_back();
					}
				} catch (std::bad_alloc &) {
					if (plugin_inited) {
						// The plugin's init() already ran and its modules are
						// registered: it is loaded and usable, only some
						// display metadata may be missing. Rolling back a
						// registered plugin is not safe, so keep it.
						pr_err("Out of memory registering plugin metadata (plugin still loaded)\n");
						status.state = State::Success;
					} else {
						pr_err("Out of memory loading plugin\n");
						status.state = State::InvalidPlugin;
						status.error_message = "Out of memory loading plugin";
						// The ramdisk file list may or may not have been moved
						// into the plugin entry yet: clean up from both places
						for (auto const &file : contents.files_copied_to_ramdisk) {
							ramdisk.delete_file(file);
						}
						while (loaded_plugins.size() > num_loaded_before) {
							for (auto const &file : loaded_plugins.back().loaded_files) {
								ramdisk.delete_file(file);
							}
							loaded_plugins.pop_back();
						}
						pluginInstance = nullptr;
					}
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
				status.state = State::Idle;
				break;
			case State::Error:
			case State::InvalidPlugin:
			case State::RamDiskFull:
				status.error_message.clear();
				break;
		}

		return status;
	}

	Plugin::Metadata get_plugin_metadata() {
		Plugin::Metadata metadata;

		if (contents.json_buffer.size()) {
			Plugin::parse_json(contents.json_buffer, &metadata);
		}

		if (contents.mm_json_buffer.size()) {
			Plugin::parse_mm_json(contents.mm_json_buffer, &metadata);
		}

		// Report warnings/errors:
		if (!metadata.brand_slug.length()) {
			pr_warn("Warning: plugin slug not found in plugin.json or plugin-mm.json\n");
		}

		if (!metadata.display_name.length()) {
			pr_warn("Warning: plugin display name not found in plugin.json or plugin-mm.json\n");
		}

		return metadata;
	}

	bool is_idle() {
		return status.state == State::Idle || status.state == State::NotInit || status.state == State::Success ||
			   status.state == State::Error || status.state == State::InvalidPlugin ||
			   status.state == State::RamDiskFull;
	}

	// Splits plugin names at the first "-v"
	void parse_versions() {
		for (auto &plugin : plugin_files) {
			plugin.version_in_filename = "";

			const auto name = std::string{plugin.plugin_name};

			// Make sure the char after the -v is a digit
			auto v = name.find("-v");
			while (v != std::string_view::npos) {
				if (isdigit(name[v + 2])) {
					plugin.plugin_name.copy(name.substr(0, v));
					plugin.version_in_filename.copy(name.substr(v + 2));
					break;
				}
				v = name.find("-v", v + 2);
			}
		}
	}

	bool load_plugin(LoadedPlugin &plugin) {
		using InitPluginFunc = void(rack::plugin::Plugin *);

		DynLoader dynloader{contents.so_buffer, plugin.code};

		if (auto err_msg = dynloader.load(); err_msg != "") {
			status.error_message = err_msg;
			pr_err("Could not load plugin\n");
			return false;
		}

		// Check the sdk version by calling sdk_version() in the plugin
		// This function will return the SDK version used to build the plugin.
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

		// Snapshot registered brands so a crashed init can be backed out
		auto brands_before = ModuleFactory::getAllBrands();

		AbortRescue rescue;
		if (setjmp(rescue.jb) != 0) {
			// The plugin died during init() (uncaught exception -> its
			// terminate -> imported abort() -> mm_plugin_abort longjmps
			// here; details were printed by the plugin's terminate handler).
			// Back out everything it registered. Its Model objects live in
			// the plugin arena: do not run plugin code to destroy them --
			// drop the references and leak them (bounded, reclaimed on
			// reboot).
			// Copy names first: unregistering invalidates registry views
			std::vector<std::string> new_brands;
			for (auto brand : ModuleFactory::getAllBrands()) {
				if (std::ranges::find(brands_before, brand) == brands_before.end())
					new_brands.emplace_back(brand);
			}
			for (auto const &brand : new_brands) {
				pr_err("Unregistering brand '%s' from crashed plugin\n", brand.c_str());
				ModuleFactory::unregisterBrand(brand);
			}
			plugin.rack_plugin.models.clear();
			plugin.rack_plugin = {};
			plugin.code = {};
			pluginInstance = nullptr;
			status.error_message = "Plugin crashed while initializing";
			return false;
		}
		rescue.arm();

		pluginInstance = &plugin.rack_plugin;
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

	PluginLoadUntar contents;

	// Dynamically allocated in non-cacheable RAM
	// Used to transfer from M4 to A7 core
	PluginFileList *plugin_file_list = nullptr;

	PluginFileList plugin_files;
};

} // namespace MetaModule
