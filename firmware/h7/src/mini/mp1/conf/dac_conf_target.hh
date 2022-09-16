#pragma once
#include "drivers/interrupt.hh"
#include "drivers/pin.hh"
#include "drivers/spi_transfer_config_struct.hh"

namespace MetaModule
{

using mdrivlib::FPin;
using mdrivlib::GPIO;
using mdrivlib::PinMode;
using mdrivlib::PinNoInit;

struct DACConfTarget : mdrivlib::DefaultSpiConf {
	static constexpr uint16_t PeriphNum = 2; // SPI2
	static constexpr IRQn_Type IRQn = SPI2_IRQn;
	static constexpr PinNoInit SCLK = {GPIO::A, 9, LL_GPIO_AF_5};
	static constexpr PinNoInit COPI = {GPIO::B, 15, LL_GPIO_AF_5};
	static constexpr PinNoInit CIPO = {GPIO::A, 0};
	static constexpr PinNoInit CS0 = {GPIO::B, 9, 0};
	static constexpr PinNoInit CS1 = {GPIO::B, 8, 0};
	static constexpr uint16_t clock_division = 1;
	static constexpr uint32_t NumClocksToggleSSInterData = 0;

	using AuxPin = FPin<GPIO::E, 3, PinMode::Output>;
	static constexpr PinNoInit SaiLRClkPin = {GPIO::D, 4};

	static constexpr uint32_t CoreNum = 1;
};

} // namespace MetaModule
