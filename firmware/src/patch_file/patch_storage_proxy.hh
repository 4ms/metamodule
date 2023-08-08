#pragma once
#include "core_intercom/patch_icc_message.hh"
#include "drivers/inter_core_comm.hh"
#include "patch_convert/yaml_to_patch.hh"
#include "patch_data.hh"
#include "patch_file.hh"
#include "patchlist.hh"

namespace MetaModule
{

class PatchStorageProxy {

public:
	using enum PatchICCMessage::MessageType;

	PatchStorageProxy(std::span<char> raw_patch_data,
					  volatile PatchICCMessage &shared_message,
					  PatchFileList &remote_patch_list)
		: remote_patch_list_{remote_patch_list}
		, comm_{shared_message}
		, raw_patch_data_{raw_patch_data} {
	}

	[[nodiscard]] bool request_viewpatch(Volume vol, uint32_t patch_id) {
		PatchICCMessage message{
			.message_type = RequestPatchData,
			.patch_id = patch_id,
			.vol_id = vol,
		};
		if (!comm_.send_message(message))
			return false;

		requested_view_patch_id_ = patch_id;
		requested_view_patch_vol_ = vol;
		return true;
	}

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

	PatchICCMessage get_message() {
		return comm_.get_new_message();
	}

	[[nodiscard]] bool request_patchlist() {
		PatchICCMessage message{.message_type = RequestRefreshPatchList};
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

private:
	PatchFileList &remote_patch_list_;
	mdrivlib::InterCoreComm<mdrivlib::ICCCoreType::Initiator, PatchICCMessage> comm_;

	std::span<char> raw_patch_data_;
	PatchData view_patch_;
	uint32_t requested_view_patch_id_ = 0;
	Volume requested_view_patch_vol_ = Volume::NorFlash;
	uint32_t view_patch_id_ = 0;
	Volume view_patch_vol_ = Volume::NorFlash;
};
} // namespace MetaModule
