#pragma once
#include "drivers/i2c_config_struct.hh"

// I2C buses on the MetaModule Pro p1 board.
//
// All I2C kernel clocks are HSI/4 = 16MHz (see rcc_conf.hh), so the timings
// below are the RM0457 reference values for a 16MHz I2CCLK with the analog
// filter on and the digital filter off.

namespace MetaModule
{

namespace I2CTiming
{
// 100kHz: PRESC=3, SCLDEL=4, SDADEL=2, SCLH=0x0F, SCLL=0x13
constexpr inline mdrivlib::I2CTimingConfig Standard100k{
	.PRESC = 0x30,
	.SCLDEL_SDADEL = 0x42,
	.SCLH = 0x0F,
	.SCLL = 0x13,
};

// 400kHz: PRESC=1, SCLDEL=3, SDADEL=2, SCLH=0x03, SCLL=0x09
constexpr inline mdrivlib::I2CTimingConfig Fast400k{
	.PRESC = 0x10,
	.SCLDEL_SDADEL = 0x32,
	.SCLH = 0x03,
	.SCLL = 0x09,
};
} // namespace I2CTiming

// I2C4: jack board (PCM3168 codec at 0x44, jack-sense TCA9555 at 0x20) and FUSB302 (0x22).
// Shared by the A35 (codec) and the M33 (jack sense, USB-C), same as I2C5 on MP1.
const mdrivlib::I2CConfig codec_jack_i2c_conf = {
	.I2Cx = I2C4,
	.SCL = {mdrivlib::GPIO::D, mdrivlib::PinNum::_11, mdrivlib::PinAF::AltFunc6},
	.SDA = {mdrivlib::GPIO::D, mdrivlib::PinNum::_10, mdrivlib::PinAF::AltFunc6},
	.timing = I2CTiming::Standard100k,
	.priority1 = 2,
	.priority2 = 1,
	.analog_filter = true,
	.digital_filter = mdrivlib::I2CConfig::DigitalFilterLevel::Min,
};

// I2C2: control expanders U1210 (0x21) and U1211 (0x22).
//
// !! p1 HARDWARE BUG: on the STM32MP257, PB5 is I2C2_SCL (AF9) and PB4 is I2C2_SDA (AF9),
// but the p1 schematic routes PB5 to the expanders' SDA and PB4 to their SCL.
// p1 boards must have the traces cut and swapped. This config assumes that bodge:
const mdrivlib::I2CConfig controls_a_i2c_conf = {
	.I2Cx = I2C2,
	.SCL = {mdrivlib::GPIO::B, mdrivlib::PinNum::_5, mdrivlib::PinAF::AltFunc9},
	.SDA = {mdrivlib::GPIO::B, mdrivlib::PinNum::_4, mdrivlib::PinAF::AltFunc9},
	.timing = I2CTiming::Fast400k,
	.priority1 = 2,
	.priority2 = 2,
	.analog_filter = true,
	.digital_filter = mdrivlib::I2CConfig::DigitalFilterLevel::Min,
};

// I2C3: control expanders U1213 (0x23) and U1209 (0x24).
const mdrivlib::I2CConfig controls_b_i2c_conf = {
	.I2Cx = I2C3,
	.SCL = {mdrivlib::GPIO::G, mdrivlib::PinNum::_1, mdrivlib::PinAF::AltFunc9},
	.SDA = {mdrivlib::GPIO::G, mdrivlib::PinNum::_2, mdrivlib::PinAF::AltFunc9},
	.timing = I2CTiming::Fast400k,
	.priority1 = 2,
	.priority2 = 2,
	.analog_filter = true,
	.digital_filter = mdrivlib::I2CConfig::DigitalFilterLevel::Min,
};

// I2C6: button LED drivers LP5018 U5 (0x28) and U8 (0x29).
const mdrivlib::I2CConfig led_i2c_conf = {
	.I2Cx = I2C6,
	.SCL = {mdrivlib::GPIO::G, mdrivlib::PinNum::_6, mdrivlib::PinAF::AltFunc9},
	.SDA = {mdrivlib::GPIO::G, mdrivlib::PinNum::_5, mdrivlib::PinAF::AltFunc9},
	.timing = I2CTiming::Fast400k,
	.priority1 = 3,
	.priority2 = 3,
	.analog_filter = true,
	.digital_filter = mdrivlib::I2CConfig::DigitalFilterLevel::Min,
};

} // namespace MetaModule
