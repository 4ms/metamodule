#pragma once
#include "drivers/pin.hh"

namespace MetaModule
{

using mdrivlib::GPIO;
using mdrivlib::PinNum;

struct ControlPins {
	static constexpr mdrivlib::PinDef rotA{GPIO::D, PinNum::_5};
	static constexpr mdrivlib::PinDef rotB{GPIO::E, PinNum::_13};
	static constexpr mdrivlib::PinDef rotS{GPIO::E, PinNum::_15};
	static constexpr mdrivlib::PinDef but0{GPIO::D, PinNum::_8};
	static constexpr mdrivlib::PinDef gate_in_1{GPIO::F, PinNum::_11};
	static constexpr mdrivlib::PinDef gate_in_2{GPIO::B, PinNum::_8};
};

} // namespace MetaModule
