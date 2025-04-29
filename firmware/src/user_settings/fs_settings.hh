#pragma once
#include <cstdint>

namespace MetaModule
{

struct FilesystemSettings {
	bool auto_reload_patch_file{true}; //ignored
	uint32_t max_open_patches{DefaultMaxOpenPatches};

	static constexpr uint32_t MinOpenPatches = 2;
	static constexpr uint32_t DefaultMaxOpenPatches = 15;
	static constexpr uint32_t MaxOpenPatches = 20;

	void make_valid() {
		if (max_open_patches > MaxOpenPatches || max_open_patches < MinOpenPatches)
			max_open_patches = DefaultMaxOpenPatches;
	}
};

} // namespace MetaModule
