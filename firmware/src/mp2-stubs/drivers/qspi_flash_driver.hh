#pragma once
#include "drivers/qspi_flash_struct.hh"
#include "fs/norflash_layout.hh"
#include <algorithm>
#include <array>
#include <cstdint>

// STUB: stands in for mdrivlib's QSPI NOR flash driver until the MP2 OSPI driver exists.
// Found before mdrivlib's drivers/qspi_flash_driver.hh because src/mp2-stubs is first in the M33 include path.
//
// It's a RAM-backed "flash", so LittleFS and PatchStorage work unchanged: on first boot the volume
// is formatted and the default patches are written to it. The RAM covers only the top of the
// flash map (patch volume + calibration data). It's in .noinit, so it keeps its contents if the
// M33 is restarted, but not across a power cycle.

namespace mdrivlib
{

class QSpiFlash {
public:
	enum ErasableSizes : uint32_t { SECTOR = 4096, BLOCK_32K = 32 * 1024, BLOCK_64K = 64 * 1024, ENTIRE_CHIP = 0xFFFFFFFF };
	enum UseInterruptFlags { EXECUTE_FOREGROUND, EXECUTE_BACKGROUND };

	static constexpr uint32_t RamBase = PatchVolFlashOffset;
	static constexpr uint32_t RamSize = CalDataFlashOffset + CalDataFlashSize - PatchVolFlashOffset;

	QSpiFlash(const QSPIFlashConfig &) {
	}

	bool check_chip_id(uint32_t, uint32_t) {
		return true;
	}

	bool is_ready() {
		return true;
	}

	uint32_t get_chip_size_bytes() {
		return RamBase + RamSize;
	}

	bool read(uint8_t *dst, uint32_t addr, uint32_t num_bytes, UseInterruptFlags = EXECUTE_FOREGROUND) {
		if (!in_range(addr, num_bytes))
			return false;
		std::copy_n(&ram[addr - RamBase], num_bytes, dst);
		return true;
	}

	// Like NOR flash, writing can only clear bits
	bool write(const uint8_t *src, uint32_t addr, uint32_t num_bytes) {
		if (!in_range(addr, num_bytes))
			return false;
		for (auto *dst = &ram[addr - RamBase]; num_bytes; num_bytes--)
			*dst++ &= *src++;
		return true;
	}

	bool erase(uint32_t size, uint32_t addr, UseInterruptFlags = EXECUTE_FOREGROUND) {
		if (size == ENTIRE_CHIP) {
			ram.fill(0xFF);
			return true;
		}
		addr &= ~(size - 1);
		if (!in_range(addr, size))
			return false;
		std::fill_n(&ram[addr - RamBase], size, 0xFF);
		return true;
	}

private:
	static bool in_range(uint32_t addr, uint32_t num_bytes) {
		return addr >= RamBase && num_bytes <= RamSize && (addr - RamBase) <= RamSize - num_bytes;
	}

	__attribute__((section(".noinit"))) static inline std::array<uint8_t, RamSize> ram;
};

} // namespace mdrivlib
