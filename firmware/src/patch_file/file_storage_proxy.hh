#pragma once
#include "core_intercom/intercore_message.hh"
#include "patch_file/dir_list_serial.hh"
#include "patch_file/file_storage_comm.hh"
#include "patch_file/patch_location.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

class FileStorageProxy {

public:
	using enum IntercoreStorageMessage::MessageType;

	//TODO: use a general-purpose buffer instead of raw_patch_data and patch_dir_list

	// list_buffer: if given, the patch list and dir entries are sent serialized into this buffer
	// (which must be in memory both cores can access), and unpacked here by get_message(), instead
	// of the other core filling in our PatchDirList/DirTree directly. Needed when the cores don't
	// share a memory layout (MP2). See dir_list_serial.hh.
	FileStorageProxy(std::span<char> raw_patch_data,
					 FileStorageComm &comm,
					 PatchDirList &patch_dir_list,
					 std::span<char> list_buffer = {})
		: comm_{comm}
		, patch_dir_list_{patch_dir_list}
		, raw_patch_data_{raw_patch_data}
		, list_buffer_{list_buffer} {
	}

	IntercoreStorageMessage get_message() {
		auto message = comm_.get_new_message();

		if (!list_buffer_.empty()) {
			if (message.message_type == PatchListChanged) {
				if (!DirListSerial::deserialize(list_buffer_.first(message.bytes_read), patch_dir_list_))
					pr_err("Error: received a corrupt patch list\n");

			} else if (message.message_type == DirEntriesSuccess && pending_dir_tree_) {
				if (!DirListSerial::deserialize(list_buffer_.first(message.bytes_read), *pending_dir_tree_)) {
					pr_err("Error: received corrupt dir entries\n");
					message.message_type = DirEntriesFailed;
				}
			}

			if (message.message_type == DirEntriesSuccess || message.message_type == DirEntriesFailed)
				pending_dir_tree_ = nullptr;
		}

		return message;
	}

	// TODO: consider passing raw_patch_data_ as a param here,
	// so the caller can read it on their own (but must ensure it's in shared/non-cache ram)
	[[nodiscard]] bool request_load_patch(PatchLocation patch_loc) {
		IntercoreStorageMessage message{
			.message_type = RequestLoadFile,
			.vol_id = patch_loc.vol,
			.buffer = raw_patch_data_,
			.filename = patch_loc.filename,
		};
		if (!comm_.send_message(message))
			return false;

		return true;
	}

	//
	// patchlist: list of all patches found on all volumes
	//
	// TODO: consider passing patch_dir_list_ as a param here,
	// so the caller can read it on their own (but must ensure it's in shared/non-cache ram)
	[[nodiscard]] bool request_patchlist() {
		IntercoreStorageMessage message{
			.message_type = RequestRefreshPatchList,
			.patch_dir_list = &patch_dir_list_, // this is where we want M4 to copy the patch_dir_list
		};

		if (!list_buffer_.empty()) {
			message.patch_dir_list = nullptr;
			message.buffer = list_buffer_;
		}

		return comm_.send_message(message);
	}

	PatchDirList &get_patch_list() {
		return patch_dir_list_;
	}

	std::span<char> get_patch_data() {
		return raw_patch_data_;
	}

	std::span<char> get_patch_data(uint32_t bytes) {
		return raw_patch_data_.subspan(0, bytes);
	}

	// Scan all mounted volumes for firmware update files
	[[nodiscard]] bool request_find_firmware_file() {
		IntercoreStorageMessage message{.message_type = RequestFirmwareFile};
		return comm_.send_message(message);
	}

	// Load a file from filesystem to RAM
	[[nodiscard]] bool request_load_file(std::string_view filename, Volume vol, std::span<char> buffer) {
		IntercoreStorageMessage message{
			.message_type = RequestLoadFile,
			.vol_id = vol,
			.buffer = buffer,
			.filename = filename,
		};
		return comm_.send_message(message);
	}

	[[nodiscard]] bool request_checksum_compare(IntercoreStorageMessage::FlashTarget target,
												StaticString<32> checksum,
												uint32_t address,
												uint32_t length,
												uint32_t *bytes_processed) {
		IntercoreStorageMessage message{
			.message_type = StartChecksumCompare,
			.address = address,
			.length = length,
			.checksum = checksum,
			.bytes_processed = bytes_processed,
			.flashTarget = target,
		};
		return comm_.send_message(message);
	}

