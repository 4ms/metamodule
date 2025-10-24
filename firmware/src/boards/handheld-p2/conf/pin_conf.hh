#pragma once
#include "conf/i2c_codec_conf.hh"
#include "drivers/i2c_config_struct.hh"
#include "drivers/pin.hh"
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

struct EncoderPins {
	PinDef A;
	PinDef B;
};

constexpr inline auto encoders = std::array{
	EncoderPins{{GPIO::C, PinNum::_2}, {GPIO::C, PinNum::_3}}, //pull-up
	EncoderPins{{GPIO::A, PinNum::_1}, {GPIO::C, PinNum::_1}}, //pull-up
};

constexpr inline PinDef encoder_but_1{GPIO::G, PinNum::_13}; // pull-up
constexpr inline PinDef encoder_but_2{GPIO::A, PinNum::_0};	 // pull-up

constexpr inline PinDef button_1{GPIO::A, PinNum::_2}; // pull-up
constexpr inline PinDef button_2{GPIO::C, PinNum::_5}; // pull-up
constexpr inline PinDef button_3{GPIO::C, PinNum::_4}; // pull-up
constexpr inline PinDef button_4{GPIO::A, PinNum::_7}; // pull-up

// Jack sense
constexpr inline PinDef sense_injack{GPIO::E, PinNum::_3};	// pull-up
constexpr inline PinDef sense_outjack{GPIO::B, PinNum::_4}; // pull-up

//TODO
// MIC (in audio)

// Accelerometer and touch sensor
const inline mdrivlib::I2CConfig sensor_i2c_conf{
	.I2Cx = I2C3,
	.SCL = {GPIO::A, PinNum::_8, PinAF::AltFunc4},
	.SDA = {GPIO::C, PinNum::_9, PinAF::AltFunc4},
	.timing =
		{
			.PRESC = 0x40,
			.SCLDEL_SDADEL = 0xFF,
			.SCLH = 0x90,
			.SCLL = 0x90,
		},
	.priority1 = 2,
	.priority2 = 1,
};

const inline mdrivlib::I2CConfig battery_guage_conf = a7m4_shared_i2c_conf;

} // namespace ControlPins

} // namespace MetaModule
