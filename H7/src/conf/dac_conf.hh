#pragma once
#include "drivers/dac_MCP48FVB22.hh"
#include "drivers/interrupt.hh"
#include "drivers/spi_transfer.hh"
#include "drivers/spi_transfer_config_struct.hh"

struct MM_DACConf : DefaultSpiTransferConf {
	struct SpiConf : DefaultSpiConf {
		static constexpr uint16_t PeriphNum = 2; // SPI2
		static constexpr uint16_t NumChips = 1;	 // FixMe: change to 2 when done testing with one chip
		static constexpr IRQType IRQn = SPI2_IRQn;
		static constexpr uint16_t priority1 = 1;
		static constexpr uint16_t priority2 = 3;
		static constexpr PinNoInit SCLK = {GPIO::B, 13, LL_GPIO_AF_5};
		static constexpr PinNoInit COPI = {GPIO::B, 15, LL_GPIO_AF_5};
		static constexpr PinNoInit CIPO = {GPIO::A, 0};
		static constexpr PinNoInit CS0 = {GPIO::B, 12, LL_GPIO_AF_5}; // FixMe: AF should be 0 when we use 2 chips
		static constexpr PinNoInit CS1 = {GPIO::B, 11, 0};
		static constexpr bool use_hardware_ss = true; // FixMe: set to false when we use two chips
		static constexpr uint16_t clock_division = 128;
		static constexpr uint16_t data_size = 24;
		static constexpr SpiDataDir data_dir = SpiDataDir::TXOnly;
		static constexpr uint8_t FifoThreshold = 1;
		static constexpr bool LSBfirst = false;
	};
	using AuxPin = FPin<GPIO::B, 14, PinMode::Output>;
};
using AnalogOutT = DacSpi_MCP48FVB22<MM_DACConf>;

