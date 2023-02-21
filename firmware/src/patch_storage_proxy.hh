#pragma once
#include "inter_core_comm.hh"
#include "patch_data.hh"
#include "patch_file.hh"
#include "patchlist.hh"

namespace MetaModule
{
using PatchFileList = std::span<PatchFile>;

class PatchStorageProxy {
	using InterCoreComm1 = InterCoreComm<ICCNum::Core1>;
	// using PatchFileList = std::vector<PatchList::PatchFile>;

public:
	using enum InterCoreComm1::Message;
	PatchStorageProxy(std::vector<PatchFile> *remote_patch_files)
		: remote_patch_files_{remote_patch_files} {
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

	InterCoreComm1::Message get_message() {
		return comm_.get_last_message();
	}

	[[nodiscard]] bool request_patchlist() {
		//send IPCC event
		if (!comm_.send_message(RequestRefreshPatchList))
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

	PatchData view_patch_;
	uint32_t view_patch_id_;
};
} // namespace MetaModule
