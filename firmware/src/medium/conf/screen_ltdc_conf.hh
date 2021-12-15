#pragma once
#include "conf/screen_buffer_conf.hh"
#include "drivers/ltdc_screen_config_struct.hh"
#include "drivers/parallel_writer_conf.hh"
//#include "drivers/spi_screen_ST77XX.hh"
#include "drivers/screen_ILI9341.hh"
#include "pin.hh"

namespace MetaModule
{

using mdrivlib::GPIO;
using mdrivlib::PinNoInit;

struct ScreenConf : mdrivlib::LTDCScreenConf {
	static constexpr PinNoInit r[8]{
		{GPIO::Unused},
		{GPIO::Unused},
		{GPIO::H, 8, LL_GPIO_AF_14},  // LTDC_R2
		{GPIO::H, 9, LL_GPIO_AF_14},  // LTDC_R3
		{GPIO::H, 10, LL_GPIO_AF_14}, // LTDC_R4
		{GPIO::A, 9, LL_GPIO_AF_14},  // LTDC_R5
		{GPIO::A, 8, LL_GPIO_AF_14},  // LTDC_R6
		{GPIO::G, 6, LL_GPIO_AF_14},  // LTDC_R7
	};
	static constexpr PinNoInit g[8]{
		{GPIO::Unused},
		{GPIO::Unused},
		{GPIO::H, 13, LL_GPIO_AF_14}, // LTDC_G2
		{GPIO::H, 14, LL_GPIO_AF_14}, // LTDC_G3
		{GPIO::H, 15, LL_GPIO_AF_14}, // LTDC_G4
		{GPIO::H, 4, LL_GPIO_AF_9},	  // LTDC_G5
		{GPIO::C, 7, LL_GPIO_AF_14},  // LTDC_G6
		{GPIO::D, 3, LL_GPIO_AF_14},  // LTDC_G7

	};
	static constexpr PinNoInit b[8]{
		{GPIO::Unused},
		{GPIO::Unused},
		{GPIO::G, 10, LL_GPIO_AF_14}, // LTDC_B2
		{GPIO::D, 10, LL_GPIO_AF_14}, // LTDC_B3
		{GPIO::I, 4, LL_GPIO_AF_14},  // LTDC_B4
		{GPIO::I, 5, LL_GPIO_AF_14},  // LTDC_B5
		{GPIO::I, 6, LL_GPIO_AF_14},  // LTDC_B6
		{GPIO::I, 7, LL_GPIO_AF_14},  // LTDC_B7
	};
	static constexpr PinNoInit de{GPIO::E, 13, LL_GPIO_AF_14};
	static constexpr PinNoInit clk{GPIO::E, 14, LL_GPIO_AF_14};
	static constexpr PinNoInit vsync{GPIO::I, 9, LL_GPIO_AF_14};
	static constexpr PinNoInit hsync{GPIO::C, 6, LL_GPIO_AF_14};

	static constexpr uint32_t width = ScreenBufferConf::width;
	static constexpr uint32_t height = ScreenBufferConf::height;
	static constexpr uint32_t viewWidth = ScreenBufferConf::viewWidth;
	static constexpr uint32_t viewHeight = ScreenBufferConf::viewHeight;
	static constexpr uint32_t rowstart = 0;
	static constexpr uint32_t colstart = 0;

	enum Rotation { NoRotation, CW90, Flip180, CCW90 };
	static constexpr Rotation rotation = CW90;

	enum ColorFormat { RGBA8888, RGB888, RGB565 };
	static constexpr ColorFormat color_format = RGB565;

	static constexpr uint32_t HSyncWidth = 8;
	static constexpr uint32_t HBackPorch = 12;
	static constexpr uint32_t HFrontPorch = 12; //38
	static constexpr uint32_t VSyncWidth = 4;
	static constexpr uint32_t VBackPorch = 2;
	static constexpr uint32_t VFrontPorch = 8;

	// 262us Vsync pulse width (low)
	// = 1523 pixel clocks (172ns each px ck)

