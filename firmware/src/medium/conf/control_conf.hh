#pragma once
#include "conf/panel_conf.hh"
#include "drivers/adc_builtin_conf.hh"
#include "drivers/dma_config_struct.hh"
#include "drivers/pin.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"

namespace MetaModule
{

const mdrivlib::TimekeeperConfig control_read_tim_conf = {
	.TIMx = TIM6,
	.period_ns = 20000, // must be just a hair faster than 48kHz
	.priority1 = 2,		// same group as global Semaphore unlock, so that
	.priority2 = 3,
};

using mdrivlib::GPIO;
using mdrivlib::PinNoInit;
using mdrivlib::PinPull;

struct MMControlPins {
	static constexpr PinNoInit rotA{GPIO::D, 5};
	static constexpr PinNoInit rotB{GPIO::E, 13};
	static constexpr PinNoInit rotS{GPIO::E, 15};
	static constexpr PinNoInit but0{GPIO::D, 8};
	static constexpr PinNoInit gate_in_1{GPIO::F, 11};
	static constexpr PinNoInit gate_in_2{GPIO::B, 8};
};

struct PotAdcConf : mdrivlib::DefaultAdcPeriphConf {
	static constexpr mdrivlib::AdcResolution resolution = mdrivlib::Bits12;
	static constexpr auto adc_periph_num = mdrivlib::AdcPeriphNum::_1;
	static constexpr auto oversample = true;
	static constexpr auto oversampling_ratio = 1024;
	static constexpr auto oversampling_right_bitshift = mdrivlib::AdcOversampleRightBitShift::Shift10Right;
	static constexpr auto clock_div = mdrivlib::PLL_Div1;

	static constexpr bool enable_end_of_sequence_isr = true;
	static constexpr bool enable_end_of_conversion_isr = false;

	struct DmaConf : mdrivlib::DefaultAdcPeriphConf::DmaConf {
		static constexpr auto DMAx = 2;
		static constexpr auto StreamNum = 7;
		static constexpr auto RequestNum = DMA_REQUEST_ADC1;
		static constexpr auto dma_priority = Low;
	};
};

using mdrivlib::AdcChannelConf;
enum Pots : uint32_t { PotA, PotB, PotC, PotD, PotE, PotF, PotU, PotV, PotW, PotX, PotY, PotZ };
constexpr auto AdcSampTime = mdrivlib::AdcSamplingTime::_2Cycles;
constexpr auto PotConfs = std::to_array({
	AdcChannelConf{{GPIO::A, 6}, mdrivlib::AdcChanNum::_3, PotA, AdcSampTime},
	AdcChannelConf{{GPIO::A, 2}, mdrivlib::AdcChanNum::_14, PotB, AdcSampTime},
	AdcChannelConf{{GPIO::B, 0}, mdrivlib::AdcChanNum::_9, PotC, AdcSampTime},
	AdcChannelConf{{GPIO::C, 1}, mdrivlib::AdcChanNum::_11, PotD, AdcSampTime},
	AdcChannelConf{{GPIO::C, 3}, mdrivlib::AdcChanNum::_13, PotE, AdcSampTime},
	AdcChannelConf{{GPIO::A, 4}, mdrivlib::AdcChanNum::_18, PotF, AdcSampTime},
	AdcChannelConf{{GPIO::C, 5}, mdrivlib::AdcChanNum::_8, PotU, AdcSampTime},
	AdcChannelConf{{GPIO::B, 1}, mdrivlib::AdcChanNum::_5, PotV, AdcSampTime},
	AdcChannelConf{{GPIO::A, 7}, mdrivlib::AdcChanNum::_7, PotW, AdcSampTime},
	AdcChannelConf{{GPIO::A, 3}, mdrivlib::AdcChanNum::_15, PotX, AdcSampTime},
	AdcChannelConf{{GPIO::A, 5}, mdrivlib::AdcChanNum::_19, PotY, AdcSampTime},
	AdcChannelConf{{GPIO::C, 2}, mdrivlib::AdcChanNum::_12, PotZ, AdcSampTime},
});

} // namespace MetaModule
