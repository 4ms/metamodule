#pragma once
#include "dynload/plugin_file_list.hh"
#include "fs/fileio_t.hh"
#include "patch_file/patch_dir_list.hh"
#include "patches_default.hh"
#include "pr_dbg.hh"
#include "util/string_compare.hh"

namespace MetaModule
{

// PatchFileIO are helpers to transfer patches between filesystems and PatchList
class PatchFileIO {

	static constexpr unsigned MaxPatchDirRecursion = 1; // /dir/patch.yml
	static constexpr unsigned MaxAssetDirRecursion = 2; // /Brand/components/name.png

public:
	// timestamp is an out param
	static bool
	read_file(std::span<char> &buffer, FileIoC auto &fileio, const std::string_view filename, uint32_t *timestamp) {

		auto file_size = fileio.get_file_size(filename);
		*timestamp = fileio.get_file_timestamp(filename);
		if (file_size == 0) {
			pr_warn("File '%.*s' does not exist, cannot read\n", (int)filename.size(), filename.data());
		}

		if (file_size > buffer.size_bytes()) {
			pr_err("Error: File '%s' too large (max is %d), skipped\n", filename.data(), buffer.size_bytes());
			return false;
		}

		auto bytes_read = fileio.read_file(filename, buffer);
		if (bytes_read == 0) {
			pr_err("Error reading file '%s'\n", filename.data());
			return false;
		}

		buffer = buffer.subspan(0, bytes_read);
		return true;
	}

	static bool write_file(std::span<const char> buffer, FileIoC auto &fileio, const std::string_view filename) {
		if (fileio.update_or_create_file(filename, buffer)) {
			return true;
		} else {
			pr_err("Error writing file %.*s\n", (int)filename.size(), filename.data());
			return false;
		}
	}

	static bool append_file(std::span<const char> buffer, FileIoC auto &fileio, const std::string_view filename) {
		if (auto success = fileio.append_file(filename, buffer)) {
			return true;
		} else {
			pr_err("Error writing file %.*s\n", (int)filename.size(), filename.data());
			return false;
		}
	}

	// Adds all files/dirs to patch_dir
	static bool add_directory(FileIoC auto &fileio, PatchDir &patch_dir, unsigned recursion_depth = 0) {
		pr_trace("Scanning dir: '%s'\n", patch_dir.name.data());

		bool ok = fileio.foreach_dir_entry(
			patch_dir.name, [&](std::string_view entryname, uint32_t timestamp, uint32_t filesize, DirEntryKind kind) {
				std::string full_path = patch_dir.name + "/" + std::string(entryname);

				// Add dirs:
				if (kind == DirEntryKind::Dir) {
					if (entryname.starts_with("."))
						return;
					if (recursion_depth < MaxPatchDirRecursion) {
						pr_trace("Add dir: %s\n", full_path.c_str());
						patch_dir.dirs.emplace_back(full_path);
					}
				}

				// Add files:
				if (kind == DirEntryKind::File) {
					if (auto patchname = get_patchname(fileio, full_path, filesize)) {
						pr_trace("Add patch: %s\n", full_path.c_str());
						patch_dir.files.push_back(PatchFile{std::string(entryname), filesize, timestamp, *patchname});
					}
				}
			});

		if (!ok) {
			pr_err("Failed to read dir on %.32s\n", fileio.volname().data());
			return false;
		}

		for (auto &dir : patch_dir.dirs) {
			pr_trace("[%d] Entering subdir: %.*s\n", recursion_depth, dir.name.size(), dir.name.data());
			ok = add_directory(fileio, dir, recursion_depth + 1);
			if (!ok) {
				pr_err("Failed to add subdir\n");
			}
		}

		std::ranges::sort(patch_dir.files, less_ci, &PatchFile::patchname);
		std::ranges::sort(patch_dir.dirs, less_ci, &DirTree<PatchFile>::name);

		return ok;
	}

	static std::optional<ModuleTypeSlug>
	get_patchname(FileIoC auto &fileio, std::string_view entryname, uint32_t filesize) {

		if (filesize < 12) {
			return {};
		}

		if (!entryname.ends_with(".yml")) {
			return {};
		}

		// if (entryname.starts_with("."))
		// 	return {};

		auto patchname = _read_patch_name(fileio, entryname);

		if (patchname.data()[0] == 0)
			return {};

		return patchname;
	}

