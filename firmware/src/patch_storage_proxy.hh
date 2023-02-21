#pragma once
#include "inter_core_comm.hh"
#include "patch_data.hh"
#include "patch_file.hh"
#include "patchlist.hh"

namespace MetaModule
{
using PatchFileList = std::span<PatchFile>;
// using PatchFileList = std::vector<PatchList::PatchFile>;

class PatchStorageProxy {
	using InterCoreComm1 = InterCoreComm<ICCCoreType::Initiator>;

public:
	using enum InterCoreCommMessage::MessageType;

	PatchStorageProxy(std::vector<PatchFile> *remote_patch_files, volatile InterCoreCommMessage &shared_message)
		: remote_patch_files_{remote_patch_files}
		, comm_{shared_message} {
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
		//send IPCC event
		icc_params.message_type = RequestRefreshPatchList;
		if (!comm_.send_message(icc_params))
			return false;
		return true;
	}

	PatchFileList &get_patch_list() {
		patch_files_ = *remote_patch_files_; //vector* -> span
		return patch_files_;
	}

private:
	std::vector<PatchFile> *remote_patch_files_;
	PatchFileList patch_files_;
	InterCoreComm1 comm_;
	InterCoreCommMessage icc_params;

	PatchData view_patch_;
	uint32_t view_patch_id_;
};
} // namespace MetaModule
