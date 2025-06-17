#pragma once
#include "drivers/adc_builtin_conf.hh"
#include "drivers/adc_periph_nums.hh"
#include "drivers/dma_config_struct.hh"
#include "drivers/pin.hh"
#include "drivers/pin_change_conf.hh"
#include <array>

namespace MetaModule
{

struct FrameRatePinChangeConf : mdrivlib::DefaultPinChangeConf {
	static constexpr uint32_t pin = 4;
	static constexpr mdrivlib::GPIO port = mdrivlib::GPIO::E;
	static constexpr bool on_rising_edge = true;
	static constexpr bool on_falling_edge = false;
	static constexpr uint32_t priority1 = 0;
	static constexpr uint32_t priority2 = 3;
};

using mdrivlib::GPIO;
using mdrivlib::PinNum;

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
enum Pots : uint32_t {};
constexpr auto AdcSampTime = mdrivlib::AdcSamplingTime::_2Cycles;
constexpr std::array<AdcChannelConf, 0> PotConfs;

constexpr int32_t MinPotValue = 72;
constexpr float MaxPotValue = 4095.f - (float)MinPotValue - 4.f;

} // namespace MetaModule
