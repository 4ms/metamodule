#pragma once
#include "sdram_AS4C16M16SA_7CN_conf.hh"
#include "sdram_W9825G6KH_75_conf.hh"
#include "sdram_config_struct.hh"

const SDRAMPinNames SDRAM_pin_names = {
	.A0{GPIO::F, 0, LL_GPIO_AF_12},
	.A1{GPIO::F, 1, LL_GPIO_AF_12},
	.A2{GPIO::F, 2, LL_GPIO_AF_12},
	.A3{GPIO::F, 3, LL_GPIO_AF_12},
	.A4{GPIO::F, 4, LL_GPIO_AF_12},
	.A5{GPIO::F, 5, LL_GPIO_AF_12},
	.A6{GPIO::F, 12, LL_GPIO_AF_12},
	.A7{GPIO::F, 13, LL_GPIO_AF_12},
	.A8{GPIO::F, 14, LL_GPIO_AF_12},
	.A9{GPIO::F, 15, LL_GPIO_AF_12},
	.A10{GPIO::G, 0, LL_GPIO_AF_12},
	.A11{GPIO::G, 1, LL_GPIO_AF_12},
	.A12{GPIO::G, 2, LL_GPIO_AF_12}, // not connected on PCB p2
	.BA0{GPIO::G, 4, LL_GPIO_AF_12},
	.BA1{GPIO::G, 5, LL_GPIO_AF_12},
	.D0{GPIO::D, 14, LL_GPIO_AF_12},
	.D1{GPIO::D, 15, LL_GPIO_AF_12},
	.D2{GPIO::D, 0, LL_GPIO_AF_12},
	.D3{GPIO::D, 1, LL_GPIO_AF_12},
	.D4{GPIO::E, 7, LL_GPIO_AF_12},
	.D5{GPIO::E, 8, LL_GPIO_AF_12},
	.D6{GPIO::E, 9, LL_GPIO_AF_12},
	.D7{GPIO::E, 10, LL_GPIO_AF_12},
	.D8{GPIO::E, 11, LL_GPIO_AF_12},
	.D9{GPIO::E, 12, LL_GPIO_AF_12},
	.D10{GPIO::E, 13, LL_GPIO_AF_12},
	.D11{GPIO::E, 14, LL_GPIO_AF_12},
	.D12{GPIO::E, 15, LL_GPIO_AF_12},
	.D13{GPIO::D, 8, LL_GPIO_AF_12},
	.D14{GPIO::D, 9, LL_GPIO_AF_12},
	.D15{GPIO::D, 10, LL_GPIO_AF_12},
	.NBL0{GPIO::E, 0, LL_GPIO_AF_12},
	.NBL1{GPIO::E, 1, LL_GPIO_AF_12},
	.SDCKE0{GPIO::C, 3, LL_GPIO_AF_12},
	.SDCLK{GPIO::G, 8, LL_GPIO_AF_12},
	.SDNCAS{GPIO::G, 15, LL_GPIO_AF_12},
	.SDNE0{GPIO::C, 2, LL_GPIO_AF_12},
	.SDNRAS{GPIO::F, 11, LL_GPIO_AF_12},
	.SDNWE{GPIO::C, 0, LL_GPIO_AF_12},
};

const SDRAMConfig SDRAM_AS4C_conf = {
	.pin_list = {SDRAM_pin_names},
	.timing = SDRAM_timing_AS4C16M16SA_7CN,
	.arch = SDRAM_arch_AS4C16M16SA_7CN,
	.connected_bank = 1,
};

const SDRAMConfig SDRAM_W9825_conf = {
	.pin_list = {SDRAM_pin_names},
	.timing = SDRAM_timing_W9825G6KH_75,
	.arch = SDRAM_arch_W9825G6KH_75,
	.connected_bank = 1,
};
