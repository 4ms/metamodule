#pragma once
#include "drivers/adc_spi_max11666.hh"
#include "drivers/interrupt.hh"
#include "drivers/spi_config_struct.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"
#include "util/filter.hh"

struct SpiAdcConf : DefaultSpiConf {
	static constexpr uint16_t PeriphNum = 1; // SPI1
	static constexpr uint16_t NumChips = 2;
	static constexpr IRQType IRQn = SPI1_IRQn;
	static constexpr uint16_t priority1 = 0;
	static constexpr uint16_t priority2 = 1;
	static constexpr PinNoInit SCLK = {GPIO::G, 11, LL_GPIO_AF_5};
	static constexpr PinNoInit COPI = {GPIO::D, 7, LL_GPIO_AF_5};
	static constexpr PinNoInit CIPO = {GPIO::G, 9, LL_GPIO_AF_5};
	static constexpr PinNoInit CS0 = {GPIO::G, 10};
	static constexpr PinNoInit CS1 = {GPIO::G, 12};
	static constexpr bool use_hardware_ss = false;
	static constexpr uint16_t clock_division = 16;
	// Todo: was 480Mhz/16 = 30MHz. Changed to 320MHz/16 = 20MHz. Can we go to 320/8 = 40MHZ?
	static constexpr uint16_t data_size = 16;
	static constexpr SpiDataDir data_dir = SpiDataDir::Duplex;
	static constexpr uint8_t FifoThreshold = 1;
	static constexpr bool LSBfirst = false;
};

using CVAdcChipT = mdrivlib::AdcSpi_MAX11666<SpiAdcConf, Oversampler<8>>;

const TimekeeperConfig cvadc_tim_conf = {
	.TIMx = TIM17,
	.period_ns = 71000, // 14khz
	.priority1 = 0,
	.priority2 = 1,
};
