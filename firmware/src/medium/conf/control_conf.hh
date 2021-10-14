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

template<GPIO port, uint16_t pin>
using FPin = mdrivlib::FPin<port, pin, mdrivlib::PinMode::Input>;

struct MMControlPins {
	static constexpr PinNoInit rotA{GPIO::A, 15};
	static constexpr PinNoInit rotB{GPIO::C, 7};
	static constexpr PinNoInit rotS{GPIO::B, 14};

	static constexpr PinNoInit but0{GPIO::I, 2};

	static constexpr PinNoInit gate_in_1{GPIO::I, 3};
	static constexpr PinNoInit gate_in_2{GPIO::H, 9};
};

using mdrivlib::AdcChannelConf;

struct PotAdcConf : mdrivlib::DefaultAdcPeriphConf {
	static constexpr auto adc_periph_num = mdrivlib::AdcPeriphNum::_1;
	static constexpr auto oversample = true;
	static constexpr auto oversampling_ratio = 256;
	static constexpr auto oversampling_right_bitshift = mdrivlib::AdcOversampleRightBitShift::Shift8Right;
	static constexpr auto clock_div = mdrivlib::PLL_Div2;

	struct DmaConf : mdrivlib::DefaultAdcPeriphConf::DmaConf {
		static constexpr auto DMAx = 2;
		static constexpr auto StreamNum = 7;
		static constexpr auto RequestNum = DMA_REQUEST_ADC1;
		static constexpr auto dma_priority = High;
	};
};

enum Pots : uint32_t { PotA, PotB, PotC, PotD, PotE, PotF, PotX, PotY, PotZ, PotQ, PotL, PotR, PatchCV };

constexpr auto AdcSampTime = mdrivlib::AdcSamplingTime::_64Cycles;

constexpr auto PotConfs = std::to_array({
	AdcChannelConf{{GPIO::B, 1}, mdrivlib::AdcChanNum::_5, PotA, AdcSampTime},
	AdcChannelConf{{GPIO::C, 3}, mdrivlib::AdcChanNum::_13, PotB, AdcSampTime},
	AdcChannelConf{{GPIO::A, 3}, mdrivlib::AdcChanNum::_15, PotC, AdcSampTime},
	AdcChannelConf{{GPIO::F, 12}, mdrivlib::AdcChanNum::_6, PotD, AdcSampTime},
	AdcChannelConf{{GPIO::A, 5}, mdrivlib::AdcChanNum::_19, PotE, AdcSampTime},
	AdcChannelConf{{GPIO::C, 0}, mdrivlib::AdcChanNum::_10, PotF, AdcSampTime},
	//PotX is ANA0. hack: use PF13 here to set it to analog mode, since on PCB p4 we have it connected to Pot9
	AdcChannelConf{{GPIO::F, 13}, mdrivlib::AdcChanNum::_0, PotX, AdcSampTime},
	//PotY is ANA1. hack: use PF14 here to set it to analog mode, since on PCB p4 we have it connected to Pot10
	AdcChannelConf{{GPIO::F, 14}, mdrivlib::AdcChanNum::_1, PotY, AdcSampTime},
	//Z = Pot9 on sch: was PF13 on p4 PCB: changed to PA1
	AdcChannelConf{{GPIO::A, 1}, mdrivlib::AdcChanNum::_17, PotZ, AdcSampTime},
	//Q = Pot10 on sch: was PF14 on p4 PCB: changed to PC5
	AdcChannelConf{{GPIO::C, 5}, mdrivlib::AdcChanNum::_8, PotQ, AdcSampTime},
	AdcChannelConf{{GPIO::A, 6}, mdrivlib::AdcChanNum::_3, PotL, AdcSampTime},
	AdcChannelConf{{GPIO::C, 1}, mdrivlib::AdcChanNum::_11, PotR, AdcSampTime},
	AdcChannelConf{{GPIO::A, 4}, mdrivlib::AdcChanNum::_18, PatchCV, AdcSampTime},
});

//TODO: parameterize this and put it in mdrivlib
struct MultiGPIOReader {
	using AudioIn1 = FPin<GPIO::I, 5>;
	using AudioIn2 = FPin<GPIO::G, 12>;
	using AudioIn3 = FPin<GPIO::D, 14>;
	using AudioIn4 = FPin<GPIO::A, 7>;
	using AudioIn5 = FPin<GPIO::A, 14>;
	using AudioIn6 = FPin<GPIO::D, 8>;
	using AudioOut1 = FPin<GPIO::A, 2>;
	using AudioOut2 = FPin<GPIO::B, 12>;
	using AudioOut3 = FPin<GPIO::B, 13>;
	using AudioOut4 = FPin<GPIO::D, 11>;
	using AudioOut5 = FPin<GPIO::B, 0>;
	using AudioOut6 = FPin<GPIO::B, 10>;
	using AudioOut7 = FPin<GPIO::C, 4>;
	using AudioOut8 = FPin<GPIO::D, 13>;
	using PatchCV = FPin<GPIO::G, 6>;
	using GateIn1 = FPin<GPIO::I, 0>;
	using GateIn2 = FPin<GPIO::I, 4>;
	using GateOut1 = FPin<GPIO::F, 11>;
	using GateOut2 = FPin<GPIO::B, 6>;

