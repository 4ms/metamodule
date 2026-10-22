#pragma once
#include "conf/plugin_file_conf.hh"
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "dynload/plugin_file_scan.hh"
#include "dynload/plugin_list_serial.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "patch_file/dir_list_serial.hh"
#include "patch_file/patch_storage.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

// The A35 can't read a PatchDirList, DirTree or PluginFileList built on this core (64-bit vs 32-bit
// layouts), so its FileStorageProxy asks for them serialized into a buffer instead
// (patch_dir_list/dir_entries/plugin_file_list null). PatchStorage fills in local copies as on MP1,
// and those get serialized here (see dir_list_serial.hh). The plugin file list is scanned straight
// into the buffer (see plugin_list_serial.hh).
//
// TODO: if we can free up some code space on the M4, then we could serialize in PatchStorage directly
// on mp1 and mp2
struct StorageMessages {
	using enum IntercoreStorageMessage::MessageType;

	StorageMessages(FatFileIO &usb_fileio, FatFileIO &sd_fileio, IntercoreStorageMessage &shared_message)
		: intercore_comm{shared_message}
		, usb_fileio{usb_fileio}
		, sd_fileio{sd_fileio}
		, patch_storage{sd_fileio, usb_fileio} {
	}

	void process() {
		patch_storage.refresh_patch_list();

		auto message = intercore_comm.get_new_message();
		if (message.message_type == None)
			return;

		auto response = handle_message(message);
		if (!response)
			response = not_ported_response(message);

		if (response) {
			// try to send response infinitely
			while (!intercore_comm.send_message(*response))
				;
		} else {
			pr_err("M33: storage message of type %u not handled\n", (unsigned)message.message_type);
		}
	}

	PatchStorage &get_patch_storage() {
		return patch_storage;
	}

private:
	mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Responder, IntercoreStorageMessage> intercore_comm;
	FatFileIO &usb_fileio;
	FatFileIO &sd_fileio;
	PatchStorage patch_storage;

	PatchDirList patch_dir_list; // what the A35 was last sent
	DirTree<FileEntry> dir_entries;

	std::optional<IntercoreStorageMessage> handle_message(IntercoreStorageMessage message) {
		// Intercept PatchList and DirEntries messages, and deserialize them
		// All other messages just pass through to PatchStorage

		if (message.message_type == RequestRefreshPatchList && !message.patch_dir_list) {
			message.patch_dir_list = &patch_dir_list;
			auto response = patch_storage.handle_message(message);

			if (response && response->message_type == PatchListChanged) {
				auto bytes = DirListSerial::serialize(patch_dir_list, message.buffer);
				if (bytes == 0) {
					pr_err("M33: patch list does not fit in the %u byte buffer\n", (unsigned)message.buffer.size());
					response->message_type = PatchListUnchanged;
				}
				response->bytes_read = bytes;
			}
			return response;
		}

		if (message.message_type == RequestDirEntries && !message.dir_entries) {
			message.dir_entries = &dir_entries;
			auto response = patch_storage.handle_message(message);

			if (response && response->message_type == DirEntriesSuccess) {
				auto bytes = DirListSerial::serialize(dir_entries, message.buffer);
				if (bytes == 0) {
					pr_err("M33: dir entries do not fit in the %u byte buffer\n", (unsigned)message.buffer.size());
					response->message_type = DirEntriesFailed;
				}
				response->bytes_read = bytes;
			}
			return response;
		}

		if (message.message_type == RequestPluginFileList && !message.plugin_file_list) {
			pr_dbg("M33: scanning volumes for plugin files (metamodule-plugins/*" PLUGIN_FILE_EXTENSION ")\n");

			PluginListSerial::Writer plugin_files{message.buffer};
			bool ok = scan_plugin_volumes(plugin_files);
			auto bytes = plugin_files.finish();
			if (bytes == 0) {
				pr_err("M33: plugin file list does not fit in the %u byte buffer\n", (unsigned)message.buffer.size());
				ok = false;
			}
			return IntercoreStorageMessage{.message_type = ok ? PluginFileListOK : PluginFileListFail,
										   .bytes_read = bytes};
		}

		return patch_storage.handle_message(message);
	}

	// Same as MP1's PluginFileFinder::find_plugin_files() (dynload/plugin_file_finder.hh), which can't
	// be shared without changing the MP1 M4 binary
	bool scan_plugin_volumes(PluginListSerial::Writer &plugin_files) {
		bool usb_ok = false;
		if (usb_fileio.is_mounted()) {
			usb_ok = scan_volume(usb_fileio, plugin_files, PluginDirName);
			usb_ok = scan_volume(usb_fileio, plugin_files, PluginUserDirName);
			usb_ok |= scan_volume(usb_fileio, plugin_files, "/");
		}

		bool sd_ok = false;
		if (sd_fileio.is_mounted()) {
			sd_ok = scan_volume(sd_fileio, plugin_files, PluginDirName);
			sd_ok = scan_volume(sd_fileio, plugin_files, PluginUserDirName);
			sd_ok |= scan_volume(sd_fileio, plugin_files, "/");
		}

		return usb_ok || sd_ok;
	}

	// Requests for handlers that aren't ported yet get a failure response. The A35 can't send another
	// request until this one is answered, so ignoring it would block all its other requests.
	static std::optional<IntercoreStorageMessage> not_ported_response(const IntercoreStorageMessage &message) {
		switch (message.message_type) {
			case RequestWifiIP: {
				// What MP1 answers when no WiFi expander responds
				IntercoreStorageMessage response{.message_type = WifiIPSuccess};
				response.wifi_ip_result = std::unexpected(WifiIPError::NO_MODULE_CONNECTED);
				return response;
			}
			case RequestFirmwareFile:
				return IntercoreStorageMessage{.message_type = FirmwareFileNotFound};
			case StartChecksumCompare:
				return IntercoreStorageMessage{.message_type = ChecksumFailed};
			case StartFlashing:
				return IntercoreStorageMessage{.message_type = FlashingFailed};
			case RequestReadFlash:
				return IntercoreStorageMessage{.message_type = ReadFlashFailed};
			default:
				return std::nullopt;
		}
	}
};

} // namespace MetaModule
