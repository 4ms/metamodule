#pragma once
#include "drivers/qspi_flash_struct.hh"

using mdrivlib::GPIO;
using mdrivlib::PinAF;
using mdrivlib::PinNum;

constexpr mdrivlib::QSPIFlashConfig qspi_norflash_conf = {
	.io0 = {GPIO::F, PinNum::_8, PinAF::AltFunc10},
	.io1 = {GPIO::F, PinNum::_9, PinAF::AltFunc10},
	.io2 = {GPIO::F, PinNum::_7, PinAF::AltFunc9},
	.io3 = {GPIO::F, PinNum::_6, PinAF::AltFunc9},
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
