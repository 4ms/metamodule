#pragma once
#include "drivers/pin.hh"

// Headphone amp (TPA6111A2) on the jack board
namespace MetaModule::Headphone
{
constexpr mdrivlib::PinDef SensePin{mdrivlib::GPIO::F, mdrivlib::PinNum::_2};	 // HP_SENSE
constexpr mdrivlib::PinDef ShutdownPin{mdrivlib::GPIO::F, mdrivlib::PinNum::_3}; // HP_SHUTDOWN
} // namespace MetaModule::Headphone
