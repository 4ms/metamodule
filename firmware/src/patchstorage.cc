#include "patchstorage.hh"
#include "conf/qspi_flash_conf.hh"
#include "fatfs/ramdisk_fileio.hh"
#include "patchlist.hh"
#include "printf.h"

#include <cstring>

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
		printf_("ERROR: NOR Flash did not init (returned wrong id)\n");
	}
	if (status == LittleNorFS::Status::LFSError) {
		printf_("ERROR: LFS could not format and mount flash drive\n");
	}
	if (status == LittleNorFS::Status::NewlyFormatted) {
		printf_("Formatted NOR Flash as LittleFs and now creating deFault patch files\n");
		create_default_patches_in_norflash();
	}
}

LittleNorFS::Status PatchStorage::init_norflash() {
	auto status = lfs.initialize();

	if (status == LittleNorFS::Status::FlashError) {
		printf_("ERROR: NOR Flash did not init (returned wrong id)\n");
	}
	if (status == LittleNorFS::Status::LFSError) {
		printf_("ERROR: LFS could not format and mount flash drive\n");
	}
	if (status == LittleNorFS::Status::NewlyFormatted) {
		printf_("NOR Flash did not have a LittleFS, formatted and created default patch files\n");
		create_default_patches_in_norflash();
	}
	if (status == LittleNorFS::Status::AlreadyFormatted) {
		printf_("Mounted existing LittleFS on NorFlash\n");
	}
	return status;
}

// Get the RamDisk ready for USB IO
// Loads *.yml files from LittleFS/NorFlash to FatFS/RAM
bool PatchStorage::norflash_patches_to_ramdisk() {

	// Remove all RamDisk .yml files
	RamDiskFileIO::for_each_file_regex(
		Disk::RamDisk, "*.yml", [](const char *fname) { RamDiskFileIO::delete_file(fname); });

	// Scan LFS for .yml files
	bool ok = lfs.foreach_file_with_ext(
		".yml", [](const std::string_view filename, uint32_t timestamp, const std::span<const char> data) {
			if (data.size() == 0)
				return;

			if (filename.starts_with("."))
				return;

			printf_("Found patch file in LFS: %s, timestamp 0x%x, creating on RamDisk\n", filename.data(), timestamp);

			//TODO: verify it's a patch file
			// data.starts_with("PatchData: ");??? use PatchFileIO?

			if (!RamDiskFileIO::create_file(filename.data(), data))
				printf_("Could not create file %s on ram disk\n", filename.data());

			RamDiskFileIO::set_file_rawtimestamp(filename.data(), timestamp);

			auto info = RamDiskFileIO::get_file_info(filename.data());
			RamDiskFileIO::debug_print_fileinfo(info);
		});

	if (!ok) {
		printf_("NorFlashRamDiskOps init failed to read patch dir\n");
		return false;
	}
	return true;
}

static size_t filename_hash(const std::string_view fname) {
	unsigned int h = 2166136261;
	for (auto &c : fname)
		h = (h * 16777619) ^ c;
	return h;
}

bool PatchStorage::ramdisk_patches_to_norflash() {
	found_files.clear();

	RamDiskFileIO::for_each_file_regex(Disk::RamDisk, "*.yml", [this](const char *fname) {
		if (fname[0] == '.')
			return;

		auto hsh = filename_hash(std::string_view{fname});
		found_files.push_back(hsh);
		printf_("dbg: filename %s hash 0x%08x\n", fname, hsh);

		//Compare to lfs file
		auto lfs_tm = lfs.get_file_timestamp(fname);
		auto fatfs_tm = RamDiskFileIO::get_file_rawtimestamp(fname);

		if (lfs_tm == 0) {
			printf_("File %s does not exist on LFS, creating\n", fname);
		} else if (lfs_tm == fatfs_tm) {
			printf_("File %s timestamp (0x%x) not changed, skipping\n", fname, fatfs_tm);
			return;
		} else
			printf_("File %s timestamps differ. lfs: 0x%x fatfs: 0x%x\n", fname, lfs_tm, fatfs_tm);

		uint32_t filesize = RamDiskFileIO::read_file(fname, buf.data(), buf.size());
		if (filesize == buf.size()) {
			printf_("File exceeds %zu bytes, too big. Skipping\r\n", buf.size());
			return;
		}
		if (!filesize) {
			printf_("File cannot be read. Skipping\r\n");
			return;
		}

		std::string_view data1{buf.data(), buf.size()};
		data1.remove_prefix(std::min(data1.find_first_not_of("\n\r"), data1.size()));
		if (!data1.starts_with("PatchData:")) {
			printf_("File does not start with 'PatchData:', skipping\n");
			return;
		}

		lfs.update_or_create_file(fname, std::span<const char>{buf.data(), filesize}, fatfs_tm);
	});

	bool ok = lfs.foreach_file_with_ext(
		".yml",
		[this](const std::string_view filename, uint32_t timestamp, const std::span<const char> data) {
		auto hsh = filename_hash(filename);
		if (std::find(found_files.begin(), found_files.end(), hsh) == found_files.end()) {
		if (std::ranges::find(found_files, hsh) == found_files.end()) {
			printf_("File on LFS %s with filename hash 0x%08x not found on RamDisk, deleting\n", filename.data(), hsh);
			// Think about this: dont delete, just move to RecentlyDeleted/ folder
			auto ok = lfs.delete_file(filename);
			if (!ok)
				printf_("Deleting failed!\n");
		} else
			printf_("dbg: Hash 0x%08x found, ignoring\n", hsh);
		});

	return true;
}

bool PatchStorage::create_default_patches_in_norflash() {
	for (uint32_t i = 0; i < DefaultPatches::num_patches(); i++) {
		const auto filename = DefaultPatches::get_filename(i);
		const auto patch = DefaultPatches::get_patch(i);

		printf_("Creating default patch file: %s\n", filename.c_str());
		if (!lfs.update_or_create_file(filename, patch)) {
			printf_("Error: aborted creating default patches to flash\n");
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

		printf_("Found patch file: %s, size %zu, Timestamp: 0x%x, Reading... ", fname.data(), data.size(), timestamp);

		std::string_view data1{data.data(), data.size()};
		data1.remove_prefix(std::min(data1.find_first_not_of("\n\r"), data1.size()));

		if (!data1.starts_with("PatchData:")) {
			printf_("File does not start with 'PatchData:', skipping\n");
			return;
		}
		data[data.size()] = '\0';
		patch_list.add_patch_from_yaml(data);
		});

	patch_list.set_status(PatchList::Status::Ready);

	return ok;
}

} // namespace MetaModule
