#pragma once
#include "fs/dir_tree.hh"
#include "patch_file.hh"
#include "util/zip.hh"
#include <algorithm>
#include <array>

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

	bool is_mounted(Volume vol) {
		return mounted[vol_idx(vol)];
	}

	void mark_mounted(Volume vol, bool status) {
		mounted[vol_idx(vol)] = status;
	}

	void clear_patches(Volume vol) {
		auto vol_num = vol_idx(vol);
		vol_root[vol_num].dirs.clear();
		vol_root[vol_num].files.clear();
	}

	std::array<PatchDir, 4> vol_root{};
	static constexpr std::array<const char *, 4> vol_name = {"Open Patches", "USB", "Card", "Internal"};
	static constexpr std::array<Volume, 4> vols{Volume::RamDisk, Volume::USB, Volume::SDCard, Volume::NorFlash};
	std::array<bool, 4> mounted{};

	static std::string_view get_vol_name(Volume vol) {
		for (auto [name, v] : zip(vol_name, vols)) {
			if (vol == v)
				return name;
		}
		return "";
	}

private:
	static unsigned vol_idx(Volume vol) {
		auto v = std::ranges::find(vols, vol);
		auto dist = std::distance(vols.begin(), v);
		int vol_num = std::clamp((int)dist, 0, (int)vols.size() - 1);
		return vol_num;
	}
};

} // namespace MetaModule
