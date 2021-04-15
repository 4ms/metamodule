#pragma once
#include "conf/stream_conf.hh"
#include "drivers/dac_MCP48FVBxx.hh"
#include "drivers/dac_stream.hh"
#include "drivers/interrupt.hh"
#include "drivers/pinchange.hh"
#include "drivers/spi_transfer.hh"
#include "drivers/spi_transfer_config_struct.hh"
#include "util/circular_buffer.hh"

struct MM_DACConf : DefaultSpiTransferConf {
	struct SpiConf : DefaultSpiConf {
		static constexpr uint16_t PeriphNum = 2; // SPI2
		static constexpr uint16_t NumChips = 2;
		static constexpr IRQType IRQn = SPI2_IRQn;
		static constexpr uint16_t priority1 = 1;
		static constexpr uint16_t priority2 = 3;
		static constexpr PinNoInit SCLK = {GPIO::A, 9, LL_GPIO_AF_5};
		static constexpr PinNoInit COPI = {GPIO::B, 15, LL_GPIO_AF_5};
		static constexpr PinNoInit CIPO = {GPIO::A, 0};
		static constexpr PinNoInit CS0 = {GPIO::B, 9, 0};
		static constexpr PinNoInit CS1 = {GPIO::B, 8, 0};
		static constexpr bool use_hardware_ss = false;
		static constexpr uint16_t clock_division = 16;
		static constexpr uint16_t data_size = 24;
		static constexpr SpiDataDir data_dir = SpiDataDir::TXOnly;
		static constexpr uint8_t FifoThreshold = 1;
		static constexpr bool LSBfirst = false;
		static constexpr uint32_t NumClocksToggleSSInterData = 0;
	};
	static constexpr uint32_t NumChannelsPerChip = 2;
	using AuxPin = FPin<GPIO::E, 3, PinMode::Output>;
};

// Pin change on SAI LR clock
const PinChangeConfig DAC_update_conf = {
	.pin = 15,
	.port = GPIO::A,
	.on_rising_edge = true,
	.on_falling_edge = true,
	.priority1 = 0,
	.priority2 = 0,
};

using AnalogOutT = DacStream<mdrivlib::DacSpi_MCP48FVBxx<MM_DACConf>,
							 CircularBuffer<StreamConf::DAC::SampleT, StreamConf::DAC::BufferSize>>;
