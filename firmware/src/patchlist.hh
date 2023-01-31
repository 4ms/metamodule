#pragma once
#include "patch/patch.hh"
#include "patch/patch_data.hh"
#include <span>
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
	PatchData &get_patch(uint32_t patch_id) {
		if (_patch_data.size() == 0)
			return nullpatch;

		if (patch_id >= _patch_data.size())
			patch_id = 0;
		return _patch_data[patch_id];
	}

	uint32_t num_patches() const {
		return _patch_data.size();
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

	[[nodiscard]] bool is_modified() {
		if (_has_been_updated) {
			_has_been_updated = false;
			return true;
		}
		return false;
	}

	void mark_modified() {
		_has_been_updated = true;
	}

	//FIXME: use _status, not _locked
	bool is_locked() {
		return _locked;
	}

	void lock() {
		_locked = true;
	}

	void unlock() {
		_locked = false;
	}

	void add_patch_from_yaml(const std::span<std::byte> data);
	void add_patch_from_yaml(const std::span<char> data);
	void add_patch_from_yaml(const std::span<uint8_t> data);

private:
	struct PatchFile {
		PatchData patch_data;
		std::string filepath;
	};

	// FIXME: We could get fragmentation if patch list is changed frequently
	// Use an arena or some separate memory area, which is wiped with every change
	// We'd need to estimate the max size of all patches to do this.
	std::vector<PatchData> _patch_data;
	Status _status;
	bool _has_been_updated = false;
	bool _locked = false;

	static inline PatchData nullpatch{};
	static inline const ModuleTypeSlug nullslug{""};
};
} // namespace MetaModule
