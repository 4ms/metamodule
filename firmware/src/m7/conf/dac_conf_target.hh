#pragma once
#include "drivers/interrupt.hh"
#include "drivers/pin.hh"
#include "drivers/spi_transfer_config_struct.hh"

using mdrivlib::FPin;
using mdrivlib::GPIO;
using mdrivlib::PinMode;
using mdrivlib::PinNoInit;

struct DACConfTarget : mdrivlib::DefaultSpiConf {
	static constexpr uint16_t PeriphNum = 2; // SPI2
	static constexpr IRQType IRQn = SPI2_IRQn;
	static constexpr PinNoInit SCLK = {GPIO::B, 13, LL_GPIO_AF_5};
	static constexpr PinNoInit COPI = {GPIO::B, 15, LL_GPIO_AF_5};
	static constexpr PinNoInit CIPO = {GPIO::A, 0};
	static constexpr PinNoInit CS0 = {GPIO::B, 12, 0};
	static constexpr PinNoInit CS1 = {GPIO::B, 11, 0};
	static constexpr uint16_t clock_division = 16;
	static constexpr uint32_t NumClocksToggleSSInterData = 0;

	using AuxPin = FPin<GPIO::B, 14, PinMode::Output>;
	static constexpr PinNoInit SaiLRClkPin = {GPIO::E, 4};

	static constexpr uint32_t CoreNum = 2;
};
