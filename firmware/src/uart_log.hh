#pragma once
#include "drivers/uart.hh"
#include "drivers/uart_conf.hh"
#include "printf.h"

namespace MetaModule
{
constexpr inline UartConf UartConfig{
	.base_addr = USART6_BASE,
	.TXPin = {mdrivlib::GPIO::C, mdrivlib::PinNum::_6, mdrivlib::PinAF::AltFunc7},
	.RXPin = {mdrivlib::GPIO::C, mdrivlib::PinNum::_7, mdrivlib::PinAF::AltFunc7},
	.mode = UartConf::Mode::TXRX,
	.baud = 115200,
	.wordlen = 8,
	.parity = UartConf::Parity::None,
	.stopbits = UartConf::StopBits::_1,
};

struct UartLog {
	static inline mdrivlib::Uart<UartConfig> log_uart;

	UartLog() {
		init();
	}

	static void init();

	static void putchar(char c);

	static void log(const char *format, ...);
};
} // namespace MetaModule
