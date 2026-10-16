#pragma once
#include "drivers/dsi_screen.hh"
#include "drivers/panels/ili9881c.hh"

// Display: ER-TFT050-10 (ILI9881C) on J11, 4-lane MIPI DSI
namespace MetaModule
{
constexpr mdrivlib::DsiScreenConf ScreenConf{
	.panel = mdrivlib::Panels::ER_TFT050_10,
	.reset_pin = {mdrivlib::GPIO::I, mdrivlib::PinNum::_6, mdrivlib::PinAF::AFNone}, // SCREEN_RESET
	.reset_active_low = true,
	.backlight_pin = {mdrivlib::GPIO::I, mdrivlib::PinNum::_5, mdrivlib::PinAF::AFNone}, // SCREEN_LED_ENABLE
	.backlight_active_high = true, // AP3012 ~SHDN. TODO: PWM dimming via TIM5_CH2 (AF8)
	.hse_hz = 40'000'000,
	.pixel_format = mdrivlib::DsiScreenConf::PixelFormat::ARGB8888,
	.irq_pri1 = 0,
	.irq_pri2 = 0,
};

// DDR: 0x88000000 is the code image, 0x90000000 is .data/.bss/heap (linker script)
constexpr uint32_t FramebufferAddr = 0xA000'0000;
} // namespace MetaModule