	[[nodiscard]] bool request_file_flash(IntercoreStorageMessage::FlashTarget target,
										  std::span<uint8_t> buffer,
										  uint32_t address,
										  std::optional<uint32_t> uncompressed_size,
										  uint32_t *bytes_processed) {
		IntercoreStorageMessage message{
			.message_type = StartFlashing,
			.buffer = {(char *)buffer.data(), buffer.size()},
			.address = address,
			.uncompressed_size = uncompressed_size,
			.bytes_processed = bytes_processed,
			.flashTarget = target,
		};
		return comm_.send_message(message);
	}

	[[nodiscard]] bool request_delete_file(std::string_view filename, Volume vol) {
		IntercoreStorageMessage message{
			.message_type = RequestDeleteFile,
			.vol_id = vol,
			.filename = filename,
		};
		return comm_.send_message(message);
	}

	[[nodiscard]] bool request_read_flash(std::span<uint8_t> buffer, uint32_t address) {
		IntercoreStorageMessage message{
			.message_type = RequestReadFlash,
			.buffer = {(char *)buffer.data(), buffer.size()},
			.address = address,
		};
		return comm_.send_message(message);
	}

	enum class WriteResult { Busy, Success, InvalidVol };

	WriteResult request_write_file(std::span<char> file_data, Volume vol, std::string_view filename) {
		if (vol == Volume::RamDisk || vol == Volume::MaxVolumes) {
			pr_err("Error: not a valid volume for writing a patch\n");
			return WriteResult::InvalidVol;
		}

		IntercoreStorageMessage message{
			.message_type = RequestWriteFile,
			.vol_id = vol,
			.buffer = file_data,
			.filename = filename,
		};

		return comm_.send_message(message) ? WriteResult::Success : WriteResult::Busy;
	}

	WriteResult request_append_file(std::span<char> file_data, Volume vol, std::string_view filename) {
		if (vol == Volume::RamDisk || vol == Volume::MaxVolumes) {
			pr_err("Error: not a valid volume for writing a patch\n");
			return WriteResult::InvalidVol;
		}

		IntercoreStorageMessage message{
			.message_type = RequestAppendFile,
			.vol_id = vol,
			.buffer = file_data,
			.filename = filename,
		};

		return comm_.send_message(message) ? WriteResult::Success : WriteResult::Busy;
	}

	bool request_factory_reset() {
		IntercoreStorageMessage message{.message_type = RequestFactoryReset};
		return comm_.send_message(message);
	}

	bool request_reload_factory_patches() {
		IntercoreStorageMessage message{.message_type = RequestReloadDefaultPatches};
		return comm_.send_message(message);
	}

	bool request_plugin_file_list(PluginFileList *plugin_file_list) {
		IntercoreStorageMessage message{.message_type = RequestPluginFileList, .plugin_file_list = plugin_file_list};
		return comm_.send_message(message);
	}

	// Query the patch file cache (faster than reading from disk)
	bool request_patchfile_info(Volume vol, std::string_view path) {
		IntercoreStorageMessage message{.message_type = RequestPatchFileInfo, .vol_id = vol, .filename = path};
		return comm_.send_message(message);
	}

	bool request_file_info(Volume vol, std::string_view path) {
		IntercoreStorageMessage message{.message_type = RequestFileInfo, .vol_id = vol, .filename = path};
		return comm_.send_message(message);
	}

	[[nodiscard]] bool request_wifi_ip() {
		IntercoreStorageMessage message{.message_type = RequestWifiIP};
		return comm_.send_message(message);
	}

	[[nodiscard]] bool
	request_dir_entries(DirTree<FileEntry> *dir_tree, Volume vol, std::string_view path, std::string_view extension) {
		IntercoreStorageMessage message{
			.message_type = RequestDirEntries,
			.vol_id = vol,
			.filename = path,			// directory whose contents to display
			.dest_filename = extension, // filter by extension. example: "wav" => shows *.wav (subdirs are always shown)
			.dir_entries = dir_tree,	// this is where we want M4 to copy the dir tree
		};

		if (!list_buffer_.empty()) {
			message.dir_entries = nullptr;
			message.buffer = list_buffer_;
		}

		if (!comm_.send_message(message))
			return false;

		pending_dir_tree_ = dir_tree;
		return true;
	}

private:
	FileStorageComm &comm_;
	PatchDirList &patch_dir_list_;
	std::span<char> raw_patch_data_;
	std::span<char> list_buffer_;
	DirTree<FileEntry> *pending_dir_tree_ = nullptr;
};
} // namespace MetaModule
