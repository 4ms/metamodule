#pragma once
#include "drivers/uart_conf.hh"
#include "drivers/pin.hh"


constexpr inline UartConf WifiBootloaderUartConfig{
	.base_addr = USART6_BASE,
	.TXPin = {mdrivlib::GPIO::G, mdrivlib::PinNum::_14, mdrivlib::PinAF::AltFunc7},
	.RXPin = {mdrivlib::GPIO::G, mdrivlib::PinNum::_9, mdrivlib::PinAF::AltFunc7},
	.mode = UartConf::Mode::TXRX,
	.baud = 115200, // 230400, 921600
	.wordlen = 8,
	.parity = UartConf::Parity::None,
	.stopbits = UartConf::StopBits::_1,
};

constexpr inline UartConf WifiUartConfig{
	.base_addr = UART5_BASE,
	.TXPin = {mdrivlib::GPIO::B, mdrivlib::PinNum::_13, mdrivlib::PinAF::AltFunc14},
	.RXPin = {mdrivlib::GPIO::B, mdrivlib::PinNum::_12, mdrivlib::PinAF::AltFunc14},
	.mode = UartConf::Mode::TXRX,
	.baud = 115200, // 230400, 921600
	.wordlen = 8,
	.parity = UartConf::Parity::None,
	.stopbits = UartConf::StopBits::_1,
};

constexpr inline mdrivlib::PinDef WifiBootloaderResetConfig{
	mdrivlib::GPIO::G,
	mdrivlib::PinNum::_13,
};

constexpr inline mdrivlib::PinDef WifiBootloaderBootSelectConfig{
	mdrivlib::GPIO::G,
	mdrivlib::PinNum::_8,
};