#pragma once
#include "patch/patch.hh"
#include "patch/patch_data.hh"
#include <vector>

namespace MetaModule
{

struct PatchList {
	int32_t NumPatches = 2;

	PatchList();

	// Returns the name of the patch at a given index (bounds-checked)
	ModuleTypeSlug &get_patch_name(uint32_t patch_id) {
		if (patch_id >= NumPatches)
			patch_id = 0;
		return _patch_data[patch_id].patch_name;
	}

	// Return a reference to the patch at the given index (bounds-checked)
	PatchData &get_patch(uint32_t patch_id) {
		if (patch_id >= NumPatches)
			patch_id = 0;
		return _patch_data[patch_id];
	}

	// Stores the given index, making sure its in bounds
	void set_cur_patch_index(uint32_t new_idx) {
		if (new_idx >= NumPatches)
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

	static ModuleTypeSlug get_default_patch_filename(uint32_t id);
	static size_t get_default_patch_data(uint32_t id, const uint8_t *data);

	enum class Status { NotLoaded, Loading, Ready } _status;
	void set_status(Status status) {
		_status = status;
	}

	void clear_all_patches() {
		_patch_data.clear();
	}

	void add_patch_from_yaml(const std::span<char> data);

private:
	std::vector<PatchData> _patch_data;
	uint32_t _cur_patch_index = 0;
};
} // namespace MetaModule
