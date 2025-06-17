#pragma once
#include "drivers/pin.hh"

namespace MetaModule
{

using mdrivlib::GPIO;
using mdrivlib::PinNum;

struct ControlPins {
	// TODO: array of encoders, array of buttons, array of gate ins
	static constexpr mdrivlib::PinDef rotA{GPIO::D, PinNum::_5};
	static constexpr mdrivlib::PinDef rotB{GPIO::E, PinNum::_13};

	static constexpr mdrivlib::PinDef rot2A{GPIO::A, PinNum::_4};
	static constexpr mdrivlib::PinDef rot2B{GPIO::C, PinNum::_3};

	static constexpr mdrivlib::PinDef rotS{GPIO::G, PinNum::_11}; //BUT1
	static constexpr mdrivlib::PinDef but0{GPIO::A, PinNum::_5};  //BUT2

	static constexpr mdrivlib::PinDef gate_in_1{GPIO::C, PinNum::_2}; //BUT3
	static constexpr mdrivlib::PinDef gate_in_2{GPIO::A, PinNum::_3}; //BUT4
};

} // namespace MetaModule
