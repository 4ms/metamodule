#pragma once
#include "drivers/adc_spi_max11666.hh"
#include "drivers/analog_in_ext.hh"
// #include "drivers/dma_config_struct.hh"
#include "drivers/pin.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"

struct MetaModuleControls {};

constexpr unsigned spi_adc_conf_periphnum = 1;
constexpr unsigned spi_adc_conf_numchips = 2;
constexpr SpiConfig<spi_adc_conf_periphnum, spi_adc_conf_numchips> spi_adc_conf = {
	.IRQn = SPI1_IRQn,
	// Toto:
	//.priority1 = 0,
	//.priority2 = 1,

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
