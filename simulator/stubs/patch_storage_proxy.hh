#pragma once
#include <cstdint>

#include "patch/patch_data.hh"
#include "patch_file.hh"
#include "patches_default.hh"
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
		msg_state_ = MsgState::ViewPatchRequested;
		return true;
	}

	bool parse_view_patch(uint32_t bytes_read) {
		std::span<char> file_data = raw_patch_data_.subspan(0, bytes_read);
		if (!yaml_raw_to_patch(file_data, view_patch_))
			return false;

		view_patch_id_ = requested_view_patch_id_;
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
		// Simulator uses the DefaultPatches as if it were the NOR Flash:

		if (msg_state_ == MsgState::ViewPatchRequested) {
			msg_state_ = MsgState::Idle;
			//load patch data into raw_patch_data_ and replace 1024 wtih actual size
			if (requested_view_patch_id_ < DefaultPatches::num_patches()) {
				raw_patch_data_ = DefaultPatches::get_patch(requested_view_patch_id_);
				uint32_t sz = raw_patch_data_.size_bytes();
				return {PatchDataLoaded, sz, requested_view_patch_id_, requested_view_patch_vol_};
			} else
				return {PatchDataLoadFail, 0, requested_view_patch_id_, requested_view_patch_vol_};
		}
		if (msg_state_ == MsgState::PatchListRequested) {
			msg_state_ = MsgState::Idle;
			if (patch_files_nor_.size() == 0) {
				for (uint32_t i = 0; i < DefaultPatches::num_patches(); i++) {
					auto p = DefaultPatches::get_patch(i);
					auto fn = DefaultPatches::get_filename(i);
					patch_files_nor_.push_back({fn, (uint32_t)p.size_bytes(), 1, fn});
				}
				remote_patch_list_.norflash = patch_files_nor_;
				return {PatchListChanged, 0, 0, 0};
			}
			return {PatchListUnchanged, 0, 0, 0};
		}

		return {};
	}

	[[nodiscard]] bool request_patchlist() {
		msg_state_ = MsgState::PatchListRequested;
		printf("Patchlist requested\n");
		return true;
	}

	PatchFileList &get_patch_list() {
		printf("Patchlist got\n");
		return remote_patch_list_;
	}

private:
	PatchFileList remote_patch_list_;
	std::vector<PatchFile> patch_files_nor_;

	std::span<char> raw_patch_data_;
	PatchData view_patch_;
	uint32_t requested_view_patch_id_ = 0;
	uint32_t requested_view_patch_vol_ = 0;
	uint32_t view_patch_id_ = 0;
	Volume view_patch_vol_ = Volume::NorFlash;

	enum class MsgState { Idle, ViewPatchRequested, PatchListRequested } msg_state_ = MsgState::Idle;
};
} // namespace MetaModule
