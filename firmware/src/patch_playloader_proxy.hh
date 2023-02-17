#pragma once
#include <cstdint>

namespace MetaModule
{

class PatchPlayLoaderProxy {
	//
public:
	void handle_sync_patch_loading() {
	}

	uint32_t cur_patch_index() {
		return 0;
	}
	void request_load_patch(uint32_t patch_id) {
	}
};
} // namespace MetaModule
