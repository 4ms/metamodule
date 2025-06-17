#pragma once
#include "drivers/clocks.hh"
#include "drivers/i2c_conf.hh"
#include "drivers/leds.hh"

namespace Board
{

using RedLED = Led<GPIO::E, PinNum::_3, LedActive::Low>;   // not connected
using GreenLED = Led<GPIO::E, PinNum::_5, LedActive::Low>; // not connected
using BlueLED = Led<GPIO::A, PinNum::_14, LedActive::Low>; // button LED blue

// Boot Select pin: press Button 1 to select DFU USB
constexpr bool UseBootSelect = true;
constexpr PinConf BootSelectPin{GPIO::G, PinNum::_11};

// Freeze mode: jumper on debug header (left-most column)
constexpr bool UseFreezePin = true;
constexpr PinConf FreezePin{GPIO::E, PinNum::_2}; //DEBUG0 of debug header

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
