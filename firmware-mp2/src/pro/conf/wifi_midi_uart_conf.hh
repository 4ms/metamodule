#pragma once
#include "drivers/pin.hh"
#include "drivers/uart_conf.hh"

namespace MetaModule
{

// DIN MIDI (J12 in via optocoupler U6, J13 out via buffer U9), on the jack board
constexpr inline UartConf MidiUartConf{
	.base_addr = USART6_BASE,
	.TXPin = {mdrivlib::GPIO::F, mdrivlib::PinNum::_5, mdrivlib::PinAF::AltFunc6},
	.RXPin = {mdrivlib::GPIO::F, mdrivlib::PinNum::_4, mdrivlib::PinAF::AltFunc6},
	.mode = UartConf::Mode::TXRX,
	.baud = 31250,
	.wordlen = 8,
	.parity = UartConf::Parity::None,
	.stopbits = UartConf::StopBits::_1,
};

// ESP32-C6 Wi-Fi module (U1207)
//
// !! p1 HARDWARE ISSUE: the two ESP UART pins have no USART instance in common:
// PH7 (to ESP RXD0) can only be UART4_TX (AF4), and PH5 (from ESP TXD0) can only be
// UART7_RX (AF8). On p1 the link must use two half-UARTs at the same baud rate.
constexpr inline UartConf WifiTxUartConf{
	.base_addr = UART4_BASE,
	.TXPin = {mdrivlib::GPIO::H, mdrivlib::PinNum::_7, mdrivlib::PinAF::AltFunc4},
	.RXPin = {mdrivlib::GPIO::Unused, mdrivlib::PinNum::_0, mdrivlib::PinAF::AFNone},
	.mode = UartConf::Mode::TXonly,
	.baud = 115200,
};

constexpr inline UartConf WifiRxUartConf{
	.base_addr = UART7_BASE,
	.TXPin = {mdrivlib::GPIO::Unused, mdrivlib::PinNum::_0, mdrivlib::PinAF::AFNone},
	.RXPin = {mdrivlib::GPIO::H, mdrivlib::PinNum::_5, mdrivlib::PinAF::AltFunc8},
	.mode = UartConf::Mode::RXonly,
	.baud = 115200,
};

namespace Wifi
{
constexpr mdrivlib::PinDef EnablePin{mdrivlib::GPIO::I, mdrivlib::PinNum::_4}; // ESP EN/CHIP_PU (also SW1206)
constexpr mdrivlib::PinDef BootPin{mdrivlib::GPIO::F, mdrivlib::PinNum::_14};  // ESP GPIO9 (also SW1207)
constexpr mdrivlib::PinDef Gpio8{mdrivlib::GPIO::H, mdrivlib::PinNum::_4};
constexpr mdrivlib::PinDef Gpio10{mdrivlib::GPIO::F, mdrivlib::PinNum::_7};
constexpr mdrivlib::PinDef Gpio11{mdrivlib::GPIO::F, mdrivlib::PinNum::_8};
} // namespace Wifi

} // namespace MetaModule
