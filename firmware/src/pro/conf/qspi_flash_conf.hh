#pragma once
#include "drivers/ospi_flash_struct.hh"

// NOR flash (W25Q128JV, 16MB) on OCTOSPI1, IO port 1. On the mp2-devboard, not the pro board.
// It's also the boot flash (see fs/norflash_layout.hh).
// Same name as MP1's config, since shared code passes it to mdrivlib::QSpiFlash (mp2-stubs/drivers/qspi_flash_driver.hh)
constexpr mdrivlib::OSPIFlashConfig qspi_patchflash_conf{
	.io0 = {mdrivlib::GPIO::D, mdrivlib::PinNum::_4, mdrivlib::PinAF::AltFunc10},
	.io1 = {mdrivlib::GPIO::D, mdrivlib::PinNum::_5, mdrivlib::PinAF::AltFunc10},
	.io2 = {mdrivlib::GPIO::D, mdrivlib::PinNum::_6, mdrivlib::PinAF::AltFunc10},
	.io3 = {mdrivlib::GPIO::D, mdrivlib::PinNum::_7, mdrivlib::PinAF::AltFunc10},
	.clk = {mdrivlib::GPIO::D, mdrivlib::PinNum::_0, mdrivlib::PinAF::AltFunc10},
	.cs = {mdrivlib::GPIO::D, mdrivlib::PinNum::_3, mdrivlib::PinAF::AltFunc10},

	.ospi_num = 1,

	// HSI 64MHz / 2 = 32MHz
	.kernel_clock = {.PLL = mdrivlib::FlexbarConf::PLLx::HSI, .findiv = 0, .prediv = 0},
	.clock_division = 2,

	.flash_size_bytes = 0x0100'0000,
	.io_mode = mdrivlib::OSPIFlashConfig::QuadSPI,
};
