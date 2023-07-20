#pragma once
#include "lib/littlefs/lfs.h"
#include "qspi_flash_driver.hh"

// NorFlashOps is the bridge between QSPI driver and LittleFS
struct NorFlashOps {
	static constexpr uint32_t BlockSize = 4096;

	//first 8MB is for bootloader (512kB) and application (7.5MB)
	static constexpr uint32_t FlashOffset = 8 * 1024 * 1024; //0x800000;

	static int read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size) {
		uint32_t addr = block * BlockSize + off + FlashOffset;
		auto *_flash = static_cast<mdrivlib::QSpiFlash *>(c->context);
		return _flash->read((uint8_t *)buffer, addr, size) ? 0 : -1;
	}

	static int prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size) {
		uint32_t addr = block * BlockSize + off + FlashOffset;
		auto *_flash = static_cast<mdrivlib::QSpiFlash *>(c->context);
		return _flash->write((const uint8_t *)buffer, addr, size) ? 0 : -1;
	}

	static int erase(const struct lfs_config *c, lfs_block_t block) {
		uint32_t addr = block * BlockSize + FlashOffset;
		uint32_t size = mdrivlib::QSpiFlash::SECTOR;
		auto *_flash = static_cast<mdrivlib::QSpiFlash *>(c->context);
		return _flash->erase(size, addr) ? 0 : -1;
	}

	static int sync(const struct lfs_config *) {
		return 0;
	}
};
