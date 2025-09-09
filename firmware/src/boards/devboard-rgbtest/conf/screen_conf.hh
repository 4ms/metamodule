#pragma once
#include "conf/screen_buffer_conf.hh"
#include "drivers/dma_config_struct.hh"
#include "drivers/dma_transfer.hh"
#include "drivers/interrupt.hh"
#include "drivers/ltdc_screen_config_struct.hh"

namespace MetaModule
{
using mdrivlib::FPin;
using mdrivlib::GPIO;
using mdrivlib::PinAF;
using mdrivlib::PinDef;
using mdrivlib::PinMode;
using mdrivlib::PinNum;

struct MMScreenConf : mdrivlib::LTDCScreenConf {

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
	static constexpr PinDef clk{GPIO::C, PinNum::_8, PinAF::AltFunc2}; //TIM3_CH3
	static constexpr PinDef vsync{GPIO::A, PinNum::_4, PinAF::AltFunc14};
	static constexpr PinDef hsync{GPIO::C, PinNum::_6, PinAF::AltFunc14};

	static constexpr uint32_t width = 400;
	static constexpr uint32_t height = 960;
	static constexpr uint32_t rowstart = 80;
	static constexpr uint32_t colstart = 0;

	enum Rotation { NoRotation, CW90, Flip180, CCW90 };
	static constexpr Rotation rotation = NoRotation;

	enum ColorFormat { RGBA8888, RGB888, RGB565 };
	static constexpr ColorFormat color_format = RGB565;

	static constexpr uint32_t HSyncWidth = 0;
	static constexpr uint32_t HBackPorch = 0;
	static constexpr uint32_t HFrontPorch = 0;
	static constexpr uint32_t VSyncWidth = 0;
	static constexpr uint32_t VBackPorch = 0;
	static constexpr uint32_t VFrontPorch = 0;

	// bit-banged
	static constexpr PinDef SCLK = {GPIO::C, PinNum::_10};
	static constexpr PinDef COPI = {GPIO::C, PinNum::_11};
	static constexpr PinDef CS0 = {GPIO::D, PinNum::_2};
	static constexpr PinDef ResetPin{GPIO::C, PinNum::_11};
};

} // namespace MetaModule
