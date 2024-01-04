#pragma once
#include "fs/fileio_t.hh"
#include "patch_convert/yaml_to_patch.hh"
#include "patch_file/patch_dir_list.hh"
#include "patches_default.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

// PatchFileIO are helpers to transfer patches between filesystems and PatchList
class PatchFileIO {

	static constexpr unsigned MaxDirRecursion = 1;

public:
	enum class FileFilter { All, NewerTimestamp };
	// void factory_clean();

	static bool read_file(std::span<char> &buffer, FileIoC auto &fileio, const std::string_view filename) {

		auto bytes_read = fileio.read_file(filename, buffer);
		if (bytes_read == 0) {
			pr_err("Error reading file %s, or file is 0 bytes\n", filename.data());
			return false;
		}
		if (bytes_read == buffer.size_bytes()) {
			pr_err("Error: File %s too large (max is %d), skipped\n", filename.data(), buffer.size_bytes());
			return false;
		}

		buffer = buffer.subspan(0, bytes_read);
		return true;
	}

	static bool write_file(std::span<const char> buffer, FileIoC auto &fileio, const std::string_view filename) {
		auto bytes_written = fileio.update_or_create_file(filename, buffer);

		if (bytes_written != buffer.size_bytes()) {
			pr_err("Error writing file %.*s\n", (int)filename.size(), filename.data());
			return false;
		}

		return true;
	}

	// Adds all files/dirs to patch_dir
	static bool add_directory(FileIoC auto &fileio, PatchDir &patch_dir, unsigned recursion_depth = 0) {
		pr_dbg("Scanning dir: '%s'\n", patch_dir.name.data());

		bool ok = fileio.foreach_dir_entry(
			patch_dir.name, [&](std::string_view entryname, uint32_t timestamp, uint32_t filesize, DirEntryKind kind) {
				std::string full_path = patch_dir.name + "/" + std::string(entryname);

				// Add dirs:
				if (kind == DirEntryKind::Dir) {
					if (entryname.starts_with("."))
						return;
					if (recursion_depth < MaxDirRecursion) {
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

		std::sort(patch_dir.files.begin(), patch_dir.files.end(), [](auto a, auto b) {
			return std::string_view{a.patchname} < std::string_view{b.patchname};
		});
		std::sort(patch_dir.dirs.begin(), patch_dir.dirs.end(), [](auto a, auto b) { return a.name < b.name; });

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
			const auto patch = DefaultPatches::get_patch(i);

			pr_trace("Creating default patch file: %s\n", filename.c_str());

			// Remove trailing null terminator that we get from storing default patches as strings
			if (patch.back() == '\0')
				patch.back() = '\n';

			if (!fileio.update_or_create_file(filename, patch)) {
				pr_err("Error: aborted creating default patches to flash\n");
				return false;
			}
		}
		return true;
	}

private:
	static ModuleTypeSlug _read_patch_name(FileIoC auto &fileio, const std::string_view filename) {
		constexpr uint32_t HEADER_SIZE = 64;
		std::array<char, HEADER_SIZE> _buf;

		auto bytes_read = fileio.read_file(filename, _buf);
		if (bytes_read == 0) {
			pr_err("Error reading file %s, or file is 0 bytes\n", filename.data());
			return "";
		}
		_buf[63] = 0;

		auto header = std::string_view{_buf.data(), _buf.size()};
		std::string_view name_tag{"patch_name"};
		auto startpos = header.find(name_tag);
		if (startpos == header.npos) {
			pr_trace("File does not contain '%s' in the first %d chars, ignoring\n", name_tag.data(), HEADER_SIZE);
			return "";
		}

		//move to the patch name
		header.remove_prefix(startpos + name_tag.length());

		//Remove leading quotes
		header.remove_prefix(std::min(header.find_first_not_of(" :'\""), header.size()));

		auto endpos = header.find_first_of("'\"\n\r");
		if (endpos == header.npos) {
			pr_dbg("File does not contain a quote or newline after '%s' in the first %d chars, ignoring\n",
				   name_tag.data(),
				   HEADER_SIZE);
			return "";
		}
		header.remove_suffix(header.size() - endpos);

		return ModuleTypeSlug{header};
	}
};
} // namespace MetaModule
