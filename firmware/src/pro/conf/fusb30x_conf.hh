#pragma once
#include "conf/i2c_conf.hh"
#include "drivers/pin.hh"

// USB-C port controller FUSB302B (U4) for the USB jack J17 (USB3DR, USB2 lines only).
// The devboard v0.1 has USB3DR D+/D- swapped going to J1 (fixed with jumpers on the devboard);
// the pro board passes J1.75/J1.77 straight through to the jack's D+/D-.

namespace MetaModule
{
// Shares I2C4 with the jack board (codec, jack sense): hold SharedI2CGuard while using it
inline const mdrivlib::I2CConfig &usb_i2c_conf = codec_jack_i2c_conf;

constexpr inline uint8_t FUSBDevAddr = 0x22 << 1; // FUSB302BMPX, shifted

#ifdef MP2_TEST_CARRIER
// Test carrier (the stm32mp2-baremetal breakout): FUSB302B on I2C4, INT_N on PD13, VBUS load
// switch enable on PB4
using FUSBIntPin =
	mdrivlib::FPin<mdrivlib::GPIO::D, mdrivlib::PinNum::_13, mdrivlib::PinMode::Input, mdrivlib::PinPolarity::Inverted>;

constexpr inline mdrivlib::PinDef Usb5VSrcEnablePin{mdrivlib::GPIO::B, mdrivlib::PinNum::_4};
#else
// INT_N is open-drain with no external pull-up on p1: enable the MCU pull-up.
// PE9 is on VDDIO2 (1.8V on the devboard), which is fine for an open-drain input.
using FUSBIntPin =
	mdrivlib::FPin<mdrivlib::GPIO::E, mdrivlib::PinNum::_9, mdrivlib::PinMode::Input, mdrivlib::PinPolarity::Inverted>;

// Enables the TPS22919 load switch that sources 5V to VBUS (host mode)
constexpr inline mdrivlib::PinDef Usb5VSrcEnablePin{mdrivlib::GPIO::D, mdrivlib::PinNum::_13};
#endif

} // namespace MetaModule
