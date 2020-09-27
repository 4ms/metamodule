#pragma once
#include "qspi_flash_struct.hh"

const QSPIFlashConfig qspi_flash_conf = {
	.io0 = {GPIO::F, 8, LL_GPIO_AF_10},
	.io1 = {GPIO::F, 9, LL_GPIO_AF_10},
	.io2 = {GPIO::F, 7, LL_GPIO_AF_9},
	.io3 = {GPIO::F, 6, LL_GPIO_AF_9},
	.clk = {GPIO::B, 2, LL_GPIO_AF_9},
	.cs = {GPIO::B, 6, LL_GPIO_AF_10},
};

