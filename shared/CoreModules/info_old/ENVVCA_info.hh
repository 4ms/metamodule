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
		Slider25mmVertLED{{{{{to_mm<72>(23.185f), to_mm<72>(108.81f), "Rise Time", "", 0}, 0.f, 1.f, 0.25f}}}},
		Slider25mmVertLED{{{{{to_mm<72>(57.325f), to_mm<72>(109.02f), "Fall Time", "", 0}, 0.f, 1.f}}}},
		Slider25mmVertLED{{{{{to_mm<72>(91.505f), to_mm<72>(108.81f), "Env Level", "", 0}, 0.f, 1.f, 1.f}}}},
		Knob9mm{{{{to_mm<72>(21.69f), to_mm<72>(178.25f), "Rise CV", "Rise CV", 0}, 0.f, 1.f, 0.f}}},
		Knob9mm{{{{to_mm<72>(92.85f), to_mm<72>(178.25f), "Fall CV", "Fall CV", 0}, 0.f, 1.f, 0.f}}},

		AnalogJackInput4ms{to_mm<72>(57.25f), to_mm<72>(203.53f), "Time CV", "Time CV", 0},
		GateJackInput4ms{to_mm<72>(22.3f), to_mm<72>(227.06f), "Trigger", "Trigger", 0},
		GateJackInput4ms{to_mm<72>(57.25f), to_mm<72>(254.25f), "Cycle", "Cycle", 0},
		AnalogJackInput4ms{to_mm<72>(22.3f), to_mm<72>(278.73f), "Follow", "Follow", 0},
		AnalogJackInput4ms{to_mm<72>(35.87f), to_mm<72>(322.47f), "In", "In", 0},
		AnalogJackOutput4ms{to_mm<72>(92.03f), to_mm<72>(227.06f), "Env", "Env", 0},
		GateJackOutput4ms{to_mm<72>(92.03f), to_mm<72>(278.73f), "EOR", "EOR", 0},
		AnalogJackOutput4ms{to_mm<72>(78.57f), to_mm<72>(322.5f), "Out", "Out", 0},

		Toggle3pos{to_mm<72>(23.19f), to_mm<72>(43.305f), "Rise", "Rise", 0},
		Toggle3pos{to_mm<72>(57.33f), to_mm<72>(43.305f), "Fall", "Fall", 0},
		LatchingButtonMonoLight{to_mm<72>(92.17f), to_mm<72>(41.65f), "Cycle", "Cycle", 0},

		RedBlueLight{to_mm<72>(45.11f), to_mm<72>(174.84f), "Rise CV", "Rise CV", 0},
		RedBlueLight{to_mm<72>(69.34f), to_mm<72>(174.84f), "Fall CV", "Fall CV", 0},
		OrangeLight{to_mm<72>(106.41f), to_mm<72>(256.6f), "EOR", "EOR", 0},
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
