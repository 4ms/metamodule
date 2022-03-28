#pragma once
#include "patch/patch.hh"
#include "patch/patch_data.hh"
#include <vector>

namespace MetaModule
{

struct PatchList {
	enum class Status { NotLoaded, Loading, Ready };

	PatchList();

	// Returns the name of the patch at a given index (bounds-checked)
	ModuleTypeSlug &get_patch_name(uint32_t patch_id) {
		if (patch_id >= _num_patches)
			patch_id = 0;
		return _patch_data[patch_id].patch_name;
	}

	// Return a reference to the patch at the given index (bounds-checked)
	PatchData &get_patch(uint32_t patch_id) {
		if (patch_id >= _num_patches)
			patch_id = 0;
		return _patch_data[patch_id];
	}

	uint32_t num_patches() {
		return _num_patches;
	}

	// Stores the given index, making sure it's in bounds
	void set_cur_patch_index(uint32_t new_idx) {
		if (new_idx >= _num_patches)
			_cur_patch_index = 0;
		else
			_cur_patch_index = new_idx;
	}

	// Retrieves the previously stored index
	uint32_t cur_patch_index() {
		return _cur_patch_index;
	}

	// Returns true if patch list is in a valid state
	bool is_ready() {
		return _status == Status::Ready;
	}

	void set_status(Status status) {
		_status = status;
	}

	void clear_all_patches() {
		_num_patches = 0;
		_patch_data.clear();
	}

	void add_patch_from_yaml(const std::span<char> data);

private:
	std::vector<PatchData> _patch_data;
	Status _status;
	uint32_t _num_patches = 0;
	uint32_t _cur_patch_index = 0;
};
} // namespace MetaModule
