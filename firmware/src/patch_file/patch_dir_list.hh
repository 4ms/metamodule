#pragma once
#include "CoreModules/module_type_slug.hh"
#include "fs/dir_tree.hh"
#include "patch_file.hh"
#include <algorithm>
#include <array>
#include <utility>

namespace MetaModule
{

using PatchDir = DirTree<PatchFile>;

struct PatchDirList {

	const PatchDir &volume_root(Volume vol) const {
		return vol_root[vol_idx(vol)];
	}

	PatchDir &volume_root(Volume vol) {
		return vol_root[vol_idx(vol)];
	}

	void clear_patches(Volume vol) {
		auto vol_num = vol_idx(vol);
		vol_root[vol_num].dirs.clear();
		vol_root[vol_num].files.clear();
	}

	std::array<PatchDir, 3> vol_root{};
	static constexpr std::array<const char *, 3> vol_name = {"USB", "Card", "Internal"};
	static constexpr std::array<Volume, 3> vols{Volume::USB, Volume::SDCard, Volume::NorFlash};

private:
	static unsigned vol_idx(Volume vol) {
		// for (unsigned i = 0; auto v : vols) {
		// 	if (vol == v)
		// 		return i;
		// 	i++;
		// }
		auto v = std::ranges::find(vols, vol);
		auto vol_num = std::distance(v, vols.begin());
		return std::clamp((int)vol_num, 0, (int)vols.size() - 1);
	}
};

} // namespace MetaModule
