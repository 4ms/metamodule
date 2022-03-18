#pragma once
#include "ff.h"
#include "qspi_flash_driver.hh"
#include <span>
#include <string_view>

class NorFlashFS {
public:
	NorFlashFS();
	void init();

	// Loads NOR flash contents into RAMDISK
	bool startfs();

	// Initializes the ramdisk with a fatfs and sample patch file
	bool make_default_fs();

	// bool create_file(const char* filename, const std::span<unsigned char> &data);
	bool create_file(const char* filename, const unsigned char *data, unsigned sz);

	//write RAMDISK to NOR flash (modified sectors only)
	void stopfs();

	struct Fil {};

	Fil next_ext_in_dir(std::string_view ext, std::string_view path);

private:
	const TCHAR vol[2] = {'0', '\0'};
	mdrivlib::QSpiFlash flash;
	FATFS *fs;

	static void u8_to_tchar(const char *u8, TCHAR *uint) {
		while (*u8) {
			*uint++ = *u8++;
		}
	}
};
