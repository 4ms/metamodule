#pragma once
#include "drivers/i2c_config_struct.hh"
#include "drivers/pin.hh"
#include "drivers/pin_change_conf.hh"

namespace MetaModule
{
// I2C for usb-c chip
const mdrivlib::I2CConfig usb_i2c_conf = {
	.I2Cx = I2C6,
	.SCL = {mdrivlib::GPIO::D, 1, mdrivlib::PinAF::AltFunc2},
	.SDA = {mdrivlib::GPIO::D, 0, mdrivlib::PinAF::AltFunc2},
	.timing =
		{
			.PRESC = 0x10, //0x20 is 100k
			.SCLDEL_SDADEL = 0x50,
			.SCLH = 0x58,
			.SCLL = 0x58,
		},
	.priority1 = 2,
	.priority2 = 2,
	.analog_filter = true,
	.digital_filter = mdrivlib::I2CConfig::DigitalFilterLevel::Max,
};

struct FUSBPinChangeConf : mdrivlib::DefaultPinChangeConf {
	static constexpr uint32_t pin = 10;
	static constexpr mdrivlib::GPIO port = mdrivlib::GPIO::A;
	static constexpr bool on_rising_edge = false;
	static constexpr bool on_falling_edge = true;
	static constexpr uint32_t priority1 = 3;
	static constexpr uint32_t priority2 = 3;
	static constexpr uint32_t core = 1;
};

using FUSBIntPin =
	mdrivlib::FPin<mdrivlib::GPIO::A, mdrivlib::PinNum::_10, mdrivlib::PinMode::Input, mdrivlib::PinPolarity::Inverted>;

constexpr inline uint8_t FUSBDevAddr = 0b01000100;

constexpr inline mdrivlib::PinNoInit Usb5VSrcEnablePin{mdrivlib::GPIO::A, 15};

} // namespace MetaModule
