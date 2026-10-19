#pragma once
#include "drivers/uart_conf.hh"

// Console on the mp2-devboard J4 header (same UART as the early console in uart_print.c)
constexpr inline UartConf LogUartConfig{
	.base_addr = USART1_BASE,
	.TXPin = {mdrivlib::GPIO::B, mdrivlib::PinNum::_8, mdrivlib::PinAF::AltFunc6},
	.RXPin = {mdrivlib::GPIO::B, mdrivlib::PinNum::_10, mdrivlib::PinAF::AltFunc6},
	.mode = UartConf::Mode::TXRX,
	.baud = 115200,
	.wordlen = 8,
	.parity = UartConf::Parity::None,
	.stopbits = UartConf::StopBits::_1,
};
