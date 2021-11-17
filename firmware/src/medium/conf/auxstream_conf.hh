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
	void set_output(uint32_t, uint32_t) {
	}
};

using GPIO = mdrivlib::GPIO;
using PinMode = mdrivlib::PinMode;

struct AuxStreamUpdateConf : mdrivlib::DefaultPinChangeConf {
	static constexpr uint32_t pin = 4;
	static constexpr GPIO port = GPIO::D; // PD4 = SAI3 LRCLK
	static constexpr bool on_rising_edge = true;
	static constexpr bool on_falling_edge = false;
	static constexpr uint32_t priority1 = 0;
	static constexpr uint32_t priority2 = 0;
	static constexpr uint32_t core = 1;
};

struct AuxStream {
	static constexpr bool BoardHasDac = false;
	static constexpr float DACscaling = 0.f;

	mdrivlib::Pin ButtonLedBlue{GPIO::B, 7, PinMode::Alt, LL_GPIO_AF_2};  // TIM4_CH2
	mdrivlib::Pin ButtonLedRed{GPIO::B, 8, PinMode::Alt, LL_GPIO_AF_2};	  // TIM4_CH3
	mdrivlib::Pin ButtonLedGreen{GPIO::B, 9, PinMode::Alt, LL_GPIO_AF_2}; // TIM4_CH4

	using ClockOutPin1 = mdrivlib::FPin<GPIO::G, 2, PinMode::Output>;
	using ClockOutPin2 = mdrivlib::FPin<GPIO::F, 15, PinMode::Output>;
	using BufferType = CircularBuffer<uint8_t, StreamConf::Audio::BlockSize>;

	mdrivlib::GPIOStream<ClockOutPin1, BufferType> gate_out_1;
	mdrivlib::GPIOStream<ClockOutPin2, BufferType> gate_out_2;

	void init() {
	}

	void queue_data(AuxStreamFrame &aux) {
		gate_out_1.queue_sample(aux.gate_out[0]);
		gate_out_2.queue_sample(aux.gate_out[1]);
	}

	void output_next() {
		gate_out_1.output_next();
		gate_out_2.output_next();
	}

	void test_outputs() {
		AuxStream::ClockOutPin1::high();
		AuxStream::ClockOutPin2::high();
		AuxStream::ClockOutPin1::low();
		AuxStream::ClockOutPin2::low();
		mdrivlib::FPin<GPIO::B, 7, PinMode::Output> blue;
		blue.high();
		mdrivlib::FPin<GPIO::B, 8, PinMode::Output> red;
		red.high();
		mdrivlib::FPin<GPIO::B, 9, PinMode::Output> green;
		green.high();
		//magenta
		blue.low();
		red.low();
		//white
		green.low();
		//yellow
		blue.high();
		//cyan
		red.high();
		blue.low();
	}
};

} // namespace MetaModule
