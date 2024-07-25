#pragma once
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "dynload/plugin_file_scan.hh"
#include "fat_file_io.hh"
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
		pr_dbg("M4: scanning volumes for plugin files (plugin/**/*.so)\n");

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

	FatFileIO &sdcard_;
	FatFileIO &usbdrive_;
};

} // namespace MetaModule
