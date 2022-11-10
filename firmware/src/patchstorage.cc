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

// Get the RamDisk ready for IO.
// Initializes the LittleFS driver,
// then loads *.yml files from LittleFS in NorFlash to FatFS in RAM
bool PatchStorage::norflash_patches_to_ramdisk() {

	//TODO: Remove all RamDisk patches

	bool ok = lfs.foreach_file_with_ext(".yml", [](const std::string_view filename, const std::span<const char> data) {
		if (data.size() == 0)
			return;

		printf_("Found patch file in LFS: %s, creating on RamDisk\n", filename.data());

		//TODO: verify it's a patch file
		//data.starts_with("PatchData: ");??? use PatchFileIO?

		if (!RamDiskFileIO::create_file(filename.data(), data))
			printf_("Could not create file %s on ram disk\n", filename.data());
	});

	if (!ok) {
		printf_("NorFlashRamDiskOps init failed to read patch dir\n");
		return false;
	}
	return true;
}

bool PatchStorage::ramdisk_patches_to_norflash() {
	//TODO: Remove all NorFlash patches that weren't found in RamDisk:
	// Use a custom attribute to tag all yml files on norflash.
	// As we read files on ramdisk, check if it exists: update, create
	// new files and updated files dont get the tag
	// then delete all tagged files
	// Or:
	// Read the filenames from norflash into a set or vector
	// As we iterate the files on the ramdisk, remove them from the set if present
	// Finally, iterate the remaining items
	//
	// Bonus: dont delete, just move to RecentlyDeleted/ folder

	// bool ok = lfs.foreach_file_with_ext(
	// 	".yml", [](const std::string_view filename, const std::span<const char> data) { lfs.delete_file(filename); });

	RamDiskFileIO::for_each_file_regex(Disk::RamDisk, "*.yml", [this](const char *fname) {
		std::array<char, 32768> buf;
		uint32_t filesize = RamDiskFileIO::read_file(fname, buf.data(), buf.size());
		if (filesize == buf.size()) {
			printf_("File exceeds %zu bytes, too big. Skipping\r\n", buf.size());
			return;
		}
		if (!filesize) {
			printf_("File cannot be read. Skipping\r\n");
			return;
		}
		lfs.create_file(fname, buf);
	});

	return true;
}

bool PatchStorage::create_default_patches_in_norflash() {
	for (uint32_t i = 0; i < DefaultPatches::num_patches(); i++) {
		const auto filename = DefaultPatches::get_filename(i);
		const auto patch = DefaultPatches::get_patch(i);
		printf_("Creating default patch file: %s\n", filename.c_str());
		if (!lfs.create_file(filename, patch)) {
			printf_("Error: aborted creating default patches to flash\n");
			return false;
		}
	}
	return true;
}

bool PatchStorage::fill_patchlist_from_norflash(PatchList &patch_list) {
	patch_list.set_status(PatchList::Status::Loading);
	patch_list.clear_all_patches();

	bool ok = lfs.foreach_file_with_ext(".yml", [&](const std::string_view fname, const std::span<char> data) {
		printf_("Found patch file: %s, Reading... ", fname.data());
		patch_list.add_patch_from_yaml(data);
	});

	patch_list.set_status(PatchList::Status::Ready);

	return ok;
}

} // namespace MetaModule
