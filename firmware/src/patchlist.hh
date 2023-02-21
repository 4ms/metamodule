#pragma once
#include "patch/patch.hh"
#include "patch/patch_data.hh"
#include "patch_file.hh"
#include "volumes.hh"
#include <span>
#include <vector>

namespace MetaModule
{

//Structure idea:
//PatchList keeps an index of all known patches (patchname, filename, volume, timestamp, size), indexed by patch_id [uint]
//PatchLoader stores index of current loaded patch and requested new patch to load <<-- these will need to be invalidated/refreshed if PatchList index is refreshed
//??Pages get a ref to PatchStorage and can use that to... query patch information (get_patch(id) -> PatchData&)
//PatchSelectorPage works as-is
//PageList::set/get_selected_patch_id() ==> patch_storage.load_view_patch(id) [loads PatchData into private patch_storage._viewing_patch], only gets called when opening a patch
//  									    patch_storage.get_view_patch_id() -> uint32_t
//patch_list.get_patch(PageList::get..)	==> patch_storage.get_view_patch() -> PatchData &  [most pages accessing patch_list are actually calling this]
//
//PatchLoader handles loading patches into PatchPlayer (and syncing loading with the audio stream)
//

struct PatchList {
	enum class Status { NotLoaded, Loading, Ready };

	PatchList() = default;

	// Returns the name of the patch at a given index (bounds-checked)
	const ModuleTypeSlug &get_patch_name(uint32_t patch_id) {
		if (_patch_data.size() == 0)
			return nullslug;

		if (patch_id >= _patch_data.size())
			patch_id = 0;
		return _patch_data[patch_id].patchname;
	}

	// Returns the volume of the patch at a given index (bounds-checked)
	const Volume get_patch_vol(uint32_t patch_id) {
		if (_patch_data.size() == 0)
			return Volume{0};

		if (patch_id >= _patch_data.size())
			patch_id = 0;
		return _patch_data[patch_id].volume;
	}

	const std::string_view get_patch_filename(uint32_t patch_id) {
		if (_patch_data.size() == 0)
			return nullslug;

		if (patch_id >= _patch_data.size())
			patch_id = 0;
		return _patch_data[patch_id].filename;
	}

	std::optional<uint32_t> find_by_name(std::string_view &patchname) {
		for (uint32_t i = 0; auto &x : _patch_data) {
			if (x.patchname == patchname)
				return {i};
			i++;
		}
		return std::nullopt;
	}

	// Return a reference to the patch at the given index (bounds-checked)
	[[deprecated]] PatchData &get_patch(uint32_t patch_id) {
		// if (_patch_data.size() == 0)
		return nullpatch;

		// if (patch_id >= _patch_data.size())
		// 	patch_id = 0;
		// return _patch_data[patch_id].patch_data;
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

	void clear_patches_from(Volume vol) {
		std::erase_if(_patch_data, [&](auto &pf) { return (pf.volume == vol); });
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

	// void add_patch_from_yaml(const std::span<std::byte> data);
	// void add_patch_from_yaml(const std::span<char> data);
	// void add_patch_from_yaml(const std::span<uint8_t> data);

	void add_patch_header(Volume volume,
						  const std::string_view filename,
						  uint32_t filesize,
						  uint32_t timestamp,
						  ModuleTypeSlug patchname) {
		_patch_data.push_back({volume, std::string{filename}, filesize, timestamp, patchname});
		// _patch_data.emplace_back(volume, filename, 0, 0, "");
	}

	std::vector<PatchFile> &get_patchfile_list() {
		return _patch_data;
	}

private:
	// FIXME: We could get fragmentation if patch list is changed frequently
	// Use an arena or some separate memory area, which is wiped when we refresh (re-insert SD card)
	// We'd need to estimate the max size of all patches to do this.
	std::vector<PatchFile> _patch_data;
	Status _status = Status::NotLoaded;
	bool _has_been_updated = false;
	bool _locked = false;

	static inline PatchData nullpatch{};
	static inline const ModuleTypeSlug nullslug{""};
};
} // namespace MetaModule
