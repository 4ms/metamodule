#include "patchstorage.hh"
#include "conf/qspi_flash_conf.hh"
#include "fatfs/ramdisk_fileio.hh"
#include "patchlist.hh"
#include "printf.h"

#include <cstring>

#define pr_dbg printf_
#define pr_log printf_
#define pr_err printf_

namespace MetaModule
{

PatchStorage::PatchStorage(mdrivlib::QSpiFlash &flash)
	: lfs{flash} {
	init_norflash();
	found_files.reserve(1024);
}

void PatchStorage::factory_clean() {
	auto status = lfs.reformat();
	if (status == LittleNorFS::Status::FlashError) {
		pr_err("ERROR: NOR Flash did not init (returned wrong id)\n");
	}
	if (status == LittleNorFS::Status::LFSError) {
		pr_err("ERROR: LFS could not format and mount flash drive\n");
	}
	if (status == LittleNorFS::Status::NewlyFormatted) {
		pr_log("Formatted NOR Flash as LittleFs and now creating deFault patch files\n");
		create_default_patches_in_norflash();
	}
}

LittleNorFS::Status PatchStorage::init_norflash() {
	auto status = lfs.initialize();

	if (status == LittleNorFS::Status::FlashError) {
		pr_err("ERROR: NOR Flash did not init (returned wrong id)\n");
	}
	if (status == LittleNorFS::Status::LFSError) {
		pr_err("ERROR: LFS could not format and mount flash drive\n");
	}
	if (status == LittleNorFS::Status::NewlyFormatted) {
		pr_log("NOR Flash did not have a LittleFS, formatted and created default patch files\n");
		create_default_patches_in_norflash();
	}
	if (status == LittleNorFS::Status::AlreadyFormatted) {
		pr_log("Mounted existing LittleFS on NorFlash\n");
	}
	return status;
}

// Loads *.yml files from LittleFS/NorFlash to FatFS/RAM
bool PatchStorage::norflash_patches_to_ramdisk() {
	// Remove all RamDisk .yml files
	RamDiskFileIO::for_each_file_regex(
		Disk::RamDisk, "*.yml", [](const char *fname) { RamDiskFileIO::delete_file(fname); });

	// Scan LFS for .yml files
	bool ok = lfs.foreach_file_with_ext(
		".yml", [](const std::string_view filename, uint32_t timestamp, const std::span<const char> data) {
			if (data.size() < 12 || filename.starts_with("."))
				return;

			pr_log("Found patch file in LFS: %s, timestamp 0x%x, creating on RamDisk\n", filename.data(), timestamp);

			if (!RamDiskFileIO::create_file(filename.data(), data)) {
				pr_err("Could not create file %s on ram disk\n", filename.data());
				return;
			}

			RamDiskFileIO::set_file_rawtimestamp(filename.data(), timestamp);
		});

	if (!ok) {
		pr_err("NorFlashRamDiskOps init failed to read patch dir\n");
		return false;
	}
	return true;
}

bool PatchStorage::ramdisk_patches_to_norflash() {
	found_files.clear();

	RamDiskFileIO::for_each_file_regex(Disk::RamDisk, "*.yml", [this](const char *fname) {
		if (fname[0] == '.')
			return;

		// Record hash of filename (used later to see what files are missing, so we can delete them from LFS)
		found_files.push_back(filename_hash(std::string_view{fname}));

		// Compare to lfs file
		auto lfs_tm = lfs.get_file_timestamp(fname);
		auto fatfs_tm = RamDiskFileIO::get_file_rawtimestamp(fname);
		{
			if (lfs_tm == 0) {
				pr_log("File %s does not exist on LFS, creating\n", fname);
			} else if (lfs_tm == fatfs_tm) {
				pr_log("File %s timestamp (0x%x) not changed, skipping\n", fname, fatfs_tm);
				return;
			} else
				pr_log("File %s timestamps differ. lfs: 0x%x fatfs: 0x%x\n", fname, lfs_tm, fatfs_tm);
		}

		// Read file from FatFS
		uint32_t filesize = RamDiskFileIO::read_file(fname, buf.data(), buf.size());
		{
			if (filesize == buf.size()) {
				pr_err("File exceeds %zu bytes, too big. Skipping\r\n", buf.size());
				return;
			}
			if (!filesize) {
				pr_err("File cannot be read. Skipping\r\n");
				return;
			}
			if (!trim_leading_newlines(buf).starts_with("PatchData:")) {
				pr_log("File does not start with 'PatchData:', skipping\n");
				return;
			}
		}

		// Write to LFS
		lfs.update_or_create_file(fname, std::span<const char>{buf.data(), filesize}, fatfs_tm);
	});

	// Delete any files on LFS whose filename hashes weren't found on FatFS
	bool ok = lfs.foreach_file_with_ext(".yml", [this](std::string_view filename, uint32_t, std::span<const char>) {
		if (std::ranges::find(found_files, filename_hash(filename)) == found_files.end()) {
			pr_log("File on LFS %s not found on RamDisk, deleting\n", filename.data());
			// Think about this: dont delete, just move to RecentlyDeleted/ folder
			auto ok = lfs.delete_file(filename);
			if (!ok)
				pr_err("Deleting failed!\n");
		}
	});

	return true;
}

bool PatchStorage::create_default_patches_in_norflash() {
	for (uint32_t i = 0; i < DefaultPatches::num_patches(); i++) {
		const auto filename = DefaultPatches::get_filename(i);
		const auto patch = DefaultPatches::get_patch(i);

		pr_log("Creating default patch file: %s\n", filename.c_str());

		// Remove trailing null terminator that we get from storing default patches as strings
		if (patch.back() == '\0')
			patch.back() = '\n';

		if (!lfs.update_or_create_file(filename, patch)) {
			pr_err("Error: aborted creating default patches to flash\n");
			return false;
		}
	}
	return true;
}

bool PatchStorage::fill_patchlist_from_norflash(PatchList &patch_list) {
	patch_list.set_status(PatchList::Status::Loading);
	patch_list.clear_all_patches();

	bool ok =
		lfs.foreach_file_with_ext(".yml",
								  [&](const std::string_view fname, uint32_t timestamp, const std::span<char> data) {
		if (data.size() < 12)
			return;
		if (fname.starts_with("."))
			return;

		pr_log("Found patch file: %s, size %zu, Timestamp: 0x%x, Reading... ", fname.data(), data.size(), timestamp);

		if (!trim_leading_newlines(data).starts_with("PatchData:")) {
			pr_log("File does not start with 'PatchData:', skipping\n");
			return;
		}
		data[data.size()] = '\0';
		patch_list.add_patch_from_yaml(data);
		});

	patch_list.set_status(PatchList::Status::Ready);

	return ok;
}

size_t PatchStorage::filename_hash(const std::string_view fname) {
	unsigned int h = 2166136261;
	for (auto &c : fname)
		h = (h * 16777619) ^ c;
	return h;
}

std::string_view PatchStorage::trim_leading_newlines(auto s) {
	std::string_view v{s.data(), s.size()};
	v.remove_prefix(std::min(v.find_first_not_of("\n\r"), v.size()));
	return v;
}

} // namespace MetaModule
