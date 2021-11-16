#pragma once
#include "conf/screen_buffer_conf.hh"
#include "drivers/ltdc_screen_config_struct.hh"
#include "drivers/parallel_writer_conf.hh"
#include "pin.hh"

namespace MetaModule
{

using mdrivlib::GPIO;
using mdrivlib::PinNoInit;

struct ScreenConf : mdrivlib::LTDCScreenConf {
	static constexpr PinNoInit r[8]{
		{GPIO::Unused},
		{GPIO::Unused},
		{GPIO::Unused},
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
		{GPIO::Unused},
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

	static constexpr uint32_t HSyncWidth = 10;
	static constexpr uint32_t HBackPorch = 10;
	static constexpr uint32_t HFrontPorch = 38;
	static constexpr uint32_t VSyncWidth = 4;
	static constexpr uint32_t VBackPorch = 4;
	static constexpr uint32_t VFrontPorch = 8;

	// TODO: remove if not used
	static constexpr bool IsInverted = false;
	//  using FrameBufferT = MMScreenBufferConf::FrameBufferT;
	//  static constexpr uint32_t FrameBytes = sizeof(FrameBufferT);
};

struct ScreenControlConf : mdrivlib::ParallelWriterConf {
	static constexpr size_t BusWidth = 8;
	static constexpr std::array<PinNoInit, BusWidth> data{{
		{ScreenConf::b[3].gpio, ScreenConf::b[3].pin},
		{ScreenConf::b[4].gpio, ScreenConf::b[4].pin},
		{ScreenConf::b[5].gpio, ScreenConf::b[5].pin},
		{ScreenConf::b[6].gpio, ScreenConf::b[6].pin},
		{ScreenConf::b[7].gpio, ScreenConf::b[7].pin},
		{ScreenConf::g[2].gpio, ScreenConf::g[2].pin},
		{ScreenConf::g[3].gpio, ScreenConf::g[3].pin},
		{ScreenConf::g[4].gpio, ScreenConf::g[4].pin},
	}};
	static constexpr PinNoInit chip_sel{GPIO::E, 11};	 //pin 38: "CSX"
	static constexpr PinNoInit write_latch{GPIO::H, 5};	 //pin 36: "DC" on p5 schematic, "WRX" in ST7789V datasheet
	static constexpr PinNoInit datacmd_sel{GPIO::E, 12}; //pin 37: "SCK" on p5 schematic, "DCX" in ST7789V datasheet

	static constexpr uint32_t DataSetupTime = 3;		//ST7789V datasheet: Sec 7.4.1. T(DST) = 10ns
	static constexpr uint32_t WriteLatchAfterDelay = 3; //ST7789V datasheet: Sec 7.4.1. T(AHT) = 10ns
};

} // namespace MetaModule
