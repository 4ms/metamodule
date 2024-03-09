#pragma once
#include "drivers/qspi_flash_driver.hh"
#include "lib/littlefs/lfs.h"

//first 10MB is for bootloaders (512kB) and application (9.5MB)
//next 4MB is Assets (4MB is reserved for this but for now we keep the image to 2MB for faster flashing)
//last 2MB is pathches
static constexpr uint32_t AssetVolFlashOffset = 10 * 1024 * 1024; //0xA00000;
static constexpr uint32_t AssetVolFlashSize = 2 * 1024 * 1024;

static constexpr uint32_t PatchVolFlashOffset = 14 * 1024 * 1024; //0xE00000;
static constexpr uint32_t PatchVolFlashSize = 2 * 1024 * 1024;

// NorFlashOps is the bridge between QSPI driver and LittleFS
template<size_t FlashAddr, size_t FlashSize>
struct NorFlashOps {
	static constexpr uint32_t BlockSize = 4096;
	static constexpr size_t FlashOffset = FlashAddr;
	static constexpr size_t Size = FlashSize;

	static int read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size) {
		uint32_t addr = block * BlockSize + off + FlashOffset;
		auto *_flash = static_cast<mdrivlib::QSpiFlash *>(c->context);
		return _flash->read((uint8_t *)buffer, addr, size) ? 0 : -1;
	}

	static int prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size) {
		uint32_t addr = block * BlockSize + off + FlashOffset;
		if (addr < FlashOffset)
			return -1;
		auto *_flash = static_cast<mdrivlib::QSpiFlash *>(c->context);
		return _flash->write((const uint8_t *)buffer, addr, size) ? 0 : -1;
	}

	static int erase(const struct lfs_config *c, lfs_block_t block) {
		uint32_t addr = block * BlockSize + FlashOffset;
		if (addr < FlashOffset)
			return -1;
		uint32_t size = mdrivlib::QSpiFlash::SECTOR;
		auto *_flash = static_cast<mdrivlib::QSpiFlash *>(c->context);
		return _flash->erase(size, addr) ? 0 : -1;
	}

	static int sync(const struct lfs_config *) {
		return 0;
	}
};
