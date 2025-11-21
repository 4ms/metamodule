#include "conf/screen_conf.hh"
#include "drivers/tim_pwm.hh"

namespace MetaModule
{

void start_pixel_clock() {
	constexpr mdrivlib::TimChanConf conf{
		.pin = ScreenConf::actual_clk,
		.TIM = TIM3_BASE,
		.channum = mdrivlib::TimChannelNum::_3,
		// .period = 5, //~60Hz refresh (with RCC PLLQ = 12)
		.period = 11,	//~30Hz refresh (with rcc PLLQ = 24)
		.prescaler = 0, // divide by 1+prescaler
		.clock_div = 0,
	};
	mdrivlib::TimPwmChan<conf> rgbclk;
	TIM3->CR1 |= TIM_CR1_DIR; //down counter
	rgbclk.set(3);
}

void init_gui() {
	printf("init_gui()\n");
	mdrivlib::Pin backlight{ScreenConf::PWMBackLight, mdrivlib::PinMode::Output, {}, mdrivlib::PinPolarity::Normal};

	backlight.on();
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
