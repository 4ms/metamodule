#pragma once
#include "ff.h"
#include "qspi_flash_driver.hh"
#include <span>
#include <string_view>

class NorFlashFS {
public:
	enum class Status { NotInit, Connected, Disconnected };

	NorFlashFS();

	bool init();

	// Loads NOR flash contents into RAMDISK
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
	const TCHAR vol[2] = {'0', '\0'};
	mdrivlib::QSpiFlash flash;
	FATFS fs;
	Status _status = Status::NotInit;

	static void u8_to_tchar(const char *u8, TCHAR *uint) {
		do {
			*uint++ = *u8++;
		} while (*u8 != '\0');
	}
};
