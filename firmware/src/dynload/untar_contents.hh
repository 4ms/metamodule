#pragma once
#include "console/pr_dbg.hh"
#include "dynload/plugin_file_list.hh"
#include "fat_file_io.hh"
#include "fs/asset_drive/untar.hh"
#include "metamodule-plugin-sdk/version.hh"
#include "plugin_file_load_states.hh"
#include <cstdint>
#include <span>
#include <string>
#include <vector>

namespace MetaModule
{

struct PluginLoadUntar {

	PluginLoadUntar(FatFileIO &ramdisk)
		: ramdisk{ramdisk} {
	}

	void clear() {
		so_buffer.clear();
		json_buffer.clear();
		mm_json_buffer.clear();
		files_copied_to_ramdisk.clear();
	}

	std::pair<PluginFileLoaderState, std::string> untar_contents(std::span<uint8_t> buffer, PluginFile &plugin_file) {
		auto plugin_tar = Tar::Archive({(char *)buffer.data(), buffer.size()});

		// plugin_tar.print_info();

		clear();

		std::string plugin_vers_filename;

		bool ramdisk_full = false;

		auto ramdisk_writer = [&](const std::string_view filename, std::span<const char> buffer) -> uint32_t {
			if (filename.ends_with(".so")) {
				if (so_buffer.size() == 0) {
					auto name = filename;
					if (auto slashpos = name.find_last_of("/"); slashpos != std::string::npos) {
						name = name.substr(slashpos + 1);
					}
					name.remove_suffix(3); //.so
					if (!name.starts_with(".")) {
						plugin_file.plugin_name = name;

						pr_trace("Found plugin binary file: %s, plugin name is %s\n",
								 filename.data(),
								 plugin_file.plugin_name.c_str());

						so_buffer.assign(buffer.begin(), buffer.end());
						return buffer.size();
					} else
						return 0;
				} else {
					pr_warn("More than one .so file found! Using just the first\n");
					return 0;
				}

			} else if (filename.ends_with("plugin.json")) {
				json_buffer.assign(buffer.begin(), buffer.end());
				return buffer.size();

			} else if (filename.ends_with("plugin-mm.json")) {
				mm_json_buffer.assign(buffer.begin(), buffer.end());
				return buffer.size();

			} else if (filename.contains("/SDK-")) {
				plugin_vers_filename = filename;
				return buffer.size();
			} else {
				if (!ramdisk.file_exists(filename)) {
					pr_trace("Copying file to ramdisk: %s\n", filename.data());
					auto bytes_written = ramdisk.write_file(filename, buffer);
					if (bytes_written > 0)
						files_copied_to_ramdisk.emplace_back(filename);
					else {
						auto [free, total] = ramdisk.get_free_total_space_kb();
						if (free * 1024U <= buffer.size_bytes()) {
							ramdisk_full = true;
							return Tar::Archive::FlagAbort;
						}
					}
					return bytes_written;
				} else {
					pr_trace("File exists, skipping: %s\n", filename.data());
					return 0;
				}
			}
		};

		bool all_ok = plugin_tar.extract_files(ramdisk_writer);

		if (ramdisk_full) {
			pr_warn("Ram disk is full.\n");

			for (auto const &fil : files_copied_to_ramdisk) {
				ramdisk.delete_file(fil);
			}
			clear();

			return {PluginFileLoaderState::RamDiskFull,
					"Error: No space in ram disk to load plugin. Free up space by removing other plugins."};
		}

		if (!all_ok) {
			pr_warn("Skipped loading some files in plugin dir (did not end in .png)\n");
			// status.error_message = "Warning: Failed to load some files";
		}

		if (so_buffer.size() == 0) {
			return {PluginFileLoaderState::InvalidPlugin,
					"Error: no plugin .so file found. Plugin is >20MB or corrupted."};
		}

		auto vers_pos = plugin_vers_filename.find_last_of("/SDK-");
		if (plugin_vers_filename.length() == 0 || vers_pos == std::string::npos) {
			return {PluginFileLoaderState::InvalidPlugin, "Warning: Plugin missing version file."};
		}

		auto plugin_vers = plugin_vers_filename.substr(vers_pos + 1);

		auto fw_version = sdk_version();

		if (fw_version.can_host_version(VersionUtil::Version(plugin_vers))) {
			return {PluginFileLoaderState::Success, ""};
		} else {
			std::string fw_vers = std::to_string(fw_version.major) + "." + std::to_string(fw_version.minor);
			auto plugin_name = std::string(plugin_file.plugin_name);
			auto err = "Plugin " + plugin_name + ": version is " + plugin_vers + ", but firmware version is " + fw_vers;
			return {PluginFileLoaderState::InvalidPlugin, err};
		}
	}

	FatFileIO &ramdisk;
	std::vector<uint8_t> so_buffer;
	std::vector<char> json_buffer;
	std::vector<char> mm_json_buffer;
	std::vector<std::string> files_copied_to_ramdisk;
};
} // namespace MetaModule
