#pragma once
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "patch_file/dir_list_serial.hh"
#include "patch_file/patch_storage.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

// The A35 can't read a PatchDirList or DirTree built on this core (64-bit vs 32-bit layouts), so its
// FileStorageProxy asks for them serialized into a buffer instead (patch_dir_list/dir_entries null).
// PatchStorage fills in local copies as on MP1, and those get serialized here (see dir_list_serial.hh).
//
// TODO: if we can free up some code space on the M4, then we could serialize in PatchStorage directly
// on mp1 and mp2
struct StorageMessages {
	using enum IntercoreStorageMessage::MessageType;

	StorageMessages(FatFileIO &usb_fileio, FatFileIO &sd_fileio, IntercoreStorageMessage &shared_message)
		: intercore_comm{shared_message}
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

		return patch_storage.handle_message(message);
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
			case RequestPluginFileList:
				return IntercoreStorageMessage{.message_type = PluginFileListFail};
			default:
				return std::nullopt;
		}
	}
};

} // namespace MetaModule
