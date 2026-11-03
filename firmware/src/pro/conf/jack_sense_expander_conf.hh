#pragma once
#include "drivers/gpio_expander.hh"
#include "drivers/pin.hh"

// Jack sense: TCA9555 U1212 on the jack board, on the same I2C4 bus as the codec
// (codec_jack_i2c_conf in i2c_conf.hh). Its INT goes to PH9.
// (Which bit is which jack is in jack_sense_conf.hh)

namespace MetaModule::JackSense
{
const mdrivlib::GPIO_expander_conf gpio_expander_conf = {
	.addr = 0x20, // A0=A1=A2=GND
	.config = mdrivlib::GPIO_expander_conf::AllInputs(),
};

constexpr mdrivlib::PinDef IntPin{mdrivlib::GPIO::H, mdrivlib::PinNum::_9};
} // namespace MetaModule::JackSense
