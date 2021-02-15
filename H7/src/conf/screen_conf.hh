#pragma once
#include "drivers/interrupt.hh"
#include "drivers/spi_screen_config_struct.hh"
#include "drivers/spi_screen_driver.hh"

struct MMScreenConf : DefaultSpiScreenConf {
	struct ScreenSpiConf : DefaultSpiConf {
		static constexpr uint16_t PeriphNum = 6; // SPI6
		static constexpr uint16_t NumChips = 1;
		static constexpr IRQType IRQn = SPI6_IRQn;
		static constexpr uint16_t priority1 = 2;
		static constexpr uint16_t priority2 = 3;
		static constexpr PinNoInit SCLK = {GPIO::A, 5, LL_GPIO_AF_8};
		static constexpr PinNoInit COPI = {GPIO::A, 7, LL_GPIO_AF_8};
		static constexpr PinNoInit CIPO = {GPIO::A, 0};
		static constexpr PinNoInit CS0 = {GPIO::A, 4, LL_GPIO_AF_8};
		static constexpr bool use_hardware_ss = true;
		static constexpr uint16_t clock_division = 8;
		static constexpr uint16_t data_size = 8;
		static constexpr SpiDataDir data_dir = SpiDataDir::TXOnly;
	};
	using DCPin = FPin<GPIO::A, 6, PinMode::Output>;

	static constexpr uint32_t width = 240;
	static constexpr uint32_t height = 240;
	static constexpr uint32_t rowstart = 80;
	static constexpr uint32_t colstart = 0;
};

