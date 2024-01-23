#pragma once
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "patch/patch_data.hh"
#include "patch_convert/patch_to_yaml.hh"
#include "patch_convert/yaml_to_patch.hh"
#include "patch_file.hh"
#include "patch_file/patch_location.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

class FileStorageProxy {

public:
	using enum IntercoreStorageMessage::MessageType;

	FileStorageProxy(std::span<char> raw_patch_data,
					 IntercoreStorageMessage &shared_message,
					 PatchDirList &patch_dir_list)
		: patch_dir_list_{patch_dir_list}
		, comm_{shared_message}
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

		requested_view_patch_loc_.filename = patch_loc.filename;
		requested_view_patch_loc_.vol = patch_loc.vol;
		return true;
	}

	// TODO: pass the span as an arg, not as a member var
	bool parse_view_patch(uint32_t bytes_read) {
		std::span<char> file_data = raw_patch_data_.subspan(0, bytes_read);

		// Load into a temporary patch file, so if it fails, view_patch_ is not effected
		// And if ryml fails to deserialize, we aren't left with data from the last patch
		PatchData patch;
		if (!yaml_raw_to_patch(file_data, patch))
			return false;

		view_patch_ = patch;
		view_patch_loc_.filename = requested_view_patch_loc_.filename;
		view_patch_loc_.vol = requested_view_patch_loc_.vol;
		return true;
	}

	PatchData &get_view_patch() {
		return view_patch_;
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
		if (!comm_.send_message(message))
			return false;
		return true;
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
		if (!comm_.send_message(message))
			return false;
		return true;
	}

	// Load a file from filesystem to RAM
	[[nodiscard]] bool request_load_file(std::string_view filename, Volume vol, std::span<char> buffer) {
		IntercoreStorageMessage message{
			.message_type = RequestLoadFileToRam,
			.vol_id = vol,
			.buffer = buffer,
			.filename = filename,
		};
		if (!comm_.send_message(message))
			return false;
		return true;
	}

	void new_patch() {
		std::string name = "Untitled Patch " + std::to_string((uint8_t)HAL_GetTick());
		view_patch_.blank_patch(name);

		name += ".yml";
		view_patch_loc_.filename.copy(name);
		view_patch_loc_.vol = Volume::RamDisk;
	}

	bool write_patch(std::string_view filename = "") {
		if (filename == "")
			filename = view_patch_loc_.filename;

		std::span<char> file_data = raw_patch_data_;

		patch_to_yaml_buffer(view_patch_, file_data);

		// printf("size: %zu, %zu\n", file_data.size(), sz);
		// printf("%.*s\n", (int)sz, file_data.data());

		IntercoreStorageMessage message{
			.message_type = RequestWritePatchData,
			.vol_id = view_patch_loc_.vol,
			.buffer = file_data,
			.filename = filename,
		};

		if (!comm_.send_message(message))
			return false;

		return true;
	}

	bool request_reset_factory_patches() {
		IntercoreStorageMessage message{
			.message_type = RequestFactoryResetPatches,
		};
		if (!comm_.send_message(message))
			return false;
		return true;
	}

private:
	PatchDirList &patch_dir_list_;

	mdrivlib::InterCoreComm<mdrivlib::ICCCoreType::Initiator, IntercoreStorageMessage> comm_;

	std::span<char> raw_patch_data_;
	PatchData view_patch_;

	PatchLocation requested_view_patch_loc_;
	PatchLocation view_patch_loc_;
};
} // namespace MetaModule
