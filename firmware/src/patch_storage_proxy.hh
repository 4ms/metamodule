#pragma once
#include "inter_core_comm.hh"
#include "patch_convert/yaml_to_patch.hh"
#include "patch_data.hh"
#include "patch_file.hh"
#include "patchlist.hh"

namespace MetaModule
{
using PatchFileList = std::span<PatchFile>;

class PatchStorageProxy {

public:
	using enum InterCoreCommMessage::MessageType;

	PatchStorageProxy(std::span<char> raw_patch_data,
					  volatile InterCoreCommMessage &shared_message,
					  std::span<PatchFile> &remote_patch_list)
		: remote_patch_list_{remote_patch_list}
		, comm_{shared_message}
		, raw_patch_data_{raw_patch_data} {
	}

	[[nodiscard]] bool request_viewpatch(uint32_t patch_id) {
		InterCoreCommMessage message{
			.message_type = RequestPatchData,
			.patch_id = patch_id,
		};
		if (!comm_.send_message(message))
			return false;

		requested_view_patch_id_ = patch_id;
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

	InterCoreCommMessage get_message() {
		return comm_.get_new_message();
	}

	[[nodiscard]] bool request_patchlist() {
		InterCoreCommMessage message{.message_type = RequestRefreshPatchList};
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
	std::span<PatchFile> &remote_patch_list_;
	InterCoreComm<ICCCoreType::Initiator> comm_;

	std::span<char> raw_patch_data_;
	PatchData view_patch_;
	uint32_t requested_view_patch_id_ = 0;
	uint32_t view_patch_id_ = 0;
};
} // namespace MetaModule
