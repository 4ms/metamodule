#pragma once
#include "drivers/qspi_flash_struct.hh"

using mdrivlib::GPIO;

constexpr mdrivlib::QSPIFlashConfig qspi_patchflash_conf = {
	.io0 = {GPIO::F, 8, LL_GPIO_AF_10},
	.io1 = {GPIO::F, 9, LL_GPIO_AF_10},
	.io2 = {GPIO::F, 7, LL_GPIO_AF_9},
	.io3 = {GPIO::A, 1, LL_GPIO_AF_9},
	.clk = {GPIO::F, 10, LL_GPIO_AF_9},
	.cs = {GPIO::B, 6, LL_GPIO_AF_10},

	/* QSPI freq = QUADSPICLK /(1 + ClockPrescaler) = 240 MHz/(2+1) = 80 Mhz */
	.clock_division = 2,
	.IRQ_pri = 2,
	.IRQ_subpri = 2,

	.flash_size_bytes = 0x0100'0000,
	.flash_size_address_bits = mdrivlib::QSPIFlashConfig::AddrBits24,

	.chip_id = mdrivlib::QSPIFlashConfig::S25FLxxxL,

	.io_mode = mdrivlib::QSPIFlashConfig::QuadSPI,

	.bank = mdrivlib::QSPIFlashConfig::Bank1,
};

// constexpr mdrivlib::QSPIFlashConfig qspi_flash_conf = {
// 	.io0 = {GPIO::H, 2, LL_GPIO_AF_9},
// 	.io1 = {GPIO::H, 3, LL_GPIO_AF_9},
// 	.io2 = {GPIO::Unused, 0},
// 	.io3 = {GPIO::Unused, 0},
// 	.clk = {GPIO::F, 10, LL_GPIO_AF_9},
// 	.cs = {GPIO::C, 0, LL_GPIO_AF_10},

// 	/* QSPI freq = QUADSPICLK /(1 + ClockPrescaler) = 240 MHz/(2+1) = 80 Mhz */
// 	.clock_division = 2,
// 	.IRQ_pri = 2,
// 	.IRQ_subpri = 2,

// 	.flash_size_bytes = 0x0100'0000,
// 	.flash_size_address_bits = mdrivlib::QSPIFlashConfig::AddrBits24,

// 	.chip_id = mdrivlib::QSPIFlashConfig::S25FLxxxL,

// 	.io_mode = mdrivlib::QSPIFlashConfig::SingleSPI,

// 	.bank = mdrivlib::QSPIFlashConfig::Bank2,
// };
