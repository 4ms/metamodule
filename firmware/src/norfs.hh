#pragma once
#include "ff.h"
#include "qspi_flash_driver.hh"
#include "ramdisk.hh"
#include <span>
#include <string_view>

//TODO: make driver-level NorFlashDiskIO
//{
//	init(); ... FatFS: disk_initialize() .. called in fdisk, mount_disk (f_mount, f_stat...)
//	mount(); ... FatFS: this is disk_intialize? called before first read (copy norfs -> ramdisk)
//	unmount(); ..FatFS: diskctl code for this? main() calls this after USBD sets NeedsWriteback flag
//	read/write() by sector USBD
// 	set/get_status? or can use mbox USBD... FatFS: disk_status() returns uint8_t
//	get block size, num blocks USBD... FatFS: disk_ioctl()
//};
//then if we switch to an SD Card for example, we can just use SDCardDiskIO
//Patchlist doesn't interact with norfs, it just can clear_patches, load_patch_From_yaml_Data
//class FileIO {
//	make_fs, create_file, read_file
//};

class NorFlashFS {
public:
	static constexpr uint32_t RamDiskSizeBytes = 16 * 1024 * 1024;
	static constexpr uint32_t RamDiskBlockSize = 512;

	NorFlashFS(std::string_view vol, RamDisk<RamDiskSizeBytes, RamDiskBlockSize> &ramdisk);

	// Gets hardware ready (QSPI bus)
	bool init();

	// Initializes the ramdisk with a fatfs
	bool make_fs();

	// Loads NOR flash contents into RAMDISK
	bool startfs();

	// Write RAMDISK to NOR flash (modified sectors only)
	bool stopfs();

	void read_bytes(uint8_t *data, uint32_t address, uint32_t bytes);
	void read_sectors(uint8_t *data, uint32_t sector, uint32_t sector_count);
	void write_bytes(const uint8_t *const data, uint32_t address, uint32_t bytes);
	void write_sectors(const uint8_t *const data, uint32_t sector, uint32_t sector_count);

	enum class Status { NotInit, InUse, NotInUse, RequiresWriteBack };

	void set_status(Status status) {
		_status = status;
	}

	Status get_status() {
		return _status;
	}

	// Creates and writes to a file. Overwrites if existing.
	bool create_file(const char *filename, const std::span<const unsigned char> data);
	bool create_file(const char *filename, const unsigned char *data, unsigned sz);

	// std::string read_file(std::string_view filename, uint32_t max_bytes = 0xFFFFFFFF);
	uint32_t read_file(std::string_view filename, char *data, uint32_t max_bytes);

	// struct Fil {};
	// Fil next_ext_in_dir(std::string_view ext, std::string_view path);

private:
	mdrivlib::QSpiFlash flash;
	FATFS fs;
	Status _status = Status::NotInit;
	const std::string_view vol;

	RamDisk<RamDiskSizeBytes, RamDiskBlockSize> &ramdisk;
};
