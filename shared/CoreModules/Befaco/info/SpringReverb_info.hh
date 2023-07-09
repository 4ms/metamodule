#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>
#include <string_view>

namespace MetaModule
{

struct SpringReverbInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"SpringReverb"};
	static constexpr std::string_view description{"Befaco Spring Reverb"};
	static constexpr uint32_t width_hp = 4;
	static constexpr bool uses_center_coords = false;

	static constexpr std::array<Element, 19> Elements{
		BefacoBigKnob{to_mm(22), to_mm(29), "WET", ""},

		BefacoSlidePot{to_mm(12), to_mm(116), "LEVEL1", ""},
		BefacoSlidePot{to_mm(93), to_mm(116), "LEVEL2", ""},

		Davies1900hWhiteKnob{to_mm(42), to_mm(210), "HPF", ""},

		BefacoInputPort{to_mm(7), to_mm(243), "CV1", ""},
		BefacoInputPort{to_mm(88), to_mm(243), "CV2", ""},
		BefacoInputPort{to_mm(27), to_mm(281), "IN1", ""},
		BefacoInputPort{to_mm(67), to_mm(281), "IN2", ""},

		BefacoOutputPort{to_mm(7), to_mm(317), "MIX", ""},
		BefacoInputPort{to_mm(47), to_mm(324), "MIX_CV", ""},
		BefacoOutputPort{to_mm(88), to_mm(317), "WET", ""},

		MediumLight<GreenRedLight>{to_mm(55), to_mm(269), "PEAK", ""},
		MediumLight<RedLight>{to_mm(55), to_mm(113), "VU1", ""},
		MediumLight<YellowLight>{to_mm(55), to_mm(126), "VU2", ""},
		MediumLight<YellowLight>{to_mm(55), to_mm(138), "VU3", ""},
		MediumLight<GreenLight>{to_mm(55), to_mm(150), "VU4", ""},
		MediumLight<GreenLight>{to_mm(55), to_mm(163), "VU5", ""},
		MediumLight<GreenLight>{to_mm(55), to_mm(175), "VU6", ""},
		MediumLight<GreenLight>{to_mm(55), to_mm(188), "VU7", ""},
	};
};

} // namespace MetaModule
