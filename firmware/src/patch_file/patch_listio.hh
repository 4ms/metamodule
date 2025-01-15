#pragma once
#include "patch_file/patch_dir_list.hh"
#include "patch_file/patch_fileio.hh"
#include <string_view>

namespace MetaModule::PatchListIO
{

inline void add_file(PatchDirList &patch_dir_list,
					 Volume vol,
					 std::string_view filename,
					 std::string_view patchname,
					 uint32_t filesize,
					 uint32_t timestamp) {

	if (filename.length() == 0)
		return;

	// TODO: extract dir from filename, set tree to that dir
	auto &tree = patch_dir_list.volume_root(vol);

	if (filename.substr(1).contains("/"))
		pr_err("Warning, adding files to subdir not supported yet\n");

	if (auto found = std::ranges::find(tree.files, filename, &PatchFile::filename); found != tree.files.end()) {
		pr_dbg("M4: file %s found, sz=%u, ts=%u, name '%s'\n", filename.data(), filesize, timestamp, patchname.data());
		found->filesize = filesize;
		found->timestamp = timestamp;
		found->patchname = patchname;
	} else {
		pr_dbg("M4: file %s added, sz=%u, ts=%u, name '%s'\n", filename.data(), filesize, timestamp, patchname.data());
		tree.files.push_back(PatchFile(filename, filesize, timestamp, patchname));
	}
}

inline bool remove_file(PatchDirList &patch_dir_list, Volume vol, std::string_view filename) {
	if (filename.length() == 0)
		return false;

	auto &tree = patch_dir_list.volume_root(vol);
	std::erase_if(tree.files, [=](auto const &file) { return file.filename == filename; });

	if (filename.substr(1).contains("/"))
		pr_err("Warning, removing files in a subdir not supported yet\n");
	return false;
}

inline PatchFile *find_fileinfo(PatchDirList &patch_dir_list, Volume vol, std::string_view filename) {
	// TODO: extract dir from filename, set tree to that dir
	auto &tree = patch_dir_list.volume_root(vol);

	if (auto found = std::ranges::find(tree.files, filename, &PatchFile::filename); found != tree.files.end()) {
		pr_dbg("M4: file %s found, sz=%u, ts=%u\n", filename.data(), found->filesize, found->timestamp);
		return &*found;
	} else {
		return nullptr;
	}
}

inline void copy_patchlist(PatchDirList *dest, PatchDirList const &src) {
	// FIXME: why does this cause memory corruption?
	// *(message.patch_dir_list) = patch_dir_list_;

	// pr_dbg("M4: Copying Patch dir list %p => %p\n", &patch_dir_list_, message.patch_dir_list);
	dest->clear_patches(Volume::USB);
	dest->clear_patches(Volume::SDCard);
	dest->clear_patches(Volume::NorFlash);

	for (auto i = 0u; auto m : src.mounted)
		dest->mounted[i++] = m;

	for (auto i = 0u; auto const &volroot : src.vol_root) {
		auto &dstroot = dest->vol_root[i++];
		dstroot.name = volroot.name;
		// pr_dbg("Vol: %s\n", dstroot.name.c_str());

		for (auto const &file : volroot.files) {
			dstroot.files.emplace_back(file.filename, file.filesize, file.timestamp, file.patchname, file.link_vol);
			// pr_dbg("%s\n", dstroot.files.back().filename.c_str());
		}

		for (auto &dir : volroot.dirs) {
			auto &dstdir = dstroot.dirs.emplace_back();
			dstdir.name = dir.name;
			// pr_dbg("Dir: %s\n", dstdir.name.c_str());

			for (auto const &file : dir.files) {
				dstdir.files.emplace_back(file.filename, file.filesize, file.timestamp, file.patchname, file.link_vol);
				// pr_dbg("  %s\n", dstdir.files.back().filename.c_str());
			}
		}
	}
	// pr_dbg("M4: Done\n");
}

} // namespace MetaModule::PatchListIO
