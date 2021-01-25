#pragma once
#include "drivers/adc_spi_max11666.hh"
#include "drivers/analog_in_ext.hh"
#include "drivers/dma_config_struct.hh"
#include "drivers/pin.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"

struct MetaModuleControls {};

const SpiConfig<2> spi_adc_conf = {
	.spi = SPI1,
	.IRQn = SPI1_IRQn,
	// .pins =
	// 	{
	.SCLK = {GPIO::G, 11}, // Todo: add alt func
	.COPI = {GPIO::D, 7},
	.CIPO = {GPIO::G, 9},
	.CS =
		{
			{GPIO::G, 10},
			{GPIO::G, 12},
		},
	// },
	// .num_chips = 2,
	// .chans_per_chip = 2,
	// .change_channel_commands = {0x00FF, 0xFF00},
	// .continue_channel_commands = {0xFFFF, 0x0000},
};

const TimekeeperConfig control_read_tim_conf = {
	.TIMx = TIM6,
	.period_ns = 100000, // 10kHz
	.priority1 = 0,
	.priority2 = 0,
};
