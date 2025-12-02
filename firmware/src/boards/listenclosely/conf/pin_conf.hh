#pragma once
#include "drivers/pin.hh"

#include "drivers/adc_builtin_conf.hh"
#include <array>

namespace ListenClosely
{

using mdrivlib::GPIO;
using mdrivlib::PinAF;
using mdrivlib::PinDef;
using mdrivlib::PinMode;
using mdrivlib::PinNum;

constexpr inline std::array LowSelLeds = {
	PinDef{GPIO::B, PinNum::_8},  // LED9
	PinDef{GPIO::E, PinNum::_2},  // LED10
	PinDef{GPIO::B, PinNum::_2},  // LED11
	PinDef{GPIO::F, PinNum::_11}, // LED12
};

constexpr inline std::array HighSelLeds = {
	PinDef{GPIO::E, PinNum::_4},  // LED13
	PinDef{GPIO::C, PinNum::_9},  // LED14
	PinDef{GPIO::C, PinNum::_8},  // LED15
	PinDef{GPIO::B, PinNum::_15}, // LED16
	PinDef{GPIO::A, PinNum::_8},  // LED17
};

constexpr inline std::array MidSelLeds = {
	PinDef{GPIO::E, PinNum::_13}, // LED18
	PinDef{GPIO::C, PinNum::_5},  // LED19
	PinDef{GPIO::A, PinNum::_5},  // LED20
	PinDef{GPIO::A, PinNum::_7},  // LED21
	PinDef{GPIO::C, PinNum::_0},  // LED22
	PinDef{GPIO::C, PinNum::_4},  // LED23
};

constexpr inline PinDef ClipLeftLed{GPIO::B, PinNum::_4};	// LED24
constexpr inline PinDef ClipRightLed{GPIO::B, PinNum::_14}; // LED25

constexpr inline PinDef CompSwitch0{GPIO::E, PinNum::_3}; //pull-up
constexpr inline PinDef CompSwitch1{GPIO::A, PinNum::_9}; //pull-up

// FIXME: need to add pull-ups to these:
enum GpioExpBit {
	SenseOutL = (1 << 6),
	SenseOutR = (1 << 7),
	SenseInCV = (1 << 8),
	EQSwitch_1 = (1 << 9),
	EQSwitch_0 = (1 << 10),
	SenseInR = (1 << 11),
	SenseInL = (1 << 12),
};

constexpr inline PinDef HighSelBut{GPIO::A, PinNum::_6}; // pull-up
constexpr inline PinDef MidSelBut{GPIO::A, PinNum::_4};	 // pull-up
constexpr inline PinDef LowSelBut{GPIO::G, PinNum::_13}; // pull-up

///// ADC

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
enum Pots : uint32_t { Amount, MakeupGain, DryWet, LowShelf, MidBand, HighShelf, WidthPot, EQLevel, WidthCV };
constexpr auto AdcSampTime = mdrivlib::AdcSamplingTime::_2Cycles;
constexpr auto PotConfs = std::to_array({
	AdcChannelConf{{GPIO::B, PinNum::_0}, mdrivlib::AdcChanNum::_9, WidthCV, AdcSampTime},
	AdcChannelConf{{GPIO::C, PinNum::_1}, mdrivlib::AdcChanNum::_11, EQLevel, AdcSampTime},
	AdcChannelConf{{GPIO::B, PinNum::_1}, mdrivlib::AdcChanNum::_5, WidthPot, AdcSampTime},
	AdcChannelConf{{GPIO::C, PinNum::_2}, mdrivlib::AdcChanNum::_12, HighShelf, AdcSampTime},
	AdcChannelConf{{GPIO::A, PinNum::_1}, mdrivlib::AdcChanNum::_17, MidBand, AdcSampTime},
	AdcChannelConf{{GPIO::A, PinNum::_2}, mdrivlib::AdcChanNum::_14, LowShelf, AdcSampTime},
	AdcChannelConf{{GPIO::A, PinNum::_3}, mdrivlib::AdcChanNum::_15, DryWet, AdcSampTime},
	AdcChannelConf{{GPIO::C, PinNum::_3}, mdrivlib::AdcChanNum::_13, MakeupGain, AdcSampTime},
	AdcChannelConf{{GPIO::A, PinNum::_0}, mdrivlib::AdcChanNum::_16, Amount, AdcSampTime},
});

constexpr int32_t MinPotValue = 72; // more like 69, actually 0x3D = 61
constexpr float MaxPotValue = 4095.f - (float)MinPotValue - 4.f;

} // namespace ListenClosely
