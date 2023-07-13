#pragma once
#include "drivers/clocks.hh"
#include "drivers/i2c_conf.hh"
#include "drivers/leds.hh"

namespace Board
{
using RedLED = Led<GPIO::E, PinNum::_4, LedActive::High>;	 //DEBUG0
using GreenLED = Led<GPIO::D, PinNum::_3, LedActive::High>;	 //DEBUG1
using RedLED2 = Led<GPIO::A, PinNum::_14, LedActive::High>;	 //Control Expander EXTGPIO1
using GreenLED2 = Led<GPIO::E, PinNum::_2, LedActive::High>; //" EXTGPIO2

using OrangeLED = RedLED2;
using BlueLED = Led<GPIO::A, PinNum::_14, LedActive::Low>;

//EXPANDER: right-most pins shorted
constexpr bool UseBootSelect = true;
constexpr PinConf BootSelectPin{GPIO::G, PinNum::_11}; //EXTGPIO3

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
