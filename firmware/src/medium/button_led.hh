#pragma once
#include "drivers/pin.hh"
#include "drivers/tim_pwm.hh"
#include "util/rgbled.hh"

namespace MetaModule
{

constexpr inline mdrivlib::TimChanConf RedPwmConf{
	.pin = {mdrivlib::GPIO::E, mdrivlib::PinNum::_14, mdrivlib::PinAF::AltFunc1},
	.TIM = TIM1_BASE,
	.channum = mdrivlib::TimChannelNum::_4,
};

constexpr inline mdrivlib::TimChanConf GreenPwmConf{
	.pin = {mdrivlib::GPIO::B, mdrivlib::PinNum::_15, mdrivlib::PinAF::AltFunc1},
	.TIM = TIM1_BASE,
	.channum = mdrivlib::TimChannelNum::_3N,
};

constexpr inline mdrivlib::TimChanConf BluePwmConf{
	.pin = {mdrivlib::GPIO::A, mdrivlib::PinNum::_9, mdrivlib::PinAF::AltFunc1},
	.TIM = TIM1_BASE,
	.channum = mdrivlib::TimChannelNum::_2,
};

using RedPwm = mdrivlib::TimPwmChan<RedPwmConf>;
using GreenPwm = mdrivlib::TimPwmChan<GreenPwmConf>;
using BluePwm = mdrivlib::TimPwmChan<BluePwmConf>;

using ButtonLED = MixedRgbLed<RedPwm, GreenPwm, BluePwm>;

} // namespace MetaModule
