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
	static constexpr auto width = Single;
	static constexpr mdrivlib::PinDef D0{Unused};
	static constexpr mdrivlib::PinDef D1{Unused};
	static constexpr mdrivlib::PinDef D2{Unused};
	static constexpr mdrivlib::PinDef D3{Unused};
	static constexpr mdrivlib::PinDef SCLK{Unused};
	static constexpr mdrivlib::PinDef CMD{Unused};
};
} // namespace MetaModule
