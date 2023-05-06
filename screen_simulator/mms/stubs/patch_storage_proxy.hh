#pragma once
#include <cstdint>

#include "patch/patch_data.hh"
#include "patch_file.hh"
#include "patchlist.hh"
#include "shared/patch_convert/yaml_to_patch.hh"
#include "volumes.hh"

namespace MetaModule
{

struct InterCoreCommMessage {
	enum MessageType : uint32_t {
		None,

		RequestRefreshPatchList,
		PatchListChanged,
		PatchListUnchanged,

		RequestPatchData,
		PatchDataLoadFail,
		PatchDataLoaded,

		NumRequests,
	};
	MessageType message_type;
	uint32_t bytes_read;
	uint32_t patch_id;
	uint32_t vol_id;
};

class PatchStorageProxy {

public:
	using enum InterCoreCommMessage::MessageType;

	PatchStorageProxy() = default;

	[[nodiscard]] bool request_viewpatch(Volume vol, uint32_t patch_id) {
		requested_view_patch_id_ = patch_id;
		requested_view_patch_vol_ = (uint32_t)vol;
		return true;
	}

	bool parse_view_patch(uint32_t bytes_read) {
		// std::span<char> file_data = raw_patch_data_.subspan(0, bytes_read);
		// if (!yaml_raw_to_patch(file_data, view_patch_))
		// 	return false;

		// view_patch_id_ = requested_view_patch_id_;
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

	InterCoreCommMessage get_message() {
		return {};
	}

	[[nodiscard]] bool request_patchlist() {
		// InterCoreCommMessage message{.message_type = RequestRefreshPatchList};
		// if (!comm_.send_message(message))
		// 	return false;
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
	PatchFileList remote_patch_list_;

	std::span<char> raw_patch_data_;
	PatchData view_patch_;
	uint32_t requested_view_patch_id_ = 0;
	uint32_t requested_view_patch_vol_ = 0;
	uint32_t view_patch_id_ = 0;
	Volume view_patch_vol_ = Volume::NorFlash;
};
} // namespace MetaModule
