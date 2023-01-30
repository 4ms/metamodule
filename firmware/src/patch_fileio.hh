#pragma once
#include "fileio_t.hh"
#include "patches_default.hh"
#include "patchlist.hh"
#include "printf.h"

namespace MetaModule
{

// PatchFileIO are helpers to transfer patches between filesystems and PatchList
class PatchFileIO {
public:
	// void factory_clean();

	static bool add_to_patchlist(FileIoC auto fileio, PatchList &patch_list) {
		patch_list.set_status(PatchList::Status::Loading);

		bool ok = fileio.foreach_file_with_ext(
			".yml",
			[&fileio, &patch_list](const std::string_view filename, uint32_t timestamp, uint32_t filesize) {
			if (filesize < 12 || filename.starts_with("."))
				return;

			pr_log("Found patch file: %s (%zuB) Timestamp: 0x%x, Reading... ", filename.data(), filesize, timestamp);

			if (!_read_patch_to_local_buffer(fileio, filename, filesize))
				return;

			buf[buf.size() - 1] = '\0';

			patch_list.add_patch_from_yaml(buf);
			});

		patch_list.set_status(PatchList::Status::Ready);

		if (!ok)
			pr_log("Failed to read patches on %s\n", fileio.volname().data());
		return ok;
	}

	static bool overwrite_patchlist(FileIoC auto fileio, PatchList &patch_list) {
		patch_list.clear_all_patches();
		return add_to_patchlist(fileio, patch_list);
	}

	static bool delete_all_patches(FileIoC auto fileio) {
		return fileio.foreach_file_with_ext(
			".yml", [&fileio](const std::string_view filename, uint32_t timestamp, uint32_t filesize) {
				fileio.delete_file(filename);
			});
	}

	// NOTE/TODO: When going from NORFS to ramdisk, we need to erase ramdisk first
	// Copies patch yml files from one FS to another.
	// If a file with the same name exists, it is silently overwritten.
	static bool copy_patches_from_to(FileIoC auto from, FileIoC auto to) {
		bool ok = from.foreach_file_with_ext(
			".yml", [&from, &to](const std::string_view filename, uint32_t timestamp, uint32_t filesize) {
				if (filesize < 12 || filename.starts_with("."))
					return;

				pr_log("Found patch file: %s, size: %d, timestamp 0x%x, creating on RamDisk\n",
					   filename.data(),
					   filesize,
					   timestamp);

				if (!_read_patch_to_local_buffer(from, filename, filesize))
					return;

				if (to.update_or_create_file(filename, buf)) {
					pr_err("Could not create file %s on ram disk\n", filename.data());
					return;
				}

				to.set_file_timestamp(filename, timestamp);
			});

		if (!ok) {
			pr_err("PatchStorage failed to copy patches on %s.\n", from.volname().data());
			return false;
		}
		return true;
	}

	// Updates patch yml files from one FS to another.
	// If a file with the same name exists, it is overwritten only if the timestamp differs (??is older??)
	static bool copy_new_patches_from_to(FileIoC auto from, FileIoC auto to) {
		bool ok = from.foreach_file_with_ext(
			".yml",
			[&from, &to](const std::string_view filename, uint32_t timestamp, uint32_t filesize) {
			if (filesize < 12 || filename.starts_with("."))
				return;

			{
				auto to_file_tmstmp = to.get_file_timestamp(filename);
				if (to_file_tmstmp == 0) {
					pr_log("File %s does not exist on dest FS, creating\n", filename.data());
				} else if (to_file_tmstmp == timestamp) {
					pr_log("File %s timestamp (0x%x) not changed, skipping\n", filename.data(), timestamp);
					return;
				} else
					pr_log(
						"File %s timestamps differ. from: 0x%x to: 0x%x\n", filename.data(), timestamp, to_file_tmstmp);
			}

			if (!_read_patch_to_local_buffer(from, filename, filesize))
				return;

			if (to.update_or_create_file(filename, buf)) {
				pr_err("Could not create file %s on ram disk\n", filename.data());
				return;
			}

			to.set_file_timestamp(filename, timestamp);
			});

		if (!ok) {
			pr_err("PatchStorage failed to copy patches.\n");
			return false;
		}
		return true;
	}

	// Delete all patch files on a FS which are not present on a reference FS
	static bool remove_patch_files_not_matching(FileIoC auto reference, FileIoC auto fileio) {
		bool ok = reference.foreach_file_with_ext(
			".yml", [&reference, &fileio](const std::string_view filename, uint32_t timestamp, uint32_t filesize) {
				//TODO: use get_file_info since timestamp might not be working on LFS since it's a custom attribute?
				auto tm = fileio.get_file_timestamp(filename);
				if (tm == 0)
					fileio.delete_file(filename);
			});
		return ok;
	}

	static bool create_default_patches(FileIoC auto fileio) {
		for (uint32_t i = 0; i < DefaultPatches::num_patches(); i++) {
			const auto filename = DefaultPatches::get_filename(i);
			const auto patch = DefaultPatches::get_patch(i);

			pr_log("Creating default patch file: %s\n", filename.c_str());

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
	// static std::vector<size_t> found_files;
	static std::array<char, 65536> buf;

	static size_t filename_hash(const std::string_view fname) {
		unsigned int h = 2166136261;
		for (auto &c : fname)
			h = (h * 16777619) ^ c;
		return h;
	}

	static std::string_view trim_leading_newlines(auto s) {
		std::string_view v{s.data(), s.size()};
		v.remove_prefix(std::min(v.find_first_not_of("\n\r"), v.size()));
		return v;
	}

	// FIXME: uses static buffer, NOT THREAD OR ISR SAFE!!
	static bool _read_patch_to_local_buffer(FileIoC auto fileio, const std::string_view filename, uint32_t filesize) {

		auto bytes_read = fileio.read_file(filename, buf);
		if (bytes_read == 0) {
			pr_err("Error reading file %s, or file is 0 bytes\n", filename.data());
			return false;
		}
		if (bytes_read < filesize) {
			pr_err("Error: File %s too large (%d, max is %d), skipped\n", filename.data(), filesize, sizeof(buf));
			return false;
		}
		if (!trim_leading_newlines(buf).starts_with("PatchData:")) {
			pr_log("File does not start with 'PatchData:', skipping\n");
			return false;
		}
		return true;
	}

	static void pr_err(const char *s, auto... d) {
		printf_(s, d...);
	}
	static void pr_log(const char *s, auto... d) {
		printf_(s, d...);
	}
};
} // namespace MetaModule
