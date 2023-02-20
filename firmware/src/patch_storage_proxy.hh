#pragma once
#include "patch_data.hh"
#include "patchlist.hh"
#include "shared_memory.hh"

namespace MetaModule
{

using PatchFileList = std::span<PatchList::PatchFile>;
// using PatchFileList = std::vector<PatchList::PatchFile>;
class PatchStorageProxy {

public:
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

	void read_messages() {
		last_message_ = comm_.get_last_message();
	}

	[[nodiscard]] InterCoreComm::Message get_message() {
		return comm_.get_last_message();
	}

	[[nodiscard]] bool request_patchlist() {
		//send IPCC event
		if (!comm_.send_message(InterCoreComm::Message::RequestRefreshPatchList))
			return false;
		return true;
	}

	[[nodiscard]] bool does_patchlist_require_refresh() {
		if (last_message_ == InterCoreComm::PatchListMediaChanged) {
			last_message_ = InterCoreComm::None;
			return true;
		}
		return false;
	}

	[[nodiscard]] bool is_patchlist_refreshed() {
		if (last_message_ == InterCoreComm::PatchListRefreshed) {
			last_message_ = InterCoreComm::None;
			auto pfs =
				SharedMemory::read_address_of<std::vector<PatchList::PatchFile> *>(SharedMemory::PatchListLocation);
			patch_files_ = *pfs; //vector -> span
			return true;
		}
		return false;
	}

	PatchFileList &get_patch_list() {
		return patch_files_;
	}

private:
	PatchData view_patch_;
	PatchFileList patch_files_;
	InterCoreComm comm_;
	InterCoreComm::Message last_message_ = InterCoreComm::None;
};
} // namespace MetaModule
