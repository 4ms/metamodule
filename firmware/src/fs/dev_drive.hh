#pragma once
#include "conf/devdrive_conf.hh"
#include "drivers/cache.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "memory/plugin_arena.hh"
#include "pr_dbg.hh"
#include <cstring>
#include <span>

namespace MetaModule
{

// Block device for the developer-mode USB drive
class DevDriveOps : public DiskOps {
public:
	void set_memory(std::span<uint8_t> mem) {
		mem_ = mem;
	}

	std::span<uint8_t> memory() const {
		return mem_;
	}

	DSTATUS status() override {
		return mem_.empty() ? (STA_NOINIT | STA_NODISK) : 0;
	}

	DSTATUS initialize() override {
		return status();
	}

	DRESULT read(uint8_t *dst, uint32_t sector_start, uint32_t num_sectors) override {
		if (auto src = sectors(sector_start, num_sectors); src.data()) {
			std::memcpy(dst, src.data(), src.size());
			return RES_OK;
		}
		return RES_ERROR;
	}

	DRESULT write(const uint8_t *src, uint32_t sector_start, uint32_t num_sectors) override {
		if (auto dst = sectors(sector_start, num_sectors); dst.data()) {
			std::memcpy(dst.data(), src, dst.size());
			return RES_OK;
		}
		return RES_ERROR;
	}

	DRESULT ioctl(uint8_t cmd, uint8_t *buff) override {
		switch (cmd) {
			case GET_SECTOR_SIZE:
				*(WORD *)buff = DevDriveBlockSize;
				break;
			case GET_BLOCK_SIZE:
				*(DWORD *)buff = 1;
				break;
			case GET_SECTOR_COUNT:
				*(DWORD *)buff = mem_.size() / DevDriveBlockSize;
				break;
			case CTRL_SYNC:
				break;
			default:
				return RES_PARERR;
		}
		return RES_OK;
	}

private:
	// The requested sectors, or an empty span with null data() if they fall
	// outside the drive.
	std::span<uint8_t> sectors(uint32_t sector_start, uint32_t num_sectors) {
		const uint32_t offset = sector_start * DevDriveBlockSize;
		const uint32_t bytes = num_sectors * DevDriveBlockSize;

		if (mem_.empty() || offset >= mem_.size() || (offset + bytes) > mem_.size()) {
			pr_err("DevDrive: access out of bounds: 0x%x + 0x%x\n", offset, bytes);
			return {};
		}

		return mem_.subspan(offset, bytes);
	}

	std::span<uint8_t> mem_{};
};

// The developer-mode USB drive, from the A7's side: claim the memory, format
// it, and hand it to (or take it back from) the M4's MSC class.
class DevDrive {
public:
	DevDrive()
		: fileio_{&ops_, Volume::DevDrive} {
	}

	bool is_enabled() const {
		return base_ != nullptr;
	}

	std::span<uint8_t> memory() const {
		return ops_.memory();
	}

	FatFileIO &files() {
		return fileio_;
	}

	// Claim the drive's memory and put an empty FAT filesystem on it
	bool enable() {
		if (is_enabled())
			return true;

		base_ = static_cast<uint8_t *>(PluginArena::alloc_aligned(DevDriveAlignment, DevDriveSizeBytes));
		if (!base_) {
			pr_err("DevDrive: could not claim %u bytes for the developer drive\n", (unsigned)DevDriveSizeBytes);
			return false;
		}

		ops_.set_memory({base_, DevDriveSizeBytes});

		if (!format()) {
			disable();
			return false;
		}

		pr_info("DevDrive: %u MB at %p\n", (unsigned)(DevDriveSizeBytes / (1024 * 1024)), (void *)base_);
		return true;
	}

	void disable() {
		if (!is_enabled())
			return;

		fileio_.unmount_drive();
		ops_.set_memory({});
		PluginArena::free(base_);
		base_ = nullptr;
	}

	void hand_to_host() {
		// TODO: may need to invalidate first
		if (is_enabled())
			mdrivlib::SystemCache::clean_dcache_by_range(base_, DevDriveSizeBytes);
	}

	void take_from_host() {
		if (is_enabled())
			mdrivlib::SystemCache::invalidate_dcache_by_range(base_, DevDriveSizeBytes);
	}

private:
	bool format() {
		if (!fileio_.format_disk()) {
			pr_err("DevDrive: failed to format\n");
			return false;
		}

		fileio_.set_label(DevDriveLabel);
		return fileio_.mount_disk();
	}

	uint8_t *base_ = nullptr;
	DevDriveOps ops_;
	FatFileIO fileio_;
};

} // namespace MetaModule
