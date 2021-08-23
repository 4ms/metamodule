#pragma once
#include "conf/stream_conf.hh"
#include "drivers/dac_stream.hh"
#include "drivers/pin_change_conf.hh"
#include "util/circular_buffer.hh"
#include <cstdint>

namespace MetaModule
{

struct AuxStreamFrame {
	std::array<uint32_t, 2> gate_out;
};

using GPIO = mdrivlib::GPIO;
using PinMode = mdrivlib::PinMode;

struct AuxStreamUpdateConf : mdrivlib::DefaultPinChangeConf {
	static constexpr uint32_t pin = 4;
	static constexpr GPIO port = GPIO::D;
	static constexpr bool on_rising_edge = true;
	static constexpr bool on_falling_edge = false;
	static constexpr uint32_t priority1 = 0;
	static constexpr uint32_t priority2 = 0;
	static constexpr uint32_t core = 1;
};

struct AuxStream {
	using ClockOutPin1 = mdrivlib::FPin<GPIO::F, 6, PinMode::Output>;
	using ClockOutPin2 = mdrivlib::FPin<GPIO::D, 12, PinMode::Output>;
	using BufferType = CircularBuffer<uint8_t, StreamConf::Audio::BlockSize>;

	mdrivlib::GPIOStream<ClockOutPin1, BufferType> gate_out_1;
	mdrivlib::GPIOStream<ClockOutPin2, BufferType> gate_out_2;

	void init() {}

	void queue_data(AuxStreamFrame &aux)
	{
		gate_out_1.queue_sample(aux.gate_out[0]);
		gate_out_2.queue_sample(aux.gate_out[1]);
	}

	void output_next()
	{
		gate_out_1.output_next();
		gate_out_2.output_next();
	}
};

} // namespace MetaModule
