#pragma once
#include "conf/sdcard_conf.hh"
#include "disk_ops.hh"
#include "drivers/sdcard.hh"

namespace MetaModule
{

template<mdrivlib::SDCardConfC ConfT>
class SDCardOps : public DiskOps {
	mdrivlib::SDCard<ConfT> sd;

public:
	enum class Status { NotInit, InUse, NotInUse, Mounted, Unmounted };

	SDCardOps() = default;

	DSTATUS status() override {
		return (_status == Status::NotInit) ? (STA_NOINIT | STA_NODISK) : 0;
	}

	Status get_status() {
		return _status;
	}

	void set_status(Status status) {
		_status = status;
	}

	// FatFS calls this :
	// - in f_mkfs(),
	// - and when it mouts the disk in f_mount(_,_,1)
	// - and the first time FatFS attempts a read/write/stat if the disk is not yet mounted
	DSTATUS initialize() override {
		if (_status == Status::NotInit) {
			sd.init();
		}
		_status = Status::NotInUse;
		return 0;
	}

	DRESULT read(uint8_t *dst, uint32_t sector_start, uint32_t num_sectors) override {
		if (!sd.detect_card()) {
			_status = Status::Unmounted;
			return RES_NOTRDY;
		}

		const uint32_t size_bytes = num_sectors * sd.BlockSize;
		auto ok = sd.read({dst, size_bytes}, sector_start);
		return ok ? RES_OK : RES_ERROR;
	}

	DRESULT write(const uint8_t *src, uint32_t sector_start, uint32_t num_sectors) override {
		if (!sd.detect_card()) {
			_status = Status::Unmounted;
			return RES_NOTRDY;
		}

		const uint32_t size_bytes = num_sectors * sd.BlockSize;
		auto ok = sd.write({src, size_bytes}, sector_start);
		return ok ? RES_OK : RES_ERROR;
	}

	DRESULT ioctl(uint8_t cmd, uint8_t *buff) override {
		switch (cmd) {
			case GET_SECTOR_SIZE: // Get R/W sector size (WORD)
				*(WORD *)buff = sd.BlockSize;
				break;
			case GET_BLOCK_SIZE: // Get erase block size in unit of sector (DWORD)
				*(DWORD *)buff = 1;
				break;
			case GET_SECTOR_COUNT: {
				uint32_t num_blocks = sd.get_card_num_blocks();
				if (!num_blocks)
					return RES_NOTRDY;
				*(DWORD *)buff = num_blocks;
			} break;
			case CTRL_SYNC:
				break;
			case CTRL_TRIM:
				break;
			case CTRL_EJECT:
				break;
		}
		return RES_OK;
	}

private:
	Status _status = Status::NotInit;
};

} // namespace MetaModule
