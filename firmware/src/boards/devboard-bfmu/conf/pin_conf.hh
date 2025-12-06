#pragma once
#include "drivers/pin.hh"
#include "drivers/tim_pwm.hh"
#include "drivers/uart_conf.hh"
#include <array>

namespace MetaModule
{

namespace ControlPins
{

using mdrivlib::GPIO;
using mdrivlib::PinAF;
using mdrivlib::PinDef;
using mdrivlib::PinMode;
using mdrivlib::PinNum;

// Encoders
struct EncoderPins {
	PinDef A;
	PinDef B;
};

constexpr inline auto encoders = std::array{
	EncoderPins{{GPIO::E, PinNum::_3}, {GPIO::D, PinNum::_10}}, //ENCODER 1
	EncoderPins{{GPIO::G, PinNum::_6}, {GPIO::D, PinNum::_3}},	//ENCODER 2
};

// PWM out:
constexpr inline mdrivlib::TimChanConf haptic_conf{
	.pin = {GPIO::B, PinNum::_9, PinAF::AltFunc1},
	.TIM = TIM17_BASE,
	.channum = mdrivlib::TimChannelNum::_1,
	.period = 512,
	.prescaler = 0,
	.clock_div = 0,
};

// GPIO outs:
constexpr inline PinDef clock_out{GPIO::C, PinNum::_7}; //inverted

// GPIO ins:
constexpr inline PinDef random_gate_in{GPIO::B, PinNum::_10}; //inverted, no pullup
constexpr inline PinDef trig_in{GPIO::G, PinNum::_15};		  //inverted, no pullup
constexpr inline PinDef sync_in{GPIO::C, PinNum::_4};		  //inverted, no pullup
constexpr inline PinDef rec_gate_in{GPIO::C, PinNum::_0};	  //inverted, no pullup

// DAC out (driver TODO)
constexpr inline PinDef cv_out_1{GPIO::A, PinNum::_4};
constexpr inline PinDef cv_out_2{GPIO::A, PinNum::_5};

// MIDI IN Uart:
constexpr inline UartConf MIDI_Uart{
	.base_addr = UART7_BASE,
	.TXPin = {GPIO::B, PinNum::_4, PinAF::AltFunc13},
	.RXPin = {GPIO::A, PinNum::_8, PinAF::AltFunc13},
	.mode = UartConf::Mode::TXRX,
	.baud = 31250,
	.wordlen = 8,
	.parity = UartConf::Parity::None,
	.stopbits = UartConf::StopBits::_1,
};

} // namespace ControlPins

} // namespace MetaModule
