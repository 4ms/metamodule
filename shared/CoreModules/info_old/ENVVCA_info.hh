#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct ENVVCAInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"ENVVCA"};
	static constexpr std::string_view description{"Envelope VCA"};
	static constexpr uint32_t width_hp = 8;
	static constexpr bool uses_center_coords = true;
	static constexpr std::string_view svg_filename{"res/modules/ENVVCA-artwork.svg"};

	static constexpr std::array<Element, 19> Elements{{
		Slider25mmVertLED{to_mm<72>(23.185f), to_mm<72>(108.81f), "Rise Time", ""},
		Slider25mmVertLED{to_mm<72>(57.325f), to_mm<72>(109.02f), "Fall Time", ""},
		Slider25mmVertLED{to_mm<72>(91.505f), to_mm<72>(108.81f), "Env Level", ""},
		Knob9mm{to_mm<72>(21.69f), to_mm<72>(178.25f), "Rise CV", ""},
		Knob9mm{to_mm<72>(92.85f), to_mm<72>(178.25f), "Fall CV", ""},

		AnalogJackInput4ms{to_mm<72>(57.25f), to_mm<72>(203.53f), "Time CV", ""},
		GateJackInput4ms{to_mm<72>(22.3f), to_mm<72>(227.06f), "Trigger", ""},
		GateJackInput4ms{to_mm<72>(57.25f), to_mm<72>(254.25f), "Cycle", ""},
		AnalogJackInput4ms{to_mm<72>(22.3f), to_mm<72>(278.73f), "Follow", ""},
		AnalogJackInput4ms{to_mm<72>(35.87f), to_mm<72>(322.47f), "In", ""},
		AnalogJackOutput4ms{to_mm<72>(92.03f), to_mm<72>(227.06f), "Env", ""},
		GateJackOutput4ms{to_mm<72>(92.03f), to_mm<72>(278.73f), "EOR", ""},
		AnalogJackOutput4ms{to_mm<72>(78.57f), to_mm<72>(322.5f), "Out", ""},

		Toggle3pos{to_mm<72>(23.19f), to_mm<72>(43.305f), "Rise", ""},
		Toggle3pos{to_mm<72>(57.33f), to_mm<72>(43.305f), "Fall", ""},
		LatchingButtonMonoLight{to_mm<72>(92.17f), to_mm<72>(41.65f), "Cycle", ""},

		RedBlueLight{to_mm<72>(45.11f), to_mm<72>(174.84f), "Rise CV", ""},
		RedBlueLight{to_mm<72>(69.34f), to_mm<72>(174.84f), "Fall CV", ""},
		OrangeLight{to_mm<72>(106.41f), to_mm<72>(256.6f), "EOR", ""},
	}};

	enum class Elem {
		RiseSlider,
		FallSlider,
		LevelSlider,
		RiseCvAtten,
		FallCvAtten,

		TimeCv,
		Trigger,
		CycleJack,
		Follow,
		AudioIn,

		EnvOut,
		Eor,
		AudioOut,

		RiseSwitch,
		FallSwitch,
		CycleButton,

		RiseCvLed,
		FallCvLed,
		EorLed,
	};
};
} // namespace MetaModule
