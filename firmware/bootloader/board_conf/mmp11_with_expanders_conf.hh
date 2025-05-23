#pragma once
#include "drivers/clocks.hh"
#include "drivers/i2c_conf.hh"
#include "drivers/leds.hh"

namespace Board
{

using RedLED = Led<GPIO::E, PinNum::_14, LedActive::Low>;	// button LED red
using GreenLED = Led<GPIO::B, PinNum::_15, LedActive::Low>; // button LED green
using RedLED2 = RedLED;
using GreenLED2 = GreenLED;

using OrangeLED = RedLED2;
using BlueLED = Led<GPIO::A, PinNum::_9, LedActive::Low>; // button LED blue

// Boot Select pin: press Rotary encoder to select DFU USB
constexpr bool UseBootSelect = true;
constexpr PinConf BootSelectPin{GPIO::E, PinNum::_15};

// Freeze mode: jumper on debug header (left-most column)
constexpr bool UseFreezePin = true;
constexpr PinConf FreezePin{GPIO::D, PinNum::_3}; //DEBUG1 of debug header

constexpr uint32_t ConsoleUART = UART7_BASE;
constexpr PinConf UartRX{GPIO::B, PinNum::_3, PinAF::AF_13};
constexpr PinConf UartTX{GPIO::B, PinNum::_4, PinAF::AF_13};

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
