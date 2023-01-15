#pragma once
#include "conf/ramdisk_conf.hh"
// #include "littlefs/norflash_lfs.hh"
#include "patches_default.hh"
#include "patchlist.hh"
#include "printf.h"
// #include "ramdisk.hh"

namespace MetaModule
{
using FileAction = std::function<void(const std::string_view filename, uint32_t timestamp, const std::span<char> data)>;

template<typename T>
concept FileIoC =
	requires(T t, const std::string_view fn, const std::span<const char> data, FileAction action, uint32_t tm) {
		{
			t.update_or_create_file(fn, data)
			} -> std::convertible_to<bool>;
		t.foreach_file_with_ext(fn, action);
		t.set_file_rawtimestamp(fn, tm);
	};

// PatchStorage transfers patches between NorFlash (littleFS) and the RamDisk (FatFS) and PatchList
class PatchStorage {
public:
	// void factory_clean();

	static bool add_to_patchlist(FileIoC auto fileio, PatchList &patch_list) {
	}
	static bool overwrite_patchlist(FileIoC auto fileio, PatchList &patch_list) {
	}

	// When going to ramdisk, we erase ramdisk first
	static bool copy_patches_from_to(FileIoC auto from, FileIoC auto to) {
		bool ok = from.foreach_file_with_ext(
			".yml",
			[&to](const std::string_view filename, uint32_t timestamp, const std::span<const char> data) {
			if (data.size() < 12 || filename.starts_with("."))
				return;

			pr_log("Found patch file in LFS: %s, timestamp 0x%x, creating on RamDisk\n", filename.data(), timestamp);

			if (to.update_or_create_file(filename.data(), data)) {
				pr_err("Could not create file %s on ram disk\n", filename.data());
				return;
			}

			to.set_file_rawtimestamp(filename.data(), timestamp);
			});

		if (!ok) {
			pr_err("NorFlashRamDiskOps init failed to read patch dir\n");
			return false;
		}
		return true;
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
	static std::vector<size_t> found_files;
	static std::array<char, 65536> buf;

	static size_t filename_hash(const std::string_view fname);
	static std::string_view trim_leading_newlines(auto s);

	static void pr_err(const char *s, auto... d) {
		printf_(s, d...);
	}
	static void pr_log(const char *s, auto... d) {
		printf_(s, d...);
	}
};
} // namespace MetaModule
