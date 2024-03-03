#pragma once
#include "CoreModules/module_type_slug.hh"
#include "fs/dir_tree.hh"
#include "patch_file.hh"
#include <array>
#include <utility>

namespace MetaModule
{

using PatchDir = DirTree<PatchFile>;

struct PatchDirList {

	const PatchDir &volume_root(Volume vol) const {
		auto vol_num = static_cast<std::underlying_type_t<Volume>>(vol);
		return vol_root[vol_num];
	}

	PatchDir &volume_root(Volume vol) {
		auto vol_num = static_cast<std::underlying_type_t<Volume>>(vol);
		return vol_root[vol_num];
	}

	void clear_patches(Volume vol) {
		auto vol_num = static_cast<std::underlying_type_t<Volume>>(vol);
		vol_root[vol_num].dirs.clear();
		vol_root[vol_num].files.clear();
	}

	std::array<PatchDir, 3> vol_root{};
	static constexpr std::array<const char *, 3> vol_name = {"USB", "Card", "Internal"};
	static constexpr std::array<Volume, 3> vols{Volume::USB, Volume::SDCard, Volume::NorFlash};
};

} // namespace MetaModule
