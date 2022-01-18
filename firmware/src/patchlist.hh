#pragma once
#include "patch/patch.hh"
#include "patch_convert/patch_data.hh"

namespace MetaModule
{

struct PatchList {
	//Todo: NumPatches will be set by the number of valid patches loaded from the filesystem
	static constexpr int32_t NumPatches = 1;

	PatchList();

	ModuleTypeSlug &get_patch_name(uint32_t patch_id) {
		if (patch_id >= NumPatches)
			patch_id = 0;
		return _patch_headers[patch_id].patch_name;
	}

	PatchHeader *get_cur_patch_header() {
		if (_cur_patch_index >= NumPatches)
			_cur_patch_index = 0;
		return &_patch_headers[_cur_patch_index];
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

private:
	// TODO: _raw_patch_yaml_files will get loaded from filesystem
	// one at a time, and loaded into _patch_headers/data. Not an array:
	// char *_raw_patch_yaml_file_data;
	std::array<void *, NumPatches> _raw_patch_yaml_files;

	std::array<PatchHeader, NumPatches> _patch_headers;
	std::array<PatchData, NumPatches> _patch_data;
	uint32_t _cur_patch_index = 0;
};
} // namespace MetaModule
