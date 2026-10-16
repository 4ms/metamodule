#pragma once
#include "drivers/sdcard_conf.hh"

// microSD card slot CON1201 on SDMMC1 (PE0-PE5, VDDIO1).
// The same bus also goes to the devboard's own microSD slot: leave that slot empty.
// No card-detect pin on the pro board.
// TODO: mdrivlib has no STM32MP2 SDMMC driver yet (no stm32mp2-baremetal proof-of-concept either)

namespace MetaModule
{

struct SDCardConf : mdrivlib::DefaultSDCardConf {
	using enum mdrivlib::GPIO;
	using enum mdrivlib::PinNum;
	using enum mdrivlib::PinAF;

	static constexpr auto SDPeriphNum = 1;
	static constexpr auto speed_hz = 32'000'000;
	static constexpr auto width = Wide4;
	static constexpr mdrivlib::PinDef D0{E, _4, AltFunc10};
	static constexpr mdrivlib::PinDef D1{E, _5, AltFunc10};
	static constexpr mdrivlib::PinDef D2{E, _0, AltFunc10};
	static constexpr mdrivlib::PinDef D3{E, _1, AltFunc10};
	static constexpr mdrivlib::PinDef SCLK{E, _3, AltFunc10};
	static constexpr mdrivlib::PinDef CMD{E, _2, AltFunc10};
};
} // namespace MetaModule
