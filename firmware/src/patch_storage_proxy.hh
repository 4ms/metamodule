#pragma once
#include "patch_data.hh"
#include "patchlist.hh"

namespace MetaModule
{

class PatchStorageProxy {
	PatchData _view_patch;

public:
	PatchList patch_list;

	PatchStorageProxy() {
		patch_list.add_patch_header(Volume::SDCard, "abc", 1234, 0xC5, "NotReal");
	}

	bool load_view_patch(uint32_t patch_id) {
		return true;
	}

	PatchData &get_view_patch() {
		return _view_patch;
	}

	uint32_t get_view_patch_id() {
		return 0;
	}
};
} // namespace MetaModule
