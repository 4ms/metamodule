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

	// void add_patch(Volume vol,
	// 			   const std::string_view filename,
	// 			   uint32_t filesize,
	// 			   uint32_t timestamp,
	// 			   StaticString<31> patchname) {

	// 	auto vol_num = std::to_underlying<Volume>(vol);
	// 	vol_root[vol_num].files.push_back({std::string{filename}, filesize, timestamp, patchname});
	// }

	// void add_dir(Volume vol, const std::string_view dirname) {
	// 	auto vol_num = std::to_underlying<Volume>(vol);
	// 	vol_root[vol_num].dirs.emplace_back(dirname);
	// }

	void clear_patches(Volume vol) {
		auto vol_num = std::to_underlying<Volume>(vol);
		vol_root[vol_num].dirs.clear();
		vol_root[vol_num].files.clear();
	}

	std::array<PatchDir, 3> vol_root{};
	std::array<StaticString<31>, 3> vol_name{{{"USB"}, {"SDCard"}, {"Internal"}}};
};

} // namespace MetaModule
