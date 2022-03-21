#pragma once
#include "ff.h"
#include "qspi_flash_driver.hh"
#include "ramdisk.hh"
#include <span>
#include <string_view>

class NorFlashFS {
public:
	static constexpr uint32_t RamDiskSizeBytes = 16 * 1024 * 1024;
	static constexpr uint32_t RamDiskBlockSize = 512;

	NorFlashFS(std::string_view vol);

	// Gets hardware ready (QSPI bus)
	bool init();

	// Initializes the ramdisk with a fatfs
	bool make_fs();

	// Loads NOR flash contents into RAMDISK
	// Does nothing is already loaded
	bool startfs();

	// Write RAMDISK to NOR flash (modified sectors only)
	void stopfs();

	void read_bytes(uint8_t *data, uint32_t address, uint32_t bytes);
	void read_sectors(uint8_t *data, uint32_t sector, uint32_t sector_count);
	void write(const uint8_t *const data, uint32_t address, uint32_t bytes);
	void write_sectors(const uint8_t *const data, uint32_t sector, uint32_t sector_count);

	enum class Status { NotInit, InUse, NotInUse };

	void set_status(Status status) {
		_status = status;
	}

	Status get_status() {
		return _status;
	}

	// Creates and writes to a file. Overwrites if existing.
	bool create_file(const char *filename, const std::span<const unsigned char> data);
	bool create_file(const char *filename, const unsigned char *data, unsigned sz);
	// struct Fil {};
	// Fil next_ext_in_dir(std::string_view ext, std::string_view path);

private:
	mdrivlib::QSpiFlash flash;
	FATFS fs;
	Status _status = Status::NotInit;
	const std::string_view vol;

	RamDisk<RamDiskSizeBytes, RamDiskBlockSize> ramdisk;
};
