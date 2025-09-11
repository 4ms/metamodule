#include "conf/screen_buffer_conf.hh"
#include "drivers/tim_pwm.hh"
#include "screen/lvgl_driver.hh"
#include <array>

namespace MetaModule
{

using FrameBufferT = std::array<lv_color_t, MetaModule::ScreenBufferConf::width * MetaModule::ScreenBufferConf::height>;
static inline FrameBufferT framebuf1 alignas(64);
static inline FrameBufferT framebuf2 alignas(64);

FrameBufferT *first_framebuf = &framebuf1;

void start_pixel_clock() {
	constexpr mdrivlib::TimChanConf conf{
		.pin = ScreenConf::actual_clk,
		.TIM = TIM3_BASE,
		.channum = mdrivlib::TimChannelNum::_3,
		.period = 23,
		// .period = 2, //period+1 = 3, so PLLQ must be 12 if pres=1 or 6 if prescaler is 0
		// .period = 4,	//period+1 = 5, so PLLQ must be 20 (pres = 1)
		.prescaler = 0, // divide by 1+prescaler
		.clock_div = 0,
	};
	mdrivlib::TimPwmChan<conf> rgbclk;
	rgbclk.set(12);
}

void init_gui() {
	mdrivlib::Pin backlight{
		{mdrivlib::GPIO::E, mdrivlib::PinNum::_4}, mdrivlib::PinMode::Output, {}, mdrivlib::PinPolarity::Normal};

	backlight.on();

	LVGLDriver gui{MMDisplay::flush_to_screen, MMDisplay::read_input, framebuf1, framebuf2};
}

// TIM3 with prescaler = 1:
// 24MHz / 2 * (34+6685/8192) / 2 / 2 / (period + 1) =
// 3 * 34+6685/8192 / (period+1)
// (104 + 3671/8192) / (period+1)
//
// LTDC
// 24MHz / 4 * (69+5178/8192) / DIVQ
// (417 + 6492/8192) / DIVQ

// period+1 / DIVQ = (855639 / 3422556)
// DIVQ = 4 * (period+1)
} // namespace MetaModule
