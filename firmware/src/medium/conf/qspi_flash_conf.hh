#pragma once
#include "drivers/qspi_flash_struct.hh"

using mdrivlib::GPIO;

const mdrivlib::QSPIFlashConfig qspi_flash_conf = {
	.io0 = {GPIO::F, 8, LL_GPIO_AF_10},
	.io1 = {GPIO::F, 9, LL_GPIO_AF_10},
	.io2 = {GPIO::F, 7, LL_GPIO_AF_9},
	.io3 = {GPIO::F, 6, LL_GPIO_AF_9},
	.clk = {GPIO::F, 10, LL_GPIO_AF_9},
	.cs = {GPIO::B, 6, LL_GPIO_AF_10},

	/* QSPI freq = QUADSPICLK /(1 + ClockPrescaler) = 240 MHz/(2+1) = 80 Mhz */
	.clock_division = 9, // Todo: set this to our final chip's max
	.IRQ_pri = 2,
	.IRQ_subpri = 2,

	.flash_size_bytes = 0x0100'0000,
	.flash_size_address_bits = mdrivlib::QSPIFlashConfig::AddrBits24,

	.io_mode = mdrivlib::QSPIFlashConfig::SDR,
};
