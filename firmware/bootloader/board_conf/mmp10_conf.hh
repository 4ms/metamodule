#pragma once
#include "drivers/clocks.hh"
#include "drivers/i2c_conf.hh"
#include "drivers/leds.hh"

namespace Board
{
using RedLED = Led<GPIO::E, PinNum::_14, LedActive::High>;
using GreenLED = Led<GPIO::B, PinNum::_15, LedActive::High>;

using OrangeLED = RedLED;
using BlueLED = Led<GPIO::A, PinNum::_9, LedActive::Low>;

// Boot select: Encoder button
constexpr bool UseBootSelect = true;
constexpr PinConf BootSelectPin{GPIO::E, PinNum::_15};

// Freeze mode: jumper on rightmost pins of the EXPANDER header
constexpr bool UseFreezePin = true;
constexpr PinConf FreezePin{GPIO::G, PinNum::_11};

constexpr uint32_t ConsoleUART = USART6_BASE;
constexpr PinConf UartRX{GPIO::C, PinNum::_7, PinAF::AF_7};
constexpr PinConf UartTX{GPIO::C, PinNum::_6, PinAF::AF_7};

namespace NORFlash
{
constexpr bool HasNORFlash = true;
constexpr PinConf d2{GPIO::F, PinNum::_7, PinAF::AF_9};
constexpr PinConf d3{GPIO::A, PinNum::_1, PinAF::AF_9};
} // namespace NORFlash

namespace PMIC
{
constexpr bool HasSTPMIC = false;
constexpr I2C_Config I2C_config{};
} // namespace PMIC

constexpr uint32_t HSE_Clock_Hz = 24000000;
constexpr uint32_t MPU_MHz = 800;
constexpr auto ClockType = SystemClocks::HSEClockSource::Resonator;

} // namespace Board
