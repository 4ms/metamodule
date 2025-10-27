#pragma once
#include "drivers/pin.hh"

namespace MetaModule
{

using mdrivlib::GPIO;
using mdrivlib::PinNum;

struct ControlPins {
	// TODO: array of encoders, array of buttons, array of gate ins
	static constexpr mdrivlib::PinDef rotA{GPIO::E, PinNum::_7}; //unused
	static constexpr mdrivlib::PinDef rotB{GPIO::E, PinNum::_8}; //unused

	static constexpr mdrivlib::PinDef rotS{GPIO::E, PinNum::_14}; //unused
	static constexpr mdrivlib::PinDef but0{GPIO::E, PinNum::_15}; //unused

	static constexpr mdrivlib::PinDef gate_in_1{GPIO::E, PinNum::_3}; //TEst gate jack
	static constexpr mdrivlib::PinDef gate_in_2{GPIO::E, PinNum::_1}; //unused
};

} // namespace MetaModule
