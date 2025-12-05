#pragma once
#include "drivers/dma_config_struct.hh"
#include "drivers/pin.hh"
#include "drivers/tim_pwm.hh"

namespace MetaModule
{

namespace ControlPins
{

using mdrivlib::GPIO;
using mdrivlib::PinAF;
using mdrivlib::PinDef;
using mdrivlib::PinMode;
using mdrivlib::PinNum;

// Neopixels
constexpr inline PinDef neopixel_b{GPIO::E, PinNum::_10};
// B58 PA6 TIM3 CH1 (or TIM13 CH1)
constexpr inline PinDef neopixel_vu{GPIO::A, PinNum::_6};

// LED Line A
// B54 PA7 TIM8 CH1N (or TIM14 CH1 or TIM3 CH2 or TIM1 CH1N)
constexpr size_t NeopixelNumLedsA = 40;

constexpr inline mdrivlib::TimChanConf NeopixelPWMConfA{
	.pin = {GPIO::A, PinNum::_7, PinAF::AltFunc3},
	.TIM = TIM8_BASE,
	.channum = mdrivlib::TimChannelNum::_1N,
	.period = 129,
	.prescaler = 1,
	.clock_div = 1,
};

struct NeopixelDMAConfA : mdrivlib::DefaultDMAConf {
	static constexpr unsigned DMAx = 1;
	static constexpr unsigned StreamNum = 1;
	static constexpr unsigned RequestNum = DMA_REQUEST_TIM8_UP;

	static constexpr Direction dir = Mem2Periph;

	static constexpr bool circular = true;
	static constexpr bool periph_flow = false;

	static constexpr TransferSize transfer_size_mem = HalfWord;
	static constexpr TransferSize transfer_size_periph = HalfWord;

	static constexpr uint8_t dma_priority = Low;

	static constexpr bool mem_inc = true;
	static constexpr bool periph_inc = false;

	static constexpr bool enable_fifo = true;
	static constexpr FifoThreshold fifo_threshold = FifoHalfFull;
};

} // namespace ControlPins
} // namespace MetaModule
