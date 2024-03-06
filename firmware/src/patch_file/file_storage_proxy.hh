#pragma once
#include "core_intercom/intercore_message.hh"
#include "patch/patch_data.hh"
#include "patch_convert/patch_to_yaml.hh"
#include "patch_convert/yaml_to_patch.hh"
#include "patch_file.hh"
#include "patch_file/file_storage_comm.hh"
#include "patch_file/patch_location.hh"
#include "pr_dbg.hh"
#include "util/seq_map.hh"

namespace MetaModule
{

class FileStorageProxy {

public:
	using enum IntercoreStorageMessage::MessageType;

	FileStorageProxy(std::span<char> raw_patch_data, FileStorageComm &comm, PatchDirList &patch_dir_list)
		: patch_dir_list_{patch_dir_list}
		, comm_{comm}
		, raw_patch_data_{raw_patch_data} {
	}

	IntercoreStorageMessage get_message() {
		return comm_.get_new_message();
	}

	//
	// viewpatch: Patch we are currently viewing in the GUI:
	//
	[[nodiscard]] bool request_viewpatch(PatchLocation patch_loc) {
		IntercoreStorageMessage message{
			.message_type = RequestPatchData,
			.vol_id = patch_loc.vol,
			.buffer = raw_patch_data_,
			.filename = patch_loc.filename,
		};
		if (!comm_.send_message(message))
			return false;

		requested_view_patch_loc_ = patch_loc;
		return true;
	}

	bool open_patch_file(PatchLocHash patch_loc_hash) {
		if (auto patch = open_patches_.get(patch_loc_hash)) {
			view_patch_ = patch;
			return true;
		} else {
			return false;
		}
	}

	// TODO: pass the span as an arg, not as a member var
	bool parse_view_patch(uint32_t bytes_read) {
		std::span<char> file_data = raw_patch_data_.subspan(0, bytes_read);

		// Load into a temporary patch file, so if it fails, view_patch_ is not effected
		// And if ryml fails to deserialize, we aren't left with data from the last patch
		PatchData patch;
		if (!yaml_raw_to_patch(file_data, patch))
			return false;

		if (auto new_patch = open_patches_.overwrite(PatchLocHash{requested_view_patch_loc_}, patch)) {
			view_patch_ = new_patch;
			view_patch_loc_ = requested_view_patch_loc_;
			return true;
		} else
			return false;
	}

	PatchData &get_view_patch() {
		return *view_patch_;
	}

	StaticString<255> get_view_patch_filename() {
		return view_patch_loc_.filename;
	}

	Volume get_view_patch_vol() {
		return view_patch_loc_.vol;
	}

	//
	// patchlist: list of all patches found on all volumes
	//
	[[nodiscard]] bool request_patchlist() {
		IntercoreStorageMessage message{.message_type = RequestRefreshPatchList, .patch_dir_list = &patch_dir_list_};
		return comm_.send_message(message);
	}

	PatchDirList &get_patch_list() {
		//FIXME: Ensure this is only called when
		//we have access to the shared data. Return a ptr,
		//or return nullptr if we've sent a RequestRefreshPatchList but
		//haven't gotten a reply yet
		return patch_dir_list_;
	}

	// Scan all mounted volumes for firmware update files
	[[nodiscard]] bool request_find_firmware_file() {
		IntercoreStorageMessage message{.message_type = RequestFirmwareFile};
		return comm_.send_message(message);
	}

	// Load a file from filesystem to RAM
	[[nodiscard]] bool request_load_file(std::string_view filename, Volume vol, std::span<char> buffer) {
		IntercoreStorageMessage message{
			.message_type = RequestLoadFileToRam,
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
										  uint32_t *bytes_processed) {
		IntercoreStorageMessage message{
			.message_type = StartFlashing,
			.buffer = {(char *)buffer.data(), buffer.size()},
			.address = address,
			.bytes_processed = bytes_processed,
			.flashTarget = target,
		};
		return comm_.send_message(message);
	}

	void new_patch() {
		std::string name = "Untitled Patch " + std::to_string((uint8_t)std::rand());
		view_patch_ = &unsaved_patch_;
		view_patch_->blank_patch(name);

		name += ".yml";
		view_patch_loc_.filename.copy(name);
		view_patch_loc_.vol = Volume::RamDisk;
	}

	bool write_patch(std::string_view filename = "") {
		if (filename == "")
			filename = view_patch_loc_.filename;

		std::span<char> file_data = raw_patch_data_;

		patch_to_yaml_buffer(*view_patch_, file_data);

		IntercoreStorageMessage message{
			.message_type = RequestWritePatchData,
			.vol_id = view_patch_loc_.vol,
			.buffer = file_data,
			.filename = filename,
		};

		return comm_.send_message(message);
	}

	bool request_reset_factory_patches() {
		IntercoreStorageMessage message{
			.message_type = RequestFactoryResetPatches,
		};
		return comm_.send_message(message);
	}

	bool request_plugin_file_list(PluginFileList *plugin_file_list) {
		IntercoreStorageMessage message{
			.message_type = RequestPluginFileList,
			.plugin_file_list = plugin_file_list,
		};
		return comm_.send_message(message);
	}

	bool request_copy_dir_to_ramdisk(Volume vol, std::string_view path) {
		IntercoreStorageMessage message{.message_type = RequestCopyPluginAssets, .vol_id = vol, .filename = path};
		return comm_.send_message(message);
	}

private:
	PatchDirList &patch_dir_list_;

	FileStorageComm &comm_;

	std::span<char> raw_patch_data_;

	PatchData unsaved_patch_;
	PatchData *view_patch_ = &unsaved_patch_;

	SeqMap<PatchLocHash, PatchData, 32> open_patches_;

	PatchLocation requested_view_patch_loc_;
	PatchLocation view_patch_loc_;
};
} // namespace MetaModule
