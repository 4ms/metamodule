#pragma once
#include "drivers/sdcard_conf.hh"

// microSD card slot CON1201 on SDMMC1 (PE0-PE5, VDDIO1).
// The same bus also goes to the devboard's own microSD slot (only one card at a time),
// and on p1 to the ESP32-C6 GPIO18-23 via R17-R24 (the ESP must keep those pins high-Z).
//
// Card detect:
// p1: none. There's no detect pin, and R27 pulls DAT3 up (so MP1's DAT3 detect can't work).
//     A card is detected by whether it responds to initialization.
// Test carrier (card in the devboard's slot): the slot's detect switch connects PB11 (SDDET1)
//     to PB3 (SDDET2) when a card is inserted. PB3 is driven low (SDCardDetectCommonPin) and
//     PB11 is read with a pull-up, so low = card present.

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

#ifdef MP2_TEST_CARRIER
	static constexpr auto card_detect = CardDetect::GPIOLow;
	static constexpr mdrivlib::PinDef CardDetectPin{B, _11};
	static constexpr auto card_detect_pull = mdrivlib::PinPull::Up;
#else
	static constexpr auto card_detect = CardDetect::None;
#endif
};
#ifdef MP2_TEST_CARRIER
// Other side of the devboard slot's detect switch: must be driven low before the SD driver starts
constexpr mdrivlib::PinDef SDCardDetectCommonPin{mdrivlib::GPIO::B, mdrivlib::PinNum::_3};
#endif

} // namespace MetaModule
