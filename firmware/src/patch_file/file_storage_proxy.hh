#pragma once
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "patch/patch_data.hh"
#include "patch_convert/yaml_to_patch.hh"
#include "patch_file.hh"
#include "patch_file/patch_location.hh"
#include "patchlist.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

class FileStorageProxy {

public:
	using enum IntercoreStorageMessage::MessageType;

	FileStorageProxy(std::span<char> raw_patch_data,
					 IntercoreStorageMessage &shared_message,
					 PatchFileList &remote_patch_list)
		: remote_patch_list_{remote_patch_list}
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
			.patch_id = patch_loc.index,
			.vol_id = patch_loc.vol,
			.buffer = raw_patch_data_,
		};
		if (!comm_.send_message(message))
			return false;

		requested_view_patch_id_ = patch_loc.index;
		requested_view_patch_vol_ = patch_loc.vol;
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
		view_patch_id_ = requested_view_patch_id_;
		view_patch_vol_ = requested_view_patch_vol_;
		return true;
	}

	PatchData &get_view_patch() {
		return view_patch_;
	}

	uint32_t get_view_patch_id() {
		return view_patch_id_;
	}

	Volume get_view_patch_vol() {
		return view_patch_vol_;
	}

	//
	// patchlist: list of all patches found on all volumes
	//
	// TODO: sender passes a reference to a PatchFileList which should be populated
	[[nodiscard]] bool request_patchlist() {
		IntercoreStorageMessage message{.message_type = RequestRefreshPatchList,
										.patch_file_list = &remote_patch_list_};
		if (!comm_.send_message(message))
			return false;
		return true;
	}

	PatchFileList &get_patch_list() {
		//FIXME: How can we insure this is only called when
		//we have access to the shared data?
		//Maybe transform get_message() into s.t. that returns
		//remote_patch_list if message is PatchListChanged?
		return remote_patch_list_;
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
			.filename = filename,
			.vol_id = vol,
			.buffer = buffer,
		};
		if (!comm_.send_message(message))
			return false;
		return true;
	}

private:
	PatchFileList &remote_patch_list_;
	mdrivlib::InterCoreComm<mdrivlib::ICCCoreType::Initiator, IntercoreStorageMessage> comm_;

	std::span<char> raw_patch_data_;
	PatchData view_patch_;
	uint32_t requested_view_patch_id_ = 0;
	Volume requested_view_patch_vol_ = Volume::NorFlash;
	uint32_t view_patch_id_ = 0;
	Volume view_patch_vol_ = Volume::NorFlash;
};
} // namespace MetaModule
