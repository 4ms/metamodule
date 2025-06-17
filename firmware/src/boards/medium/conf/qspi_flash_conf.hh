#pragma once
#include "drivers/qspi_flash_struct.hh"

using mdrivlib::GPIO;
using mdrivlib::PinAF;
using mdrivlib::PinNum;

constexpr mdrivlib::QSPIFlashConfig qspi_patchflash_conf = {
	.io0 = {GPIO::F, PinNum::_8, PinAF::AltFunc10},
	.io1 = {GPIO::F, PinNum::_9, PinAF::AltFunc10},
	.io2 = {GPIO::F, PinNum::_7, PinAF::AltFunc9},
	.io3 = {GPIO::A, PinNum::_1, PinAF::AltFunc9},
	.clk = {GPIO::F, PinNum::_10, PinAF::AltFunc9},
	.cs = {GPIO::B, PinNum::_6, PinAF::AltFunc10},

	/* QSPI freq = QUADSPICLK /(1 + ClockPrescaler) = 266 MHz/(2+1) = 88 Mhz */
	.clock_division = 3,
	.IRQ_pri = 2,
	.IRQ_subpri = 2,

	.flash_size_bytes = 0x0100'0000,
	.flash_size_address_bits = mdrivlib::QSPIFlashConfig::AddrBits24,

	.chip_id = mdrivlib::QSPIFlashConfig::W25Q128JV,

	.io_mode = mdrivlib::QSPIFlashConfig::IOMode::QuadSPI,

	.bank = mdrivlib::QSPIFlashConfig::Bank1,
};

// constexpr mdrivlib::QSPIFlashConfig qspi_flash_conf = {
// 	.io0 = {GPIO::H, PinNum::_2, PinAF::AltFunc9},
// 	.io1 = {GPIO::H, PinNum::_3, PinAF::AltFunc9},
// 	.io2 = {GPIO::Unused, PinNum::_0},
// 	.io3 = {GPIO::Unused, PinNum::_0},
// 	.clk = {GPIO::F, PinNum::_10, PinAF::AltFunc9},
// 	.cs = {GPIO::C, PinNum::_0, PinAF::AltFunc10},

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
