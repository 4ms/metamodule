#pragma once
#include "conf/screen_buffer_conf.hh"
#include "drivers/ltdc_screen_config_struct.hh"

using mdrivlib::FPin;
using mdrivlib::GPIO;
using mdrivlib::PinMode;
using mdrivlib::PinNoInit;

// static constexpr PinNoInit SCLK = {GPIO::E, 12, LL_GPIO_AF_5};
// static constexpr PinNoInit COPI = {GPIO::E, 6, LL_GPIO_AF_5}; // p4: PE14
// static constexpr PinNoInit CIPO = {GPIO::A, 0};
// static constexpr PinNoInit CS0 = {GPIO::E, 11, LL_GPIO_AF_5};
// using DCPin = FPin<GPIO::H, 5, PinMode::Output>; // p4: PH4

namespace MetaModule
{
struct ScreenConf : mdrivlib::LTDCScreenConf {
	static constexpr PinNoInit r[8]{};
	static constexpr PinNoInit g[8]{};
	static constexpr PinNoInit b[8]{};
	static constexpr PinNoInit de{};
	static constexpr PinNoInit clk{};
	static constexpr PinNoInit vsync{};
	static constexpr PinNoInit hsync{};

	static constexpr uint32_t width = MMScreenBufferConf::width;
	static constexpr uint32_t height = MMScreenBufferConf::height;
	static constexpr uint32_t rowstart = 0;
	static constexpr uint32_t colstart = 0;

	enum Rotation { None, CW90, Flip180, CCW90 };
	static constexpr Rotation rotation = CW90;

	enum ColorFormat { RGBA8888, RGB888, RGB565 };
	static constexpr ColorFormat color_format = RGB565;

	static constexpr uint32_t HSyncWidth = 0;
	static constexpr uint32_t HBackPorch = 0;
	static constexpr uint32_t HFrontPorch = 0;
	static constexpr uint32_t VSyncWidth = 0;
	static constexpr uint32_t VBackPorch = 0;
	static constexpr uint32_t VFrontPorch = 0;

	// TODO: remove if not used
	//  static constexpr bool IsInverted = false;
	//  using FrameBufferT = MMScreenBufferConf::FrameBufferT;
	//  static constexpr uint32_t FrameBytes = sizeof(FrameBufferT);
};

struct MMScreenControlConf : mdrivlib::LTDCScreenControlConf {
	static constexpr PinNoInit cs{};
	static constexpr PinNoInit serial_data_out{};
	static constexpr PinNoInit serial_write{};
	static constexpr PinNoInit serial_datacmd_sel{};

	using ScreenConf = ScreenConf;
};
} // namespace MetaModule
