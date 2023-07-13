#pragma once
#include "drivers/uart_conf.hh"

//p11:
constexpr inline UartConf UartConfig{
	.base_addr = UART7_BASE,
	.TXPin = {mdrivlib::GPIO::B, mdrivlib::PinNum::_4, mdrivlib::PinAF::AltFunc13},
	.RXPin = {mdrivlib::GPIO::B, mdrivlib::PinNum::_3, mdrivlib::PinAF::AltFunc13},
	.mode = UartConf::Mode::TXRX,
	.baud = 115200,
	.wordlen = 8,
	.parity = UartConf::Parity::None,
	.stopbits = UartConf::StopBits::_1,
};
// p10:
// constexpr inline UartConf UartConfig{
// 	.base_addr = USART6_BASE,
// 	.TXPin = {mdrivlib::GPIO::C, mdrivlib::PinNum::_6, mdrivlib::PinAF::AltFunc7},
// 	.RXPin = {mdrivlib::GPIO::C, mdrivlib::PinNum::_7, mdrivlib::PinAF::AltFunc7},
// 	.mode = UartConf::Mode::TXRX,
// 	.baud = 115200,
// 	.wordlen = 8,
// 	.parity = UartConf::Parity::None,
// 	.stopbits = UartConf::StopBits::_1,
// };
