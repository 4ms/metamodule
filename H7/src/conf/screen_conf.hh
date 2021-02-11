#pragma once
#include "drivers/spi_screen_config_struct.hh"
#include "drivers/spi_screen_driver.hh"

constexpr struct MMScreenConf : DefaultSpiScreenConf {
	static constexpr unsigned ScreenSPIx = 6;
	static constexpr SpiConfig<ScreenSPIx> screen_SPI_conf = {
		.IRQn = SPI6_IRQn,
		.priority1 = 2,
		.priority2 = 3,

		.SCLK = {GPIO::A, 5, LL_GPIO_AF_8}, // A4 on H745 pcb
		.COPI = {GPIO::A, 7, LL_GPIO_AF_8},
		.CIPO = {GPIO::A, 0}, // unused pin
		.CS =
			{
				{GPIO::A, 4, LL_GPIO_AF_8}, // A5 on H745 pcb
			},

		.use_hardware_ss = true,
		.clock_division = 8,
		.data_size = 8,
		.data_dir = SpiDataDir::TXOnly,
	};
	using DCPin = FPin<GPIO::A, 6, PinMode::Output>;

	static constexpr uint32_t width = 240;
	static constexpr uint32_t height = 240;
} screen_conf;

using MMScreenDriverT = SpiScreenDriver<SpiConfig<MMScreenConf::ScreenSPIx>, MMScreenConf::DCPin>;
