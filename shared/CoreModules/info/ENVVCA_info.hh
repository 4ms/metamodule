#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct ENVVCAInfo : ElementInfoBase {
	static constexpr std::string_view slug{"ENVVCA"};
	static constexpr std::string_view description{"Envelope VCA"};
	static constexpr uint32_t width_hp = 8;
	static constexpr std::string_view svg_filename{"res/modules/ENVVCA-artwork.svg"};

	// Todo: get rid of these enums, set all Elements to idx=0?
	enum {
		KnobRise_Slider = 0,
		KnobFall_Slider = 1,
		KnobEnv_Level_Slider = 2,
		KnobRise_Cv = 3,
		KnobFall_Cv = 4,
		SwitchSlow_Med_Fast_Rise = 5,
		SwitchSlow_Med_Fast_Fall = 6,
		SwitchCycle = 7,
	};
	enum {
		InputTime_Cv = 0,
		InputTrigger = 1,
		InputCycle = 2,
		InputFollow = 3,
		InputIn = 4,
	};
	enum {
		OutputEnv = 0,
		OutputEor = 1,
		OutputOut = 2,
	};

	// FIXME: Led Idx must be manually set, and it's not intuituve; Use named-elements instead?
	enum {
		LedCycle_Led = 0,
		LedRiseBlue_Led = 1,
		LedRiseRed_Led = 2,
		LedFallBlue_Led = 3,
		LedFallRed_Led = 4,
		LedEor_Led = 5,
	};

	static constexpr std::array<Element, 19> Elements{{
		Slider25mmVert{to_mm<72>(23.185f), to_mm<72>(108.81f), "Rise Slider", "", KnobRise_Slider, 0.f, 1.f, 0.25f},
		Slider25mmVert{to_mm<72>(57.325f), to_mm<72>(109.02f), "Fall Slider", "", KnobFall_Slider, 0.f, 1.f, 0.25f},
		Slider25mmVert{to_mm<72>(91.505f), to_mm<72>(108.81f), "Env Level", "", KnobEnv_Level_Slider, 0.f, 1.f, 1.f},
		Knob9mm{to_mm<72>(21.69f), to_mm<72>(178.25f), "Rise CV", "Rise CV", KnobRise_Cv, 0.f, 1.f, 0.f},
		Knob9mm{to_mm<72>(92.85f), to_mm<72>(178.25f), "Fall CV", "Fall CV", KnobFall_Cv, 0.f, 1.f, 0.f},

		AnalogJackInput{to_mm<72>(57.25f), to_mm<72>(203.53f), "Time CV", "Time CV", InputTime_Cv},
		GateJackInput{to_mm<72>(22.3f), to_mm<72>(227.06f), "Trigger", "Trigger", InputTrigger},
		GateJackInput{to_mm<72>(57.25f), to_mm<72>(254.25f), "Cycle", "Cycle", InputCycle},
		AnalogJackInput{to_mm<72>(22.3f), to_mm<72>(278.73f), "Follow", "Follow", InputFollow},
		AnalogJackInput{to_mm<72>(35.87f), to_mm<72>(322.47f), "In", "In", InputIn},
		AnalogJackOutput{to_mm<72>(92.03f), to_mm<72>(227.06f), "Env", "Env", OutputEnv},
		GateJackOutput{to_mm<72>(92.03f), to_mm<72>(278.73f), "EOR", "EOR", OutputEor},
		AnalogJackOutput{to_mm<72>(78.57f), to_mm<72>(322.5f), "Out", "Out", OutputOut},

		Toggle3pos{to_mm<72>(23.19f), to_mm<72>(43.305f), "Rise", "Rise", SwitchSlow_Med_Fast_Rise, 0, 2, 1},
		Toggle3pos{to_mm<72>(57.33f), to_mm<72>(43.305f), "Fall", "Fall", SwitchSlow_Med_Fast_Fall, 0, 2, 1},
		LatchingButtonMonoLight{to_mm<72>(92.17f), to_mm<72>(41.65f), "Cycle", "Cycle", SwitchCycle, 0, 1, 0},

		RedBlueLight{to_mm<72>(45.11f), to_mm<72>(174.84f), "Rise CV", "Rise CV", LedRiseBlue_Led},
		RedBlueLight{to_mm<72>(69.34f), to_mm<72>(174.84f), "Fall CV", "Fall CV", LedFallBlue_Led},
		OrangeLight{to_mm<72>(106.41f), to_mm<72>(256.6f), "EOR", "EOR", LedEor_Led},
	}};

	static constexpr auto Rise_Slider = get<Slider25mmVert>(Elements[0]);
	static constexpr auto Fall_Slider = get<Slider25mmVert>(Elements[1]);
	static constexpr auto Level_Slider = get<Slider25mmVert>(Elements[2]);
	static constexpr auto Rise_Cv = get<Knob9mm>(Elements[3]);
	static constexpr auto Fall_Cv = get<Knob9mm>(Elements[4]);

	static constexpr auto Time_Cv = get<AnalogJackInput>(Elements[5]);
	static constexpr auto Trigger = get<GateJackInput>(Elements[6]);
	static constexpr auto CycleJack = get<GateJackInput>(Elements[7]);
	static constexpr auto Follow = get<AnalogJackInput>(Elements[8]);
	static constexpr auto In = get<AnalogJackInput>(Elements[9]);

	static constexpr auto Env = get<AnalogJackOutput>(Elements[10]);
	static constexpr auto Eor = get<GateJackOutput>(Elements[11]);
	static constexpr auto Out = get<AnalogJackOutput>(Elements[12]);

	static constexpr auto Slow_Med_Fast_Rise = get<Toggle3pos>(Elements[13]);
	static constexpr auto Slow_Med_Fast_Fall = get<Toggle3pos>(Elements[14]);
	static constexpr auto CycleSwitch = get<LatchingButtonMonoLight>(Elements[15]);

	static constexpr auto Rise_Led = get<RedBlueLight>(Elements[16]);
	static constexpr auto Fall_Led = get<RedBlueLight>(Elements[17]);
	static constexpr auto Eor_Led = get<OrangeLight>(Elements[18]);
};
} // namespace MetaModule
