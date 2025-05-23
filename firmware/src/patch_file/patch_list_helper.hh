#pragma once
#include "patch_file/patch_dir_list.hh"
#include "pr_dbg.hh"
#include "util/string_compare.hh"
#include <string_view>

namespace MetaModule
{

class PatchListHelper {
	PatchDirList &patch_dir_list;

public:
	PatchListHelper(PatchDirList &patch_dir_list)
		: patch_dir_list{patch_dir_list} {
	}

	void
	add_file(Volume vol, std::string_view filename, std::string_view patchname, uint32_t filesize, uint32_t timestamp) {

		if (filename.length() == 0)
			return;

		auto &tree = base_dir(vol, filename);
		filename = file_name(filename);

		if (auto found = std::ranges::find(tree.files, filename, &PatchFile::filename); found != tree.files.end()) {
			pr_trace(
				"M4: file '%s' found, sz=%u, ts=%u, '%s'\n", filename.data(), filesize, timestamp, patchname.data());
			found->filesize = filesize;
			found->timestamp = timestamp;
			found->patchname = patchname;
		} else {

			pr_trace("M4: added %s, sz=%u, ts=%u, name '%s'\n", filename.data(), filesize, timestamp, patchname.data());
			auto pos = std::ranges::lower_bound(tree.files, filename, less_ci, &PatchFile::filename);
			tree.files.insert(pos, PatchFile(filename, filesize, timestamp, patchname));
		}

		// dump_patchdir();
	}

	bool remove_file(Volume vol, std::string_view filename) {
		if (filename.length() == 0)
			return false;

		auto &tree = base_dir(vol, filename);
		filename = file_name(filename);

		std::erase_if(tree.files, [=](auto const &file) { return file.filename == filename; });

		// dump_patchdir();

		return false;
	}

	PatchFile *find_patchfileinfo(Volume vol, std::string_view filename) {
		auto &tree = base_dir(vol, filename);
		filename = file_name(filename);

		if (auto found = std::ranges::find(tree.files, filename, &PatchFile::filename); found != tree.files.end()) {
			// pr_trace(
			// 	"M4 find_fileinfo: file %s found, sz=%u, ts=%u\n", filename.data(), found->filesize, found->timestamp);
			return &*found;
		} else {
			return nullptr;
		}
	}

	void copy_patchlist(PatchDirList *dest) {
		// FIXME: why does this cause memory corruption?
		// *dest = src;

		dest->clear_patches(Volume::USB);
		dest->clear_patches(Volume::SDCard);
		dest->clear_patches(Volume::NorFlash);

		for (auto i = 0u; auto m : patch_dir_list.mounted)
			dest->mounted[i++] = m;

		for (auto i = 0u; auto const &volroot : patch_dir_list.vol_root) {
			auto &dstroot = dest->vol_root[i++];
			dstroot.name = volroot.name;

			for (auto const &file : volroot.files) {
				dstroot.files.emplace_back(file.filename, file.filesize, file.timestamp, file.patchname, file.link_vol);
			}

			for (auto &dir : volroot.dirs) {
				auto &dstdir = dstroot.dirs.emplace_back();
				dstdir.name = dir.name;

				for (auto const &file : dir.files) {
					dstdir.files.emplace_back(
						file.filename, file.filesize, file.timestamp, file.patchname, file.link_vol);
				}
			}
		}
	}

	PatchDir &base_dir(Volume vol, std::string_view path) {
		auto *root = &patch_dir_list.volume_root(vol);

		// add leading slash: in MetaModule all dirs start with a slash
		std::string fullpath = (path[0] == '/') ? std::string(path) : ("/" + std::string(path));

		// extract dir name if path contains a slash
		if (auto slashpos = fullpath.find_last_of('/'); slashpos != fullpath.npos && slashpos != 0) {
			auto dir = std::string(fullpath.substr(0, slashpos));

			if (auto slashpos = dir.find_last_of('/'); slashpos != dir.npos && slashpos != 0) {
				pr_err("Error: patch files in nested subdirs are not supported\n");
			}

			auto found = std::ranges::find(root->dirs, dir, &PatchDir::name);
			if (found != root->dirs.end()) {
				root = &*found;
			}
		}

		return *root;
	}

	static std::string_view file_name(std::string_view path) {
		if (auto slashpos = path.find_last_of('/'); slashpos != path.npos) {
			return path.substr(slashpos + 1);
		} else
			return path;
	}

private:
	void dump_patchdir() {
		for (auto const &vol : patch_dir_list.vol_root) {
			pr_dbg("\nVolume: %s:\n", vol.name.c_str());

			for ([[maybe_unused]] auto const &f : vol.files) {
				pr_dbg(" %s\n", f.filename.c_str());
			}

			for (auto const &d : vol.dirs) {
				pr_dbg(" %s (dir):\n", d.name.c_str());

				for ([[maybe_unused]] auto const &f : d.files) {
					pr_dbg("  %s\n", f.filename.c_str());
				}
			}
		}
	}
};

} // namespace MetaModule
