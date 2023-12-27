#pragma once
#include "CoreModules/module_type_slug.hh"
#include "patch_dir.hh"
#include <array>
#include <utility>

namespace MetaModule
{

struct PatchDirList {

	PatchDir &volume_root(Volume vol) {
		auto vol_num = std::to_underlying<Volume>(vol);
		return vol_root[vol_num];
	}

	void clear_patches(Volume vol) {
		auto vol_num = std::to_underlying<Volume>(vol);
		vol_root[vol_num].dirs.clear();
		vol_root[vol_num].files.clear();
	}

	std::array<PatchDir, 3> vol_root{};
	std::array<StaticString<31>, 3> vol_name{{{"USB"}, {"SDCard"}, {"Internal"}}};
	std::array<Volume, 3> vols{Volume::USB, Volume::SDCard, Volume::NorFlash};
};

} // namespace MetaModule