	static bool create_default_patches(FileIoC auto &fileio) {
		for (uint32_t i = 0; i < DefaultPatches::num_patches(); i++) {
			const auto filename = DefaultPatches::get_filename(i);
			auto patch = DefaultPatches::get_patch(i);

			pr_trace("Creating default patch file: %s\n", filename.c_str());

			// Remove trailing null terminator that we get from storing default patches as strings
			if (patch.back() == '\0')
				patch = patch.subspan(0, patch.size() - 1);

			if (!fileio.update_or_create_file(filename, patch)) {
				pr_err("Error: failed to write %d. Aborted creating default patches to flash\n", filename.c_str());
				return false;
			}
		}
		return true;
	}

	static bool
	deep_copy_dirs(FileIoC auto &fileio_from, FileIoC auto &fileio_to, std::string dir, unsigned recursion_depth = 0) {
		pr_trace("[%d] Deep copy of %s\n", recursion_depth, dir.c_str());

		bool ok = fileio_from.foreach_dir_entry(
			dir, [&](std::string_view entryname, uint32_t timestamp, uint32_t filesize, DirEntryKind kind) {
				std::string full_path = dir + "/" + std::string(entryname);

				// Copy files:
				if (kind == DirEntryKind::File) {
					if (entryname.ends_with(".so") || entryname.starts_with('.')) {
						pr_trace("Skipping file %s\n", full_path.c_str());
						return;
					}
					if (filesize > 1024 * 1024) {
						pr_warn("Skipping large file %s (%zu bytes)", full_path.c_str(), filesize);
						return;
					}

					std::vector<char> filedata(filesize);
					auto bytes_read = fileio_from.read_file(full_path, filedata);

					if (bytes_read == filesize) {
						std::string write_path = full_path.substr(PluginDirName.length() + 1);
						if (fileio_to.write_file(write_path, filedata)) {
							pr_dump("Wrote %s (%zu bytes)\n", write_path.c_str(), filesize);
						} else
							pr_err("Failed to copy file %s (%zu bytes)\n", write_path.c_str(), filesize);
					} else
						pr_err("Failed to read file %s (%zu bytes)\n", full_path.c_str(), filesize);
				}

				// Follow dirs:
				if (kind == DirEntryKind::Dir) {
					if (entryname.starts_with("."))
						return;
					if (recursion_depth < MaxAssetDirRecursion) {
						pr_trace("Entering dir: %s\n", full_path.c_str());
						ok = deep_copy_dirs(fileio_from, fileio_to, full_path, recursion_depth + 1);
					} else
						pr_warn("Found dir: %s, but recursion level is at max, ignoring\n", full_path.c_str());
				}
			});

		if (!ok)
			pr_err("Failed to read dir on %.32s\n", fileio_from.volname().data());

		return ok;
	}

	static ModuleTypeSlug extract_patch_name(std::string_view header) {
		std::string_view name_tag{"patch_name"};

		auto startpos = header.find(name_tag);
		if (startpos == header.npos) {
			pr_trace("File does not contain '%s' in the first %d chars, ignoring\n", name_tag.data(), header.size());
			return "";
		}

		//move to the patch name
		header.remove_prefix(startpos + name_tag.length());

		//Remove leading quotes
		header.remove_prefix(std::min(header.find_first_not_of(" :'\""), header.size()));

		auto endpos = header.find_first_of("'\"\n\r");
		if (endpos == header.npos) {
			pr_trace("File does not contain a quote or newline after '%s' in the first %d chars, ignoring\n",
					 name_tag.data(),
					 header.size());
			return "";
		}
		header.remove_suffix(header.size() - endpos);

		return ModuleTypeSlug{header};
	}

private:
	static ModuleTypeSlug _read_patch_name(FileIoC auto &fileio, const std::string_view filename) {
		constexpr uint32_t HEADER_SIZE = 64;
		std::array<char, HEADER_SIZE> _buf;

		auto bytes_read = fileio.read_file(filename, _buf, 0);
		if (bytes_read == 0) {
			pr_err("Error reading file %s, or file is 0 bytes\n", filename.data());
			return "";
		}
		_buf[63] = 0;

		auto header = std::string_view{_buf.data(), _buf.size()};
		return extract_patch_name(header);
	}
};
} // namespace MetaModule
