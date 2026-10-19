#include "sd_test.hh"
#include "conf/sdcard_conf.hh"
#include "console.hh"
#include "drivers/pin.hh"
#include "ff.h"
#include "fs/fatfs/sdcard_ops.hh"
#include <array>

bool fatfs_register_disk(DiskOps *ops, uint8_t disk_id); // fs/fatfs/diskio.cc

namespace MetaModule
{

using M33Console::log;

namespace
{

auto &sd_card_ops() {
#ifdef MP2_TEST_CARRIER
	// Drive the common side of the detect switch low before the SD driver first reads it
	static mdrivlib::Pin detect_common{SDCardDetectCommonPin, mdrivlib::PinMode::Output};
	detect_common.low();
#endif
	static SDCardOps<SDCardConf> ops;
	return ops;
}

// FatFS write test: write 1MB with a position-dependent pattern, read back and verify, then delete.
// Each 32-bit word encodes its own offset, so misplaced or shifted data shows up as a mismatch.
void sd_write_test() {
	constexpr const char *path = "1:/mp2_write_test.bin";
	constexpr uint32_t ChunkWords = 16 * 1024; // 64kB
	constexpr uint32_t NumChunks = 16;		   // 1MB total
	static std::array<uint32_t, ChunkWords> chunk;

	auto pattern = [](uint32_t word_index) {
		return (word_index * 2654435761u) ^ 0xA5A5A5A5u;
	};

	FIL f;
	if (auto res = f_open(&f, path, FA_CREATE_ALWAYS | FA_WRITE); res != FR_OK) {
		log("  Write test: f_open for write FAILED: ", uint32_t(res), "\n");
		return;
	}

	auto start = HAL_GetTick();
	for (uint32_t c = 0; c < NumChunks; c++) {
		for (uint32_t i = 0; i < ChunkWords; i++)
			chunk[i] = pattern(c * ChunkWords + i);
		UINT written = 0;
		if (auto res = f_write(&f, chunk.data(), sizeof(chunk), &written); res != FR_OK || written != sizeof(chunk)) {
			log("  Write test: f_write FAILED: ", uint32_t(res), "\n");
			f_close(&f);
			return;
		}
	}
	if (auto res = f_close(&f); res != FR_OK) {
		log("  Write test: f_close FAILED: ", uint32_t(res), "\n");
		return;
	}
	auto write_ms = HAL_GetTick() - start;

	if (auto res = f_open(&f, path, FA_READ); res != FR_OK) {
		log("  Write test: f_open for read FAILED: ", uint32_t(res), "\n");
		return;
	}
	start = HAL_GetTick();
	uint32_t mismatches = 0;
	uint32_t first_bad_word = 0;
	for (uint32_t c = 0; c < NumChunks; c++) {
		UINT bytes_read = 0;
		if (auto res = f_read(&f, chunk.data(), sizeof(chunk), &bytes_read); res != FR_OK || bytes_read != sizeof(chunk)) {
			log("  Write test: f_read FAILED: ", uint32_t(res), "\n");
			f_close(&f);
			return;
		}
		for (uint32_t i = 0; i < ChunkWords; i++) {
			if (chunk[i] != pattern(c * ChunkWords + i)) {
				if (mismatches++ == 0)
					first_bad_word = c * ChunkWords + i;
			}
		}
	}
	auto read_ms = HAL_GetTick() - start;
	f_close(&f);

	auto unlink_res = f_unlink(path);

	if (mismatches == 0)
		log("  Write test (", path, "): OK. Wrote 1MB in ", write_ms, " ms, read back and verified in ", read_ms, " ms\n");
	else
		log("  Write test (",
			path,
			"): VERIFY FAILED: ",
			mismatches,
			" bad words, first at byte offset ",
			first_bad_word * 4,
			"\n");

	if (unlink_res != FR_OK)
		log("  f_unlink FAILED: ", uint32_t(unlink_res), "\n");
}

} // namespace

void sd_card_test() {
	auto &sd_ops = sd_card_ops();
	if (sd_ops.initialize() != 0) {
		log("M33: SD card: no card\n");
		return;
	}

	uint32_t num_sectors = 0;
	sd_ops.ioctl(GET_SECTOR_COUNT, reinterpret_cast<uint8_t *>(&num_sectors));
	log("M33: SD card: ", num_sectors / 2048, " MB\n");

	// Raw read speed: 1MB in 64kB reads
	static std::array<uint8_t, 64 * 1024> buf;
	constexpr uint32_t SectorsPerRead = buf.size() / 512;
	auto start = HAL_GetTick();
	for (uint32_t sector = 0; sector < 2048; sector += SectorsPerRead) {
		if (sd_ops.read(buf.data(), sector, SectorsPerRead) != RES_OK) {
			log("  Read FAILED at sector ", sector, "\n");
			return;
		}
	}
	log("  Read 1MB in ", HAL_GetTick() - start, " ms\n");

	// FatFS: drive "1:" is the SD card (see VolToPart in fs/fatfs/diskio.cc)
	if (!fatfs_register_disk(&sd_ops, 1)) {
		log("  fatfs_register_disk FAILED\n");
		return;
	}
	static FATFS fs;
	if (auto res = f_mount(&fs, "1:", 1); res != FR_OK) {
		log("  f_mount FAILED: ", uint32_t(res), "\n");
		return;
	}

	DIR dir;
	if (f_opendir(&dir, "1:/") != FR_OK) {
		log("  f_opendir FAILED\n");
		return;
	}
	log("  Root directory:\n");
	FILINFO info;
	unsigned count = 0;
	while (f_readdir(&dir, &info) == FR_OK && info.fname[0] != 0) {
		if (++count > 30) {
			log("    ...\n");
			break;
		}
		if (info.fattrib & AM_DIR)
			log("    [dir] ", info.fname, "\n");
		else
			log("    ", info.fname, "  (", uint32_t(info.fsize), " bytes)\n");
	}
	f_closedir(&dir);

	sd_write_test();
}

void sd_card_poll() {
	static uint32_t last_check = 0;
	static uint8_t last_present = 0xFF;

	if (HAL_GetTick() - last_check < 500)
		return;
	last_check = HAL_GetTick();

	uint8_t present = 0;
	sd_card_ops().ioctl(MMC_GET_SDSTAT, &present);
	if (present != last_present) {
		if (last_present != 0xFF)
			log(present ? "M33: SD card inserted\n" : "M33: SD card removed\n");
		last_present = present;
	}
}

} // namespace MetaModule
