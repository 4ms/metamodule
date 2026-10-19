#pragma once
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "patch_file/dir_list_serial.hh"
#include "patch_file/patch_storage.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

// Answers the A35's FileStorageProxy requests. MP2's version of MP1's FilesystemMessages
// (fs/fs_messages.hh), with only PatchStorage so far: no firmware update, plugin file list,
// calibration, or WiFi handlers yet.
//
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

		if (auto response = handle_message(message); response) {
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
};

} // namespace MetaModule