	template<enum GPIO port>
	using PortRead = mdrivlib::PortRead<port>;

	template<uint32_t pin_num, uint32_t jack_num>
	struct PackedBit {
		static uint32_t extract(uint32_t port_reading)
		{
			auto pin_reading = port_reading & (1 << pin_num);
			if constexpr (pin_num >= jack_num)
				return pin_reading >> (pin_num - jack_num);
			else
				return pin_reading << (jack_num - pin_num);
		}
	};
	enum JackOrder {
		AIn1,
		AIn2,
		AIn3,
		AIn4,
		AIn5,
		AIn6,
		GIn1,
		GIn2,
		AOut1,
		AOut2,
		AOut3,
		AOut4,
		AOut5,
		AOut6,
		AOut7,
		AOut8,
		GOut1,
		GOut2,
		PCV
	};

	uint32_t read_sense_pins()
	{
		uint32_t val = 0;
		auto A = PortRead<GPIO::A>::read();
		val |= PackedBit<AudioIn4::PinNum_v, AIn4>::extract(A);
		val |= PackedBit<AudioIn5::PinNum_v, AIn5>::extract(A);
		val |= PackedBit<AudioOut1::PinNum_v, AOut1>::extract(A);

		auto B = PortRead<GPIO::B>::read();
		val |= PackedBit<AudioOut5::PinNum_v, AOut5>::extract(B);
		val |= PackedBit<AudioOut2::PinNum_v, AOut2>::extract(B);
		val |= PackedBit<AudioOut3::PinNum_v, AOut3>::extract(B);
		val |= PackedBit<AudioOut6::PinNum_v, AOut6>::extract(B);
		val |= PackedBit<GateOut2::PinNum_v, GOut2>::extract(B);

		auto C = PortRead<GPIO::C>::read();
		val |= PackedBit<AudioOut7::PinNum_v, AOut7>::extract(C);

		auto D = PortRead<GPIO::D>::read();
		val |= PackedBit<AudioIn3::PinNum_v, AIn3>::extract(D);
		val |= PackedBit<AudioIn6::PinNum_v, AIn6>::extract(D);
		val |= PackedBit<AudioOut4::PinNum_v, AOut4>::extract(D);
		val |= PackedBit<AudioOut8::PinNum_v, AOut8>::extract(D);

		auto F = PortRead<GPIO::F>::read();
		val |= PackedBit<GateOut1::PinNum_v, GOut1>::extract(F);

		auto G = PortRead<GPIO::G>::read();
		val |= PackedBit<AudioIn2::PinNum_v, AIn2>::extract(G);
		val |= PackedBit<PatchCV::PinNum_v, PCV>::extract(G);

		auto I = PortRead<GPIO::I>::read();
		val |= PackedBit<AudioIn1::PinNum_v, AIn1>::extract(I);
		val |= PackedBit<GateIn1::PinNum_v, GIn1>::extract(I);
		val |= PackedBit<GateIn2::PinNum_v, GIn2>::extract(I);

		return val;
	}

	AudioIn1 init_AudioIn1{PinPull::Up};
	AudioIn2 init_AudioIn2{PinPull::Up};
	AudioIn3 init_AudioIn3{PinPull::Up};
	AudioIn4 init_AudioIn4{PinPull::Up};
	AudioIn5 init_AudioIn5{PinPull::Up};
	AudioIn6 init_AudioIn6{PinPull::Up};
	AudioOut1 init_AudioOut1{PinPull::Up};
	AudioOut2 init_AudioOut2{PinPull::Up};
	AudioOut3 init_AudioOut3{PinPull::Up};
	AudioOut4 init_AudioOut4{PinPull::Up};
	AudioOut5 init_AudioOut5{PinPull::Up};
	AudioOut6 init_AudioOut6{PinPull::Up};
	AudioOut7 init_AudioOut7{PinPull::Up};
	AudioOut8 init_AudioOut8{PinPull::Up};
	PatchCV init_PatchCV{PinPull::Up};
	GateIn1 init_GateIn1{PinPull::Up};
	GateIn2 init_GateIn2{PinPull::Up};
	GateOut1 init_GateOut1{PinPull::Up};
	GateOut2 init_GateOut2{PinPull::Up};
};

} // namespace MetaModule
