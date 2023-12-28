#pragma once
#include "CoreModules/module_type_slug.hh"
#include "patch_dir.hh"
#include <array>
#include <utility>

namespace MetaModule
{

struct PatchDirList {

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
