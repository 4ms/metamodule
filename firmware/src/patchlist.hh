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
	const ModuleTypeSlug &get_patch_name(uint32_t patch_id) {
		if (_patch_data.size() == 0)
			return nullslug;

		if (patch_id >= _patch_data.size())
			patch_id = 0;
		return _patch_data[patch_id].patch_name;
	}

	// Return a reference to the patch at the given index (bounds-checked)
	const PatchData &get_patch(uint32_t patch_id) {
		if (_patch_data.size() == 0)
			return nullpatch;

		if (patch_id >= _patch_data.size())
			patch_id = 0;
		return _patch_data[patch_id];
	}

	uint32_t num_patches() const {
		return _patch_data.size();
	}

	// Stores the given index, making sure it's in bounds
	void set_cur_patch_index(uint32_t new_idx) {
		if (new_idx >= _patch_data.size())
			_cur_patch_index = 0;
		else
			_cur_patch_index = new_idx;
	}

	// Retrieves the previously stored index
	uint32_t cur_patch_index() const {
		return _cur_patch_index;
	}

	// Returns true if patch list is in a valid state
	bool is_ready() const {
		return _status == Status::Ready;
	}

	void set_status(Status status) {
		_status = status;
	}

	void clear_all_patches() {
		_patch_data.clear();
	}

	void add_patch_from_yaml(const std::span<char> data);
	void add_patch_from_yaml(const std::span<uint8_t> data);

private:
	std::vector<PatchData> _patch_data;
	Status _status;
	uint32_t _cur_patch_index = 0;

	static inline const PatchData nullpatch{};
	static inline const ModuleTypeSlug nullslug{""};
};
} // namespace MetaModule
