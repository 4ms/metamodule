#pragma once
#include "drivers/rcc_pll.hh"
#include "drivers/rcc_xbar.hh"

// Clocks the A35 app sets up itself. TF-A BL2 has already set up:
// PLL1 (CPU), PLL2 (DDR), PLL4 (1200MHz, used for LTDC/DSI and USB PHY), and I2C7 (PMIC).
//
// Flexgen channel numbers are the MP25x default mapping (stm32mp2xx_hal_rcc_ex.h)

namespace MetaModule::RccConf
{

// Audio PLL: 48kHz * 256 * 68 = 835.584MHz (verified in stm32mp2-baremetal hal-audio)
constexpr mdrivlib::RCC_Clocks::PLLSettings AudioPLL8{
	.src = mdrivlib::RCC_Clocks::MuxSelSource::hse,
	.mult = 167,
	.refdiv = 4,
	.postdiv1 = 1,
	.postdiv2 = 2,
	.frac = 0x1DE69B,
};
static_assert(AudioPLL8.calc_freq(40'000'000) >= 835'584'000);
static_assert(AudioPLL8.calc_freq(40'000'000) <= 835'584'100);

// SAI1 kernel clock: PLL8 / 17 = 49.152MHz = 1024 * 48kHz
// (SAI then divides down MCLK = 256fs for 48kHz or 96kHz)
constexpr unsigned SAI1_FlexgenChan = 23;
constexpr mdrivlib::FlexbarConf SAI1_KernelClock{.PLL = mdrivlib::FlexbarConf::PLLx::_8, .findiv = 16, .prediv = 0};

// I2C kernel clocks: HSI (64MHz) / 4 = 16MHz. Timings in i2c_conf.hh assume this.
constexpr unsigned I2C1_2_FlexgenChan = 12;
constexpr unsigned I2C3_5_FlexgenChan = 13;
constexpr unsigned I2C4_6_FlexgenChan = 14;
constexpr mdrivlib::FlexbarConf I2C_KernelClock{
	.PLL = mdrivlib::FlexbarConf::PLLx::HSI, .findiv = 3, .prediv = 0};

} // namespace MetaModule::RccConf
