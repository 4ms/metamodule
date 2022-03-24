#pragma once
#include "norfs.hh"
#include "patch/patch.hh"
#include "patch/patch_data.hh"
#include <vector>

namespace MetaModule
{

struct PatchList {
	int32_t NumPatches = 2;

	PatchList();
	PatchList(NorFlashFS &norfs);

	ModuleTypeSlug &get_patch_name(uint32_t patch_id) {
		if (patch_id >= NumPatches)
			patch_id = 0;
		return _patch_data[patch_id].patch_name;
	}

	PatchData *get_cur_patch_data() {
		if (_cur_patch_index >= NumPatches)
			_cur_patch_index = 0;
		return &_patch_data[_cur_patch_index];
	}

	uint32_t cur_patch() {
		if (_cur_patch_index >= NumPatches)
			_cur_patch_index = 0;
		return _cur_patch_index;
	}

	void set_cur_patch_index(uint32_t new_idx) {
		if (new_idx >= NumPatches)
			_cur_patch_index = 0;
		else
			_cur_patch_index = new_idx;
	}

	uint32_t cur_patch_index() {
		return _cur_patch_index;
	}

	uint32_t next_patch_index() {
		return _cur_patch_index >= (NumPatches - 1) ? 0 : _cur_patch_index + 1;
	}

	uint32_t prev_patch_index() {
		return _cur_patch_index == 0 ? (NumPatches - 1) : _cur_patch_index - 1;
	}
	void refresh_patches_from_fs();

private:
	// TODO: _raw_patch_yaml_files will get loaded from filesystem
	// one at a time, and loaded into _patch_headers/data. Not an array:
	// char *_raw_patch_yaml_file_data;
	std::vector<PatchData> _patch_data;
	uint32_t _cur_patch_index = 0;
};
} // namespace MetaModule
