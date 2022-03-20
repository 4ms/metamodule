#pragma once
#include "ff.h"
#include "qspi_flash_driver.hh"
#include <span>
#include <string_view>


class NorFlashFS {
public:
	enum class Status { NotInit, InUse, NotInUse };

	NorFlashFS(std::string_view vol);

	bool init();

	// Loads NOR flash contents into RAMDISK
	// Does nothing is already loaded
	bool startfs();

	// Initializes the ramdisk with a fatfs
	bool make_fs();

	// Creates and writes to a file. Overwrites if existing.
	bool create_file(const char *filename, const std::span<const unsigned char> data);
	bool create_file(const char *filename, const unsigned char *data, unsigned sz);

	// Write RAMDISK to NOR flash (modified sectors only)
	void stopfs();

	void read_raw_ramdisk(uint32_t address, uint32_t bytes, const uint8_t *data);
	void write_raw_ramdisk(uint32_t address, uint32_t bytes, const uint8_t *const data);

	void set_status(Status status) {
		_status = status;
	}

	Status get_status() {
		return _status;
	}

	// struct Fil {};
	// Fil next_ext_in_dir(std::string_view ext, std::string_view path);

private:
	mdrivlib::QSpiFlash flash;
	FATFS fs;
	Status _status = Status::NotInit;
	const std::string_view vol;

	//TODO: added a 16MB RamDisk member

};

