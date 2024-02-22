#pragma once
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "fat_file_io.hh"
#include "fs/file_ram_loader.hh"
#include "fs/fileio_t.hh"
#include "fw_update/update_path.hh"
#include "util/poll_change.hh"
#include "util/static_string.hh"
#include <cstring>
#include <optional>

namespace MetaModule
{

struct PluginFileFinder {
	using enum IntercoreStorageMessage::MessageType;

	PluginFileFinder(FatFileIO &sdcard_fileio, FatFileIO &usb_fileio)
		: sdcard_{sdcard_fileio}
		, usbdrive_{usb_fileio} {
	}

	std::optional<IntercoreStorageMessage> handle_message(const IntercoreStorageMessage &message) {

		if (message.message_type == RequestPluginFileList) {
			return find_plugin_files(message);
		}

		return std::nullopt;
	}

private:
	IntercoreStorageMessage find_plugin_files(const IntercoreStorageMessage &message) {
		pr_trace("M4: scanning volumes for plugin files (plugin/**/*.so)\n");

		message.plugin_file_list->clear();

		bool usb_ok = false;
		if (usbdrive_.is_mounted()) {
			usb_ok = scan_volume(usbdrive_, *message.plugin_file_list);
		}

		bool sd_ok = false;
		if (sdcard_.is_mounted()) {
			sd_ok = scan_volume(sdcard_, *message.plugin_file_list);
		}

		if (usb_ok || sd_ok)
			return {.message_type = PluginFileListOK};
		else
			return {.message_type = PluginFileListFail};
	}

	bool scan_volume(FileIoC auto &fileio, PluginFileList &plugin_files) {
		pr_dbg("Scanning metamodule-plugins dir on volume %s\n", fileio.volname());

		bool ok = fileio.foreach_dir_entry(
			"metamodule-plugins",
			[&](std::string_view entryname, uint32_t timestamp, uint32_t filesize, DirEntryKind kind) {
				std::string full_path = "metamodule-plugins/" + std::string(entryname);

				// Scan each dir in metamodule-plugins/
				if (kind == DirEntryKind::Dir) {
					if (entryname.starts_with("."))
						return;
					if (!scan_directory(fileio, plugin_files, full_path))
						pr_err("Failed to scan dir\n");
				}
			});

		if (!ok) {
			pr_err("Failed to read dir on %.32s\n", fileio.volname().data());
		}

		return ok;
	}

	bool scan_directory(FileIoC auto &fileio, PluginFileList &plugin_files, std::string const &path) {
		pr_trace("Scan dir: %s\n", path.c_str());
		bool ok = fileio.foreach_dir_entry(
			path, [&](std::string_view entryname, uint32_t timestamp, uint32_t filesize, DirEntryKind kind) {
				// Add files:
				if (kind == DirEntryKind::File) {
					if (entryname.ends_with(".so")) {
						pr_trace("Found plugin file %.*s/%.*s\n", path.c_str(), entryname.size(), entryname.data());
						plugin_files.push_back(PluginFile{fileio.vol_id(), path, std::string(entryname), filesize});
					}
				}
			});
		return ok;
	}

	FatFileIO &sdcard_;
	FatFileIO &usbdrive_;
};

} // namespace MetaModule
