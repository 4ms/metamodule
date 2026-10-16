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

// DDR usable by our secure context is only what TF-A's RISAF4 region 1 opens:
// 0x8000'0000 - 0x9FFF'FFFF (512MB, the `ddrram` node in the TF-A dts). Outside of that,
// LTDC reads are blocked and return zeros (black screen, no error).
// Within it: 0x81FC'0000-0x83FF'FFFF is TF-A BL31 context + OP-TEE, 0x8800'0000 is our code
// image (16MB) and 0x9000'0000 is .data/.bss/heap/stacks (16MB), per the linker script.
constexpr uint32_t FramebufferAddr = 0x9100'0000;
constexpr uint32_t SecureDDREnd = 0xA000'0000;
constexpr uint32_t NumFramebuffers = 2; // double-buffered
static_assert(FramebufferAddr + NumFramebuffers * ScreenConf.panel.h_active * ScreenConf.panel.v_active * 4 <= SecureDDREnd);
} // namespace MetaModule
