#pragma once
#include "drivers/pin.hh"
#include "drivers/spi_config_struct.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"

constexpr unsigned kSpiAdcConfPeriphNum = 1;
constexpr unsigned kSpiAdcConfNumChips = 2;
constexpr SpiConfig<kSpiAdcConfPeriphNum, kSpiAdcConfNumChips> spi_adc_conf = {
	.IRQn = SPI1_IRQn,
	.priority1 = 0,
	.priority2 = 1,

	.SCLK = {GPIO::G, 11, LL_GPIO_AF_5},
	.COPI = {GPIO::D, 7, LL_GPIO_AF_5},
	.CIPO = {GPIO::G, 9, LL_GPIO_AF_5},
	.CS =
		{
			{GPIO::G, 10},
			{GPIO::G, 12},
		},

	.use_hardware_ss = false,
	.clock_division = 8,
	//.data_size

};

const TimekeeperConfig control_read_tim_conf = {
	.TIMx = TIM6,
	.period_ns = 100000, // 10kHz
	.priority1 = 0,
	.priority2 = 0,
};

