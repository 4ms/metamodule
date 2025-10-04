#pragma once
#include "fat_file_io.hh"

namespace MetaModule
{

class NullFatFSHost {

public:
	NullFatFSHost() {
	}

	void process() {
	}

	FatFileIO &get_fileio() {
		return sd_;
	}

	bool is_mounted() {
		return false;
	}

private:
	struct NullOps : DiskOps {
		DSTATUS status() override {
			return STA_NODISK;
		}
		DSTATUS initialize() override {
			return STA_NODISK;
		}
		DRESULT read(uint8_t *dst, uint32_t sector_start, uint32_t num_sectors) override {
			return RES_NOTRDY;
		}
		DRESULT write(const uint8_t *src, uint32_t sector_start, uint32_t num_sectors) override {
			return RES_NOTRDY;
		}
		DRESULT ioctl(uint8_t cmd, uint8_t *buff) override {
			return RES_NOTRDY;
		}
	};

	NullOps null_ops_;
	FatFileIO sd_{&null_ops_, Volume::SDCard};
};

} // namespace MetaModule
