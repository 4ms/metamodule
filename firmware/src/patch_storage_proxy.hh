#pragma once
#include "inter_core_comm.hh"
#include "patch_data.hh"
#include "patch_file.hh"
#include "patchlist.hh"

namespace MetaModule
{
using PatchFileList = std::span<PatchFile>;

class PatchStorageProxy {
	using InterCoreComm1 = InterCoreComm<ICCCoreType::Initiator>;

public:
	using enum InterCoreCommMessage::MessageType;

	PatchStorageProxy(std::span<PatchFile> &remote_patch_list,
					  std::span<char> raw_patch_data,
					  volatile InterCoreCommMessage &shared_message)
		: remote_patch_list_{remote_patch_list}
		, comm_{shared_message} {
	}

	[[nodiscard]] bool request_viewpatch(uint32_t patch_id) {
		InterCoreCommMessage message{
			.message_type = RequestPatchData,
			.patch_id = patch_id,
		};
		if (!comm_.send_message(message))
			return false;
		return true;
	}

	bool load_view_patch(uint32_t patch_id) {
		return true;
	}

	PatchData &get_view_patch() {
		return view_patch_;
	}

	uint32_t get_view_patch_id() {
		return 0;
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
	InterCoreComm1 comm_;

	PatchData view_patch_;
	uint32_t view_patch_id_;
};
} // namespace MetaModule
