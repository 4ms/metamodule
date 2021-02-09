#pragma once
#include "drivers/adc_spi_max11666.hh"
#include "drivers/pin.hh"
#include "drivers/spi_config_struct.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"
#include "util/filter.hh"

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
	.clock_division = 64,
	.data_size = 16,
	.data_dir = SpiDataDir::Duplex,
};

// Todo: try using this instead of the above
struct SpiAdcConf : DefaultSpiConf {
	static constexpr uint16_t PeriphNum = 1; // SPI1
	static constexpr uint16_t NumChips = 2;
	static constexpr uint16_t IRQn = SPI1_IRQn;
	static constexpr uint16_t priority1 = 0;
	static constexpr uint16_t priority2 = 1;
	static constexpr PinNoInit SCLK = {GPIO::G, 11, LL_GPIO_AF_5};
	static constexpr PinNoInit COPI = {GPIO::D, 7, LL_GPIO_AF_5};
	static constexpr PinNoInit CIPO = {GPIO::G, 9, LL_GPIO_AF_5};
	static constexpr PinNoInit CS[2] = {
		{GPIO::G, 10},
		{GPIO::G, 12},
	};
	static constexpr bool use_hardware_ss = false;
	static constexpr uint16_t clock_division = 64;
	static constexpr uint16_t data_size = 16;
	static constexpr SpiDataDir data_dir = SpiDataDir::Duplex;
};

const TimekeeperConfig control_read_tim_conf = {
	.TIMx = TIM6,
	.period_ns = 100000, // 10kHz
	.priority1 = 0,
	.priority2 = 0,
};

using CVAdcChipT = AdcSpi_MAX11666<SpiConfig<spi_adc_conf.PeriphNum, spi_adc_conf.NumChips>, Oversampler<16>>;
