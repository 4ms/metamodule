#pragma once
#include "drivers/qspi_flash_struct.hh"

// FIXME: p1 has OSPI NOR flash, and there's no MP2 driver for it yet.
// Until then drivers/qspi_flash_driver.hh is a RAM-backed stub (src/mp2-stubs) that ignores this config.
constexpr mdrivlib::QSPIFlashConfig qspi_patchflash_conf{
	.flash_size_bytes = 0x0100'0000,
};
