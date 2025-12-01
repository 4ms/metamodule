#pragma once
#include "conf/i2c_codec_conf.hh"
#include "drivers/i2c_config_struct.hh"
#include "drivers/pin.hh"
#include "drivers/pin_change_conf.hh"

namespace MetaModule
{
// I2C for usb-c chip, which is used by m4 in UsbManager
// shared with codec (a7 only on init) and battery fuel guage (m4 controls)
const mdrivlib::I2CConfig usb_i2c_conf = a7m4_shared_i2c_conf;

struct FUSBPinChangeConf : mdrivlib::DefaultPinChangeConf {
	static constexpr uint32_t pin = 10;
	static constexpr mdrivlib::GPIO port = mdrivlib::GPIO::E;
	static constexpr bool on_rising_edge = false;
	static constexpr bool on_falling_edge = true;
	static constexpr uint32_t priority1 = 3;
	static constexpr uint32_t priority2 = 3;
	static constexpr uint32_t core = 1;
};

using FUSBIntPin =
	mdrivlib::FPin<mdrivlib::GPIO::E, mdrivlib::PinNum::_10, mdrivlib::PinMode::Input, mdrivlib::PinPolarity::Inverted>;

constexpr inline uint8_t FUSBDevAddr = 0b01000100;

constexpr inline mdrivlib::PinDef Usb5VSrcEnablePin{mdrivlib::GPIO::G, mdrivlib::PinNum::_9};

} // namespace MetaModule
