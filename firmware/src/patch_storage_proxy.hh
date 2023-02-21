#pragma once
#include "inter_core_comm.hh"
#include "patch_data.hh"
#include "patchlist.hh"
#include "shared_memory.hh"

namespace MetaModule
{
using PatchFileList = std::span<PatchList::PatchFile>;

class PatchStorageProxy {
	using InterCoreComm1 = InterCoreComm<ICCNum::Core1>;
	// using PatchFileList = std::vector<PatchList::PatchFile>;

public:
	using enum InterCoreComm1::Message;
	PatchStorageProxy() = default;

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
		auto pfs = SharedMemory::read_address_of<std::vector<PatchList::PatchFile> *>(SharedMemory::PatchListLocation);
		patch_files_ = *pfs; //vector* -> span
		return patch_files_;
	}

private:
	PatchData view_patch_;
	PatchFileList patch_files_;
	InterCoreComm1 comm_;
};
} // namespace MetaModule
