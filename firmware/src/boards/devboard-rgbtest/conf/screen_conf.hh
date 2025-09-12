#pragma once
#include "drivers/ltdc_screen_config_struct.hh"
#include "drivers/screen_9bit_setup.hh"

namespace MetaModule
{
using mdrivlib::FPin;
using mdrivlib::GPIO;
using mdrivlib::PinAF;
using mdrivlib::PinDef;
using mdrivlib::PinMode;
using mdrivlib::PinNum;
using mdrivlib::PinPolarity;

struct ScreenConf : mdrivlib::LTDCScreenConf {

	static constexpr PinDef r[8]{
		{},										 //0
		{},										 //1
		{},										 //2
		{GPIO::B, PinNum::_0, PinAF::AltFunc9},	 //3
		{GPIO::A, PinNum::_5, PinAF::AltFunc14}, //4
		{GPIO::C, PinNum::_0, PinAF::AltFunc14}, //5
		{GPIO::B, PinNum::_1, PinAF::AltFunc9},	 //6
		{GPIO::G, PinNum::_6, PinAF::AltFunc14}, //7
	};

	static constexpr PinDef g[8]{
		{},										  //0
		{},										  //1
		{GPIO::A, PinNum::_6, PinAF::AltFunc14},  //2
		{GPIO::E, PinNum::_11, PinAF::AltFunc14}, //3
		{GPIO::B, PinNum::_10, PinAF::AltFunc14}, //4
		{GPIO::F, PinNum::_11, PinAF::AltFunc14}, //5
		{GPIO::C, PinNum::_7, PinAF::AltFunc14},  //6
		{GPIO::D, PinNum::_3, PinAF::AltFunc14},  //7
	};

	static constexpr PinDef b[8]{
		{},										  //0
		{},										  //1
		{},										  //2
		{GPIO::D, PinNum::_10, PinAF::AltFunc14}, //3
		{GPIO::E, PinNum::_12, PinAF::AltFunc14}, //4
		{GPIO::A, PinNum::_3, PinAF::AltFunc14},  //5
		{GPIO::B, PinNum::_8, PinAF::AltFunc14},  //6
		{GPIO::B, PinNum::_9, PinAF::AltFunc14},  //7
	};
	static constexpr PinDef de{GPIO::E, PinNum::_13, PinAF::AltFunc14};
	static constexpr PinDef clk{GPIO::E, PinNum::_14, PinAF::AltFunc14}; //not connected on mp153-devboard-v0.2
	static constexpr PinDef actual_clk{
		GPIO::C, PinNum::_8, PinAF::AltFunc2}; //TIM3_CH3: actually connected to LCD clk pin
	static constexpr PinDef vsync{GPIO::A, PinNum::_4, PinAF::AltFunc14};
	static constexpr PinDef hsync{GPIO::C, PinNum::_6, PinAF::AltFunc14};

	static constexpr uint32_t viewWidth = 400;
	static constexpr uint32_t viewHeight = 960;

	static constexpr uint32_t HSyncWidth = 16;
	static constexpr uint32_t HBackPorch = 20;
	static constexpr uint32_t HFrontPorch = 160; //toysynth: 28, was 160

	static constexpr uint32_t VSyncWidth = 3;
	static constexpr uint32_t VBackPorch = 20;
	static constexpr uint32_t VFrontPorch = 12;
};

struct ScreenControlConf : mdrivlib::BitBangSpiTxConf {
	static constexpr PinDef data{GPIO::C, PinNum::_12};
	static constexpr PinDef chip_sel{GPIO::D, PinNum::_2};
	static constexpr PinDef clock{GPIO::C, PinNum::_10};

	static constexpr PinPolarity clk_polarity = PinPolarity::Normal;

	static constexpr uint32_t DataSetupTime = 100;
	static constexpr uint32_t ClockLowTime = 100;
	static constexpr uint32_t ClockHighTime = 100;
	static constexpr uint32_t ChipSelectSetupTime = 100;
	static constexpr uint32_t WriteLatchAfterDelay = 100;

	static constexpr PinDef reset{GPIO::C, PinNum::_11};
};

} // namespace MetaModule
