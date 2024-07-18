#pragma once
#include "conf/panel_conf.hh"
#include "conf/stream_conf.hh"
#include "drivers/dac_stream.hh"
#include "drivers/pin_change_conf.hh"
#include "util/circular_buffer.hh"
#include <cstdint>

namespace MetaModule
{

struct AuxStreamFrame {
	[[no_unique_address]] std::array<uint32_t, PanelDef::NumGateOut> gate_out;
	void set_output(uint32_t, uint32_t) {
	}
};

using GPIO = mdrivlib::GPIO;
using PinMode = mdrivlib::PinMode;

struct AuxStreamUpdateConf : mdrivlib::DefaultPinChangeConf {
	static constexpr uint32_t pin = 12;
	static constexpr GPIO port = GPIO::D; // PD12 = SAI3 LRCLK
	static constexpr bool on_rising_edge = true;
	static constexpr bool on_falling_edge = false;
	static constexpr uint32_t priority1 = 0;
	static constexpr uint32_t priority2 = 0;
	static constexpr uint32_t core = 1;
};

struct AuxStream {
	static constexpr bool BoardHasDac = false;
	static constexpr bool BoardHasGateOuts = false;

	static constexpr float DACscaling = 0.f;

	// mdrivlib::Pin ButtonLedBlue{GPIO::A, 9, PinMode::Alt, LL_GPIO_AF_1};   // TIM1_CH2
	// mdrivlib::Pin ButtonLedRed{GPIO::B, 15, PinMode::Alt, LL_GPIO_AF_1};   // TIM1_CH3N
	// mdrivlib::Pin ButtonLedGreen{GPIO::E, 14, PinMode::Alt, LL_GPIO_AF_1}; // TIM1_CH4

	// using ClockOutPin1 = mdrivlib::FPin<GPIO::G, 14, PinMode::Output>;
	// using ClockOutPin2 = mdrivlib::FPin<GPIO::B, 12, PinMode::Output>;
	using BufferType = CircularBuffer<uint8_t, StreamConf::Audio::MaxBlockSize>;

	// mdrivlib::GPIOStream<ClockOutPin1, BufferType> gate_out_1;
	// mdrivlib::GPIOStream<ClockOutPin2, BufferType> gate_out_2;

	void init() {
	}

	void queue_data(AuxStreamFrame &frame) {
		// gate_out_1.queue_sample(frame.gate_out[0]);
		// gate_out_2.queue_sample(frame.gate_out[1]);
	}

	void output_next() {
		// gate_out_1.output_next();
		// gate_out_2.output_next();
	}

	void test_outputs() {
		// AuxStream::ClockOutPin1::high();
		// AuxStream::ClockOutPin2::high();
		// AuxStream::ClockOutPin1::low();
		// AuxStream::ClockOutPin2::low();
		// ButtonLedBlue.high();
		// ButtonLedBlue.low();
		// ButtonLedGreen.high();
		// ButtonLedGreen.low();
		// ButtonLedRed.high();
		// ButtonLedRed.low();
	}
};

} // namespace MetaModule
