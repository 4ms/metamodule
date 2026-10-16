#pragma once
#include "drivers/dsi_screen.hh"
#include "drivers/panels/ili9881c.hh"

// Display: ER-TFT050-10 (ILI9881C) on J11, 4-lane MIPI DSI
namespace MetaModule
{
constexpr mdrivlib::DsiScreenConf ScreenConf{
	.panel = mdrivlib::Panels::ER_TFT050_10,
#ifdef MP2_TEST_CARRIER
	.reset_pin = {mdrivlib::GPIO::H, mdrivlib::PinNum::_7, mdrivlib::PinAF::AFNone}, // breakout wiring (= stm32mp2-baremetal)
#else
	.reset_pin = {mdrivlib::GPIO::I, mdrivlib::PinNum::_6, mdrivlib::PinAF::AFNone}, // SCREEN_RESET
#endif
	.reset_active_low = true,
	.backlight_pin = {mdrivlib::GPIO::I, mdrivlib::PinNum::_5, mdrivlib::PinAF::AFNone}, // SCREEN_LED_ENABLE
	.backlight_active_high = true, // AP3012 ~SHDN. TODO: PWM dimming via TIM5_CH2 (AF8)
	.hse_hz = 40'000'000,
	.pixel_format = mdrivlib::DsiScreenConf::PixelFormat::ARGB8888,
	.irq_pri1 = 0,
	.irq_pri2 = 0,
};

// Framebuffers go in the .framebuffers linker section (FRAMEBUF region, see
// system/stm32mp2xx_ca35.ld), which is inside the DDR that TF-A opens to the LTDC.
} // namespace MetaModule
