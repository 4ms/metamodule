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

// give a file path, returns {"usb:", "subdir/patch.yml"}
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

constexpr auto volume_labels = std::array{
	std::pair<std::string_view, Volume>{{"ram:"}, {Volume::RamDisk}},
	std::pair<std::string_view, Volume>{{"usb:"}, {Volume::USB}},
	std::pair<std::string_view, Volume>{{"sdc:"}, {Volume::SDCard}},
	std::pair<std::string_view, Volume>{{"nor:"}, {Volume::NorFlash}},
	// Alternative labels:
	std::pair<std::string_view, Volume>{{"USB:"}, {Volume::USB}},
	std::pair<std::string_view, Volume>{{"SD Card:"}, {Volume::SDCard}},
	std::pair<std::string_view, Volume>{{"Internal:"}, {Volume::NorFlash}},
};

constexpr Volume string_to_volume(std::string_view str) {
	for (auto const &label : volume_labels) {
		if (str.starts_with(label.first)) {
			return label.second;
		}
	}
	return Volume::MaxVolumes;
}

// Joins a dir and a file name on a volume (without the volume prefix) and cleans
// up the result. As with "/.." in POSIX, ".." at the volume root stays at the root.
// A relative dir gives a relative result: ("dir" -> "dir/file")
// Empty or absolute dir gives an absolute result: ("" -> "/file").
inline std::string make_full_path(std::string_view path, std::string_view filename) {
	// Check if it has a leading slash (we treat "" as "/")
	bool relative = !path.empty() && !path.starts_with('/');

	// Remove all leading slashes
	while (path.starts_with('/'))
		path.remove_prefix(1);

	// Make sure `path` has a slash before and after
	auto fullpath = "/" + std::string(path);
	if (!fullpath.ends_with('/'))
		fullpath += '/';
	// Append the filename
	fullpath += filename;
	// Normalize
	auto normal = std::filesystem::path(fullpath).lexically_normal().string();

	// Remove the leading slash if we passed in a relative path
	if (relative && normal.size() > 1)
		normal.erase(0, 1);
	return normal;
}

// Cleans up the path. As with "/.." in POSIX, ".." at the volume root stays at
// the root, so the result always starts with the volume prefix (which FatFS
// needs to pick the drive)
inline std::string make_full_path(Volume vol, std::string_view path) {
	auto vol_str = volume_string(vol);
	if (vol_str.empty())
		return std::filesystem::path(path).lexically_normal().string();

	// Normalize the path as an absolute one, which can't go above its root.
	// Strip its own leading slashes first: on Windows (simulator), "//x" is a network path
	while (path.starts_with('/'))
		path.remove_prefix(1);
	auto rooted = std::filesystem::path("/" + std::string(path)).lexically_normal().string();

	// "sdc:/" + "/dir/file" would double the slash, so drop the one from the prefix
	vol_str.remove_suffix(1);
	return std::string(vol_str) + rooted;
}

// Cleans up the path. ".." at the volume root stays at the root
inline std::string make_full_path(Volume vol, std::string_view path, std::string_view filename) {
	return make_full_path(vol, make_full_path(path, filename));
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
