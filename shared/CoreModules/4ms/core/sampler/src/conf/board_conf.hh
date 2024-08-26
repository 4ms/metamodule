#pragma once
#include "brain_conf.hh"
#include "brain_pinout.hh"
#include "drivers/adc_builtin_conf.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/pin.hh"
#include "drivers/rgbled.hh"
#include "drivers/tim_pwm.hh"
#include "elements.hh"
#include <array>

namespace SamplerKit::Board
{

using mdrivlib::AdcChannelConf;
using mdrivlib::AdcChanNum;
using mdrivlib::GPIO;
using mdrivlib::PinDef;
using mdrivlib::PinNum;
using enum mdrivlib::PinPolarity;
using enum mdrivlib::PinMode;
namespace BrainPin = Brain::Pin;

using PlayButton = mdrivlib::DebouncedButton<BrainPin::D12, Inverted>;
using BankButton = mdrivlib::DebouncedButton<BrainPin::D6, Inverted>;
using RevButton = mdrivlib::DebouncedButton<BrainPin::A6, Inverted>;

using PlayJack = mdrivlib::DebouncedPin<BrainPin::D13, Normal>;
using RevJack = mdrivlib::DebouncedPin<BrainPin::D2, Normal>;

using PlayR = mdrivlib::FPin<BrainPin::D8.gpio, BrainPin::D8.pin, Output, Inverted>;
using PlayG = mdrivlib::FPin<BrainPin::D11.gpio, BrainPin::D11.pin, Output, Inverted>;
using PlayB = mdrivlib::FPin<BrainPin::D14.gpio, BrainPin::D14.pin, Output, Inverted>;
using PlayLED = mdrivlib::MixedRgbLed<PlayR, PlayG, PlayB>;

using RevR = mdrivlib::FPin<BrainPin::D7.gpio, BrainPin::D7.pin, Output, Inverted>;
using RevG = mdrivlib::FPin<BrainPin::D10.gpio, BrainPin::D10.pin, Output, Inverted>;
using RevB = mdrivlib::FPin<BrainPin::D3.gpio, BrainPin::D3.pin, Output, Inverted>;
using RevLED = mdrivlib::MixedRgbLed<RevR, RevG, RevB>;

using BankR = mdrivlib::FPin<BrainPin::D1.gpio, BrainPin::D1.pin, Output, Inverted>;
using BankG = mdrivlib::FPin<BrainPin::D0.gpio, BrainPin::D0.pin, Output, Inverted>;
using BankB = mdrivlib::FPin<BrainPin::D5.gpio, BrainPin::D5.pin, Output, Inverted>;
using BankLED = mdrivlib::MixedRgbLed<BankR, BankG, BankB>;

using PlayR50 = mdrivlib::Led50<BrainPin::D8.gpio, BrainPin::D8.pin, Inverted>;
using PlayGPwm = mdrivlib::TimPwmChan<BrainPin::D11PwmConf>;
using PlayBPwm = mdrivlib::TimPwmChan<BrainPin::D14PwmConf>;
using PlayPWM = mdrivlib::MixedRgbLed<PlayR50, PlayGPwm, PlayBPwm, LEDUpdateRateHz>;

using RevR50 = mdrivlib::Led50<BrainPin::D7.gpio, BrainPin::D7.pin, Inverted>;
using RevGPwm = mdrivlib::TimPwmChan<BrainPin::D10PwmConf>;
using RevBPwm = mdrivlib::TimPwmChan<BrainPin::D3PwmConf>;
using RevPWM = mdrivlib::MixedRgbLed<RevR50, RevGPwm, RevBPwm, LEDUpdateRateHz>;

using BankRPwm = mdrivlib::TimPwmChan<BrainPin::D1PwmConf>;
using BankGPwm = mdrivlib::TimPwmChan<BrainPin::D0PwmConf>;
#ifdef STM32F7
using BankBPwm = mdrivlib::TimPwmChan<BrainPin::D5PwmConf>;
using BankPWM = mdrivlib::MixedRgbLed<BankRPwm, BankGPwm, BankBPwm, LEDUpdateRateHz>;
#else
using BankB50 = mdrivlib::Led50<BrainPin::D5.gpio, BrainPin::D5.pin, Inverted>;
using BankPWM = mdrivlib::MixedRgbLed<BankRPwm, BankGPwm, BankB50, LEDUpdateRateHz>;
#endif

using EndOut = mdrivlib::FPin<BrainPin::D15.gpio, BrainPin::D15.pin, Output, Normal>;

constexpr std::array<AdcChannelConf, NumPots> PotAdcChans = {{
	{BrainPin::A1, BrainPin::A1AdcChan, PitchPot, Brain::AdcSampTime},
	{BrainPin::A3, BrainPin::A3AdcChan, StartPot, Brain::AdcSampTime},
	{BrainPin::A7, BrainPin::A7AdcChan, LengthPot, Brain::AdcSampTime},
	{BrainPin::A9, BrainPin::A9AdcChan, SamplePot, Brain::AdcSampTime},
}};

constexpr std::array<AdcChannelConf, NumCVs> CVAdcChans = {{
	{BrainPin::A2, BrainPin::A2AdcChan, PitchCV, Brain::AdcSampTime},
	{BrainPin::A0, BrainPin::A0AdcChan, StartCV, Brain::AdcSampTime},
	{BrainPin::A5, BrainPin::A5AdcChan, LengthCV, Brain::AdcSampTime},
	{BrainPin::A8, BrainPin::A8AdcChan, SampleCV, Brain::AdcSampTime},
	{BrainPin::A4, BrainPin::A4AdcChan, BankCV, Brain::AdcSampTime},
}};

} // namespace SamplerKit::Board