	// TODO: remove if not used
	static constexpr bool IsInverted = false;
	//  using FrameBufferT = MMScreenBufferConf::FrameBufferT;
	//  static constexpr uint32_t FrameBytes = sizeof(FrameBufferT);
};

struct ScreenControlConf : mdrivlib::ParallelWriterConf {
	static constexpr size_t BusWidth = 8;
	static constexpr std::array<PinNoInit, BusWidth> data{{
		{ScreenConf::b[2].gpio, ScreenConf::b[2].pin}, //comment out for p5
		{ScreenConf::b[3].gpio, ScreenConf::b[3].pin},
		{ScreenConf::b[4].gpio, ScreenConf::b[4].pin},
		{ScreenConf::b[5].gpio, ScreenConf::b[5].pin},
		{ScreenConf::b[6].gpio, ScreenConf::b[6].pin},
		{ScreenConf::b[7].gpio, ScreenConf::b[7].pin},
		{ScreenConf::g[2].gpio, ScreenConf::g[2].pin},
		{ScreenConf::g[3].gpio, ScreenConf::g[3].pin},
		// {ScreenConf::g[4].gpio, ScreenConf::g[4].pin}, //uncomment for p6, comment for p6
	}};
	static constexpr PinNoInit chip_sel{GPIO::E, 11};	 //pin 38: "CSX"
	static constexpr PinNoInit write_latch{GPIO::H, 5};	 //pin 36: "DC" on p5 schematic, "WRX" in ST7789V datasheet
	static constexpr PinNoInit datacmd_sel{GPIO::E, 12}; //pin 37: "SCK" on p5 schematic, "DCX" in ST7789V datasheet
	static constexpr PinNoInit reset{GPIO::E, 15};

	static constexpr uint32_t DataSetupTime = 3;		//ST7789V datasheet: Sec 7.4.1. T(DST) = 10ns
	static constexpr uint32_t WriteLatchAfterDelay = 3; //ST7789V datasheet: Sec 7.4.1. T(AHT) = 10ns
};

//FixMe: gcc 10.2 doesn't support using enum?
//using namespace mdrivlib::ST77XX;
//struct ST7789RGBInit {
//	using ConfT = ScreenConf;
//	using InitCommand = mdrivlib::ST77XX::InitCommand;
//	// using enum mdrivlib::ST77XX::Command;
//	// using enum mdrivlib::ST77XX::MADCTL_Rotation;
//	// using enum mdrivlib::ST77XX::RAMCTRL_Args;
//	// using enum mdrivlib::ST77XX::COLMOD_Args;
//	// using enum mdrivlib::ST77XX::MADCTL_Arg;

//	static constexpr std::array cmds = {
//		InitCommand{SLPIN, 0, 10},
//		InitCommand{SWRESET, 0, 150},
//		InitCommand{SLPOUT, 0, 120},

//		InitCommand{MADCTL,
//					1,
//					0,
//					ConfT::rotation == ConfT::NoRotation ? MADCTL_ROT0
//					: ConfT::rotation == ConfT::CW90	 ? MADCTL_ROTCW90
//					: ConfT::rotation == ConfT::Flip180	 ? MADCTL_ROT180
//														 : MADCTL_ROTCCW90},

//		InitCommand{COLMOD, 1, 0, 0x55},

//		InitCommand{ConfT::IsInverted == mdrivlib::ST77XX::Inverted ? INVON : INVOFF, 0, 0},

//		InitCommand{CASET, 4, 0, InitCommand::makecmd(0, ConfT::viewWidth)},
//		InitCommand{RASET, 4, 0, InitCommand::makecmd(0, ConfT::viewHeight)},

//		//// seq 2
//		//Enable Table 2 Commands:
//		InitCommand{CMD2EN, 4, 1, InitCommand::makecmd(0x5A, 0x69, 0x02, 0x01)},

//		// RGB Control: V/H back porch
//		InitCommand{
//			RGBCTRL,
//			3,
//			0,
//			InitCommand::makecmd(
//				RGBCTRL_DE_Mode | RGBCTRL_UseRAM, ConfT::VBackPorch, ConfT::HBackPorch /*+ ConfT::HSyncWidth*/, 0)},

//		// RAM Control: set RGB mode. EPF and MTD don't matter
//		InitCommand{RAMCTRL, 2, 0, InitCommand::makecmd(RAMCTRL_RGB_IF, RAMCTRL_EPF_DEFAULT, 0, 0)},

//		InitCommand{FRCTRL2, 1, 10, 0x0F}, //0x0F = 60Hz, 0x0E = 62Hz

//		//InitCommand{GCTRL, 4, 10, InitCommand::makecmd(0x2A, 0x2B, 0x22 + 6, 0x75)},

//		//InitCommand{CABCCTRL, 1, 10, 0b0010}, //LED no reversed, init state LEDPWM low, LEDPWM fixed to on, LEDPWM Polarity 0/high

//		//InitCommand{PWMFRSEL, 1, 10, (0x04 << 3) | 0x00}, //CS = 4, CLK = 0 => 666kHz PWM

//		// Porch setting: Not sure if this wants V or H porch?
//		// InitCommand{PORCTRL, 3, 0, InitCommand::makecmd(ConfT::HBackPorch, ConfT::HFrontPorch, 0, 0)},

//		//Max brightness
//		// InitCommand{WRDISBV, 1, 0, 0xFF0000FF},

//		// Normal display on
//		// InitCommand{NORON, 0, 10},

//		InitCommand{DISPON, 0, 100},
//		InitCommand{SLPOUT, 0, 100},
//		InitCommand{RAMWR, 0, 50},
//	};
//};
} // namespace MetaModule
