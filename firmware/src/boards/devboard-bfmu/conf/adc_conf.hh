#pragma once
#include "drivers/adc_builtin_conf.hh"
#include "drivers/adc_periph_nums.hh"
#include "drivers/dma_config_struct.hh"
#include "drivers/pin.hh"
#include <array>

namespace MetaModule
{

namespace ADCs
{
using mdrivlib::AdcChannelConf;
using mdrivlib::GPIO;
using mdrivlib::PinDef;
using mdrivlib::PinNum;

constexpr auto AdcSampTime = mdrivlib::AdcSamplingTime::_2Cycles;

enum Adcs : uint32_t { Mux1, Mux2, Mux3, Mux4, Mux5, VOct, CV1, CV2, CV3, CV4 };

constexpr inline auto AdcPins = std::array{
	AdcChannelConf{{GPIO::A, PinNum::_0}, mdrivlib::AdcChanNum::_16, Mux1, AdcSampTime},
	AdcChannelConf{{GPIO::A, PinNum::_3}, mdrivlib::AdcChanNum::_15, Mux2, AdcSampTime},
	AdcChannelConf{{GPIO::C, PinNum::_3}, mdrivlib::AdcChanNum::_13, Mux3, AdcSampTime},
	AdcChannelConf{{GPIO::C, PinNum::_2}, mdrivlib::AdcChanNum::_12, Mux4, AdcSampTime},
	AdcChannelConf{{GPIO::C, PinNum::_1}, mdrivlib::AdcChanNum::_11, Mux5, AdcSampTime},
	AdcChannelConf{{GPIO::A, PinNum::_1}, mdrivlib::AdcChanNum::_17, VOct, AdcSampTime},
	AdcChannelConf{{GPIO::B, PinNum::_0}, mdrivlib::AdcChanNum::_9, CV1, AdcSampTime},
	AdcChannelConf{{GPIO::A, PinNum::_2}, mdrivlib::AdcChanNum::_14, CV2, AdcSampTime},
	AdcChannelConf{{GPIO::B, PinNum::_1}, mdrivlib::AdcChanNum::_5, CV3, AdcSampTime},
	AdcChannelConf{{GPIO::C, PinNum::_5}, mdrivlib::AdcChanNum::_8, CV4, AdcSampTime},
};

// Mux select
constexpr inline PinDef mux_a{GPIO::F, PinNum::_11};
constexpr inline PinDef mux_b{GPIO::E, PinNum::_2};
constexpr inline PinDef mux_c{GPIO::G, PinNum::_13};

// Can set this if the ADCs aren't going full range
constexpr int32_t MinPotValue = 0;
constexpr float MaxPotValue = 4095.f - (float)MinPotValue;

// ADC DMA:
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
		static constexpr auto circular = false; // Not free-running: need to update the MUX between sequences
	};
};

} // namespace ADCs

} // namespace MetaModule
