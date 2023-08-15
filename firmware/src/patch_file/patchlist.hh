#pragma once
#include "fs/volumes.hh"
#include "patch/patch.hh"
#include "patch/patch_data.hh"
#include "patch_file.hh"
#include <span>
#include <vector>

namespace MetaModule
{

struct PatchList {
	PatchList() {
		_patch_data_sd.reserve(32);
		_patch_data_usb.reserve(32);
		_patch_data_nor.reserve(32);
	}

	const auto &_get_list(Volume vol) const {
		if (vol == Volume::USB)
			return _patch_data_usb;
		if (vol == Volume::SDCard)
			return _patch_data_sd;
		return _patch_data_nor;
	}

	// Returns the name of the patch at a given index (bounds-checked)
	const ModuleTypeSlug &get_patch_name(Volume vol, uint32_t patch_id) {
		const auto &_patch_data = _get_list(vol);
		if (_patch_data.size() == 0)
			return nullslug;

		if (patch_id >= _patch_data.size())
			patch_id = 0;
		return _patch_data[patch_id].patchname;
	}

	std::string_view get_patch_filename(Volume vol, uint32_t patch_id) {
		const auto &_patch_data = _get_list(vol);
		if (_patch_data.size() == 0)
			return nullslug;

		if (patch_id >= _patch_data.size())
			return nullslug;

		return _patch_data[patch_id].filename;
	}

	std::optional<uint32_t> find_by_name(Volume vol, std::string_view &patchname) const {
		const auto &_patch_data = _get_list(vol);
		for (uint32_t i = 0; auto &x : _patch_data) {
			if (x.patchname == patchname)
				return {i};
			i++;
		}
		return std::nullopt;
	}

	uint32_t num_patches(Volume vol) const {
		const auto &_patch_data = _get_list(vol);
		return _patch_data.size();
	}

	uint32_t num_patches() const {
		return num_patches(Volume::SDCard) + num_patches(Volume::USB) + num_patches(Volume::NorFlash);
	}

	void clear_patches(Volume vol) {
		if (vol == Volume::USB)
			_patch_data_usb.clear();
		if (vol == Volume::SDCard)
			_patch_data_sd.clear();
		if (vol == Volume::NorFlash)
			_patch_data_nor.clear();
	}

	void add_patch_header(
		Volume vol, const std::string_view filename, uint32_t filesize, uint32_t timestamp, ModuleTypeSlug patchname) {
		if (vol == Volume::USB)
			_patch_data_usb.push_back({std::string{filename}, filesize, timestamp, patchname});
		if (vol == Volume::SDCard)
			_patch_data_sd.push_back({std::string{filename}, filesize, timestamp, patchname});
		if (vol == Volume::NorFlash)
			_patch_data_nor.push_back({std::string{filename}, filesize, timestamp, patchname});
	}

	auto get_patchfile_list(Volume vol) const {
		return std::span<const PatchFile>(_get_list(vol));
	}

private:
	// FIXME: We could get fragmentation if patch list is changed frequently
	// Use std::pmr::vector<PatchFile> (with std::pmr::string inside PatchFile)
	// and a monotonic buffer resource.
	// Reserve the size of the resource after wiping, to avoid re-allocations on push_back.
	// Reset the buffer resource when we refresh/rescan the media.

	std::vector<PatchFile> _patch_data_usb;
	std::vector<PatchFile> _patch_data_sd;
	std::vector<PatchFile> _patch_data_nor;

	static inline const ModuleTypeSlug nullslug{""};
};
} // namespace MetaModule
