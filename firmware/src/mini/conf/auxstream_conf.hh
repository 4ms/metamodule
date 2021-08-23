#pragma once
#include "conf/stream_conf.hh"
#include "drivers/dac_MCP48FVBxx.hh"
#include "drivers/dac_stream.hh"
#include "drivers/pin_change_conf.hh"
#include "drivers/spi_transfer.hh"
#include "drivers/spi_transfer_config_struct.hh"
#include "util/circular_buffer.hh"

#if defined(STM32MP1)
	#include "a7/conf/dac_conf_target.hh"
#elif defined(STM32H7)
	#include "m7/conf/dac_conf_target.hh"
#endif

namespace MetaModule
{

struct AuxStreamFrame {
	std::array<uint32_t, 1> gate_out;
	uint32_t dac1;
	uint32_t dac2;
};

struct AuxStreamUpdateConf : public mdrivlib::DefaultPinChangeConf {
	static constexpr uint32_t pin = DACConfTarget::SaiLRClkPin.pin;
	static constexpr GPIO port = DACConfTarget::SaiLRClkPin.gpio;
	static constexpr bool on_rising_edge = true;
	static constexpr bool on_falling_edge = true;
	static constexpr uint32_t priority1 = 0;
	static constexpr uint32_t priority2 = 0;
	static constexpr uint32_t core = DACConfTarget::CoreNum;
};

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

struct AuxStream {
	using DacType = mdrivlib::DacSpi_MCP48FVBxx<MM_DACConf>;
	using DacBufferType = CircularBuffer<StreamConf::DAC::SampleT, StreamConf::DAC::BufferSize>;
	mdrivlib::DacStream<DacType, DacBufferType> dac;

	using ClockOutPin = mdrivlib::FPin<GPIO::E, 0, PinMode::Output>;
	using ClockOutBufferType = CircularBuffer<uint8_t, StreamConf::Audio::BlockSize>;
	mdrivlib::GPIOStream<ClockOutPin, ClockOutBufferType> clock_out;

	void init()
	{
		dac.init();
	}

	void queue_data(AuxStreamFrame &aux)
	{
		dac.queue_sample(0, aux.dac1);
		dac.queue_sample(1, aux.dac2);
		clock_out.queue_sample(aux.gate_out[0]);
	}

	void output_next()
	{
		dac.output_next();
		rising_edge = !rising_edge;
		if (rising_edge)
			clock_out.output_next();
	}

private:
	bool rising_edge = false;
};

} // namespace MetaModule
