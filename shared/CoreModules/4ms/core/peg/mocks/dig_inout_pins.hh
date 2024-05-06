#pragma once

#include "pins.hh"
using namespace MetaModule::PEG::Mocks;

// TODO: this needs to become a member object

// struct DigIO {
namespace DigIO
{

	InputPin PingBut;
	InputPin CycleBut;

	InputPin PingJack;
	InputPin CycleJack;
	InputPin TrigJack;

	OutputPin EOJack;
    OutputPin ClockBusOut;

	// //SWO pin can be debug out
	// using DebugOut = mdrivlib::FPin<GPIO::B, PinNum::_3, PinMode::Output, PinPolarity::Normal>;
};
