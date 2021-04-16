#pragma once
#include "conf/stream_conf.hh"
#include "drivers/dac_MCP48FVBxx.hh"
#include "drivers/dac_stream.hh"
#include "drivers/interrupt.hh"
#include "drivers/pinchange.hh"
#include "drivers/spi_transfer.hh"
#include "drivers/spi_transfer_config_struct.hh"
#include "util/circular_buffer.hh"

#ifdef STM32H7
	#include "m7/conf/dac_conf_target.hh"
#elif defined(STM32MP1)
	#include "a7/conf/dac_conf_target.hh"
#endif

struct MM_DACConf : DefaultSpiTransferConf {
	struct SpiConf : DACConfTarget {
		static constexpr uint16_t PeriphNum = 2;
		static constexpr uint16_t NumChips = 2;
		static constexpr IRQType IRQn = SPI2_IRQn;
		static constexpr uint16_t priority1 = 1;
		static constexpr uint16_t priority2 = 3;
		static constexpr PinNoInit SCLK = {GPIO::B, 13, LL_GPIO_AF_5};
		static constexpr PinNoInit COPI = {GPIO::B, 15, LL_GPIO_AF_5};
		static constexpr PinNoInit CIPO = {GPIO::A, 0};
		static constexpr PinNoInit CS0 = {GPIO::B, 12, 0};
		static constexpr PinNoInit CS1 = {GPIO::B, 11, 0};
		static constexpr bool use_hardware_ss = false;
		static constexpr uint16_t clock_division = 16;
		static constexpr uint16_t data_size = 24;
		static constexpr SpiDataDir data_dir = SpiDataDir::TXOnly;
		static constexpr uint8_t FifoThreshold = 1;
		static constexpr bool LSBfirst = false;
		static constexpr uint32_t NumClocksToggleSSInterData = 0;
	};
	static constexpr uint32_t NumChannelsPerChip = 2;

	using AuxPin = DACConfTarget::AuxPin; // FPin<GPIO::B, 14, PinMode::Output>;
};

const PinChangeConfig DAC_update_conf = {
	.pin = DACConfTarget::SaiLRClkPin.pin,
	.port = DACConfTarget::SaiLRClkPin.gpio,
	.on_rising_edge = true,
	.on_falling_edge = true,
	.priority1 = 0,
	.priority2 = 0,
};

using AnalogOutT = DacStream<mdrivlib::DacSpi_MCP48FVBxx<MM_DACConf>,
							 CircularBuffer<StreamConf::DAC::SampleT, StreamConf::DAC::BufferSize>>;
