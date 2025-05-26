#pragma once
#include "fat_file_io.hh"
#include "fs/dir_tree.hh"
#include "util/string_compare.hh"
#include "volumes.hh"
#include <algorithm>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace MetaModule
{

// given a string of comma-separated extensions, examples: ".wav, .WAV, .raw"
// creates a vector of extensions: {".wav", ".WAV", ".raw"}
std::vector<std::string> parse_extensions(std::string_view str, std::string const &delimiters = ",");

std::pair<std::string_view, Volume> split_volume(const char *filename);
std::pair<std::string_view, Volume> split_volume(std::string_view filename);

inline std::string_view volume_string(Volume vol) {
	if (vol == Volume::USB)
		return "usb:/";
	else if (vol == Volume::SDCard)
		return "sdc:/";
	else if (vol == Volume::NorFlash)
		return "nor:/";
	else if (vol == Volume::RamDisk)
		return "ram:/";
	else
		return "";
}

inline std::string make_full_path(std::string_view path, std::string_view filename = "") {
	std::string fullpath = std::string(path) + std::string("/");
	return std::filesystem::path(fullpath).lexically_normal().string() + std::string(filename);
}

inline std::string make_full_path(Volume vol, std::string_view path, std::string_view filename = "") {
	auto fullpath = std::string(volume_string(vol)) + make_full_path(path, filename);
	return std::filesystem::path(fullpath).lexically_normal().string();
}

static inline void
get_dir_entries(auto &drive, std::string_view path, std::string_view filter_exts, DirTree<FileEntry> *dir_tree) {

	auto exts = parse_extensions(filter_exts, ",");

	auto ok = drive.foreach_dir_entry(
		path, [dir_tree, &exts](std::string_view name, size_t tm, size_t size, DirEntryKind kind) {
			if (name.starts_with("."))
				return;

			if (kind == DirEntryKind::Dir) {
				dir_tree->dirs.push_back({std::string(name)});
			}

			if (kind == DirEntryKind::File) {
				if (exts.size() == 0) {
					dir_tree->files.push_back({std::string(name), (uint32_t)size, (uint32_t)tm});

				} else {
					for (auto const &ext : exts) {
						if (name.ends_with(ext)) {
							dir_tree->files.push_back({std::string(name), (uint32_t)size, (uint32_t)tm});
							pr_trace("Match: %s ends in %s\n", name.data(), ext.data());
							break;
						}
					}
					pr_trace("No match: %s\n", name.data());
				}
			}
		});

	if (ok) {
		std::ranges::sort(dir_tree->files, less_ci, &FileEntry::filename);
		std::ranges::sort(dir_tree->dirs, less_ci, &DirTree<FileEntry>::name);
	}
}

} // namespace MetaModule
