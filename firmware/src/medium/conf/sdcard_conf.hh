#pragma once
#include "drivers/sdcard_conf.hh"

namespace MetaModule
{

struct SDCardConf : mdrivlib::DefaultSDCardConf {
	using enum mdrivlib::GPIO;
	using enum mdrivlib::PinNum;
	using enum mdrivlib::PinAF;

	static constexpr auto SDPeriphNum = 1;
	static constexpr auto speed_hz = 32'000'000;
	static constexpr auto width = Wide4;
	static constexpr mdrivlib::PinDef D0{C, _8, AltFunc12};
	static constexpr mdrivlib::PinDef D1{C, _9, AltFunc12};
	static constexpr mdrivlib::PinDef D2{C, _10, AltFunc12};
	static constexpr mdrivlib::PinDef D3{C, _11, AltFunc12};
	static constexpr mdrivlib::PinDef SCLK{C, _12, AltFunc12};
	static constexpr mdrivlib::PinDef CMD{D, _2, AltFunc12};
};
} // namespace MetaModule
