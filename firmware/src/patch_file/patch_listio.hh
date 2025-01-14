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
	// TODO: extract dir from filename, set tree to that dir
	auto &tree = patch_dir_list.volume_root(vol);

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
	return false;
}

} // namespace MetaModule::PatchListIO
