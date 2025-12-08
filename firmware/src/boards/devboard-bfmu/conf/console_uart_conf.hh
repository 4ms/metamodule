#pragma once
#include "drivers/uart_conf.hh"

constexpr inline UartConf LogUartConfig{
	.base_addr = UART4_BASE,
	.TXPin = {mdrivlib::GPIO::D, mdrivlib::PinNum::_1, mdrivlib::PinAF::AltFunc8},
	.RXPin = {mdrivlib::GPIO::D, mdrivlib::PinNum::_0, mdrivlib::PinAF::AltFunc8},
	.mode = UartConf::Mode::TXRX,
	.baud = 115200,
	.wordlen = 8,
	.parity = UartConf::Parity::None,
	.stopbits = UartConf::StopBits::_1,
};
