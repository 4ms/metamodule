#pragma once
#include "conf/stream_conf.hh"
#include "drivers/dac_MCP48FVBxx.hh"
#include "drivers/dac_stream.hh"
#include "drivers/interrupt.hh"
#include "drivers/pin_change.hh"
#include "drivers/spi_transfer.hh"
#include "drivers/spi_transfer_config_struct.hh"
#include "util/circular_buffer.hh"

#if defined(STM32MP1)
	#include "a7/conf/dac_conf_target.hh"
#elif defined(STM32H7)
	#include "m7/conf/dac_conf_target.hh"
#endif

struct MM_DACConf : mdrivlib::DefaultSpiTransferConf {
	struct SpiConf : DACConfTarget {
		static constexpr uint16_t NumChips = 2;
		static constexpr uint16_t priority1 = 1;
		static constexpr uint16_t priority2 = 3;
		static constexpr bool use_hardware_ss = false;
		static constexpr uint16_t data_size = 24;
		static constexpr mdrivlib::SpiDataDir data_dir = mdrivlib::SpiDataDir::TXOnly;
		static constexpr uint8_t FifoThreshold = 1;
		static constexpr bool LSBfirst = false;
	};
	static constexpr uint32_t NumChannelsPerChip = 2;

	using AuxPin = DACConfTarget::AuxPin;

	static constexpr float scaling = 0.790336f;
};

struct DACUpdateConf : public mdrivlib::DefaultPinChangeConf {
	static constexpr uint32_t pin = DACConfTarget::SaiLRClkPin.pin;
	static constexpr GPIO port = DACConfTarget::SaiLRClkPin.gpio;
	static constexpr bool on_rising_edge = true;
	static constexpr bool on_falling_edge = true;
	static constexpr uint32_t priority1 = 0;
	static constexpr uint32_t priority2 = 0;
	static constexpr uint32_t core = DACConfTarget::CoreNum;
};

using AnalogOutT = mdrivlib::DacStream<mdrivlib::DacSpi_MCP48FVBxx<MM_DACConf>,
									   CircularBuffer<StreamConf::DAC::SampleT, StreamConf::DAC::BufferSize>>;
