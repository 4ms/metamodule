#pragma once
#include "drivers/dma_config_struct.hh"
#include "drivers/pin.hh"
#include "drivers/tim_pwm.hh"

namespace MetaModule
{

namespace Neopixels
{

using mdrivlib::GPIO;
using mdrivlib::PinAF;
using mdrivlib::PinDef;
using mdrivlib::PinMode;
using mdrivlib::PinNum;

// Neopixels

// LED Line A
// B54 PA7 TIM8 CH1N (or TIM14 CH1 or TIM3 CH2 or TIM1 CH1N)
constexpr size_t num_leds_a = 40;

constexpr inline mdrivlib::TimChanConf pwm_conf_a{
	.pin = {GPIO::A, PinNum::_7, PinAF::AltFunc3},
	.TIM = TIM8_BASE,
	.channum = mdrivlib::TimChannelNum::_1N,
	.period = 129,
	.prescaler = 1,
	.clock_div = 1,
};

struct dma_conf_a : mdrivlib::DefaultDMAConf {
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

// LED Line B
// A63 PE10 TIM1 CH2N
constexpr size_t num_leds_b = 40;

constexpr inline mdrivlib::TimChanConf pwm_conf_b{
	.pin = {GPIO::E, PinNum::_10, PinAF::AltFunc1},
	.TIM = TIM1_BASE,
	.channum = mdrivlib::TimChannelNum::_2N,
	.period = 129,
	.prescaler = 1,
	.clock_div = 1,
};

struct dma_conf_b : mdrivlib::DefaultDMAConf {
	static constexpr unsigned DMAx = 1;
	static constexpr unsigned StreamNum = 2;
	static constexpr unsigned RequestNum = DMA_REQUEST_TIM1_UP;

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

// LED Line VU
// B58 PA6 TIM3 CH1
constexpr size_t num_leds_vu = 26;

constexpr inline mdrivlib::TimChanConf pwm_conf_vu{
	.pin = {GPIO::A, PinNum::_6, PinAF::AltFunc2},
	.TIM = TIM3_BASE,
	.channum = mdrivlib::TimChannelNum::_1,
	.period = 129,
	.prescaler = 1,
	.clock_div = 1,
};

struct dma_conf_vu : mdrivlib::DefaultDMAConf {
	static constexpr unsigned DMAx = 1;
	static constexpr unsigned StreamNum = 3;
	static constexpr unsigned RequestNum = DMA_REQUEST_TIM3_UP;

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

} // namespace Neopixels
} // namespace MetaModule
