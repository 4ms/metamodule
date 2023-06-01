#pragma once
#include "CoreModules/elements.hh"
#include <array>

//TODO: Try getting rid of id field (need to manually check VCV-converted modules)
// TODO: Add spans for types that firmware wants to access quickly (Knobs, switches, jacks)

namespace MetaModule
{
struct ENVVCAInfo : ElementInfoBase {
	static constexpr std::string_view slug{"ENVVCA"};
	static constexpr std::string_view description{"Envelope VCA"};
	static constexpr uint32_t width_hp = 8;
	static constexpr std::string_view svg_filename{"res/modules/ENVVCA-artwork.svg"};

	enum {
		KnobRise_Slider = 0,
		KnobFall_Slider = 1,
		KnobEnv_Level_Slider = 2,
		KnobRise_Cv = 3,
		KnobFall_Cv = 4,
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
	enum {
		SwitchSlow_Med_Fast_Rise = 0,
		SwitchSlow_Med_Fast_Fall = 1,
		SwitchCycle = 2,
	};
	enum {
		LedRise_Led = 0,
		LedFall_Led = 1,
		LedEor_Led = 2,
	};

	static constexpr std::array<Element, 19> Elements{{
		Slider25mmVert{(23.185f), (108.81f), "Rise Slider", "Rise Slider", KnobRise_Slider, 0.5f},
		Slider25mmVert{(57.325f), (109.02f), "Fall Slider", "Fall Slider", KnobFall_Slider, 0.5f},
		Slider25mmVert{(91.505f), (108.81f), "Env Level Slider", "Env Level Slider", KnobEnv_Level_Slider, 1.0f},
		Knob9mm{(21.69f), (178.25f), "Rise CV", "Rise CV", KnobRise_Cv, 1.0f},
		Knob9mm{(92.85f), (178.25f), "Fall CV", "Fall CV", KnobFall_Cv, 1.0f},

		AnalogJackInput{px_to_mm<72>(57.25f), px_to_mm<72>(203.53f), "Time CV", "Time CV", InputTime_Cv, 0.f},
		GateJackInput{px_to_mm<72>(22.3f), px_to_mm<72>(227.06f), "Trigger", "Trigger", InputTrigger, 0.f},
		GateJackInput{px_to_mm<72>(57.25f), px_to_mm<72>(254.25f), "Cycle", "Cycle", InputCycle, 0.f},
		AnalogJackInput{px_to_mm<72>(22.3f), px_to_mm<72>(278.73f), "Follow", "Follow", InputFollow, 0.f},
		AnalogJackInput{px_to_mm<72>(35.87f), px_to_mm<72>(322.47f), "In", "In", InputIn, 0.f},
		AnalogJackOutput{px_to_mm<72>(92.03f), px_to_mm<72>(227.06f), "Env", "Env", OutputEnv},
		GateJackOutput{px_to_mm<72>(92.03f), px_to_mm<72>(278.73f), "EOR", "EOR", OutputEor},
		AnalogJackOutput{px_to_mm<72>(78.57f), px_to_mm<72>(322.5f), "Out", "Out", OutputOut},

		Toggle3pos{px_to_mm<72>(23.19f), px_to_mm<72>(43.305f), "Rise", "Rise", SwitchSlow_Med_Fast_Rise},
		Toggle3pos{px_to_mm<72>(57.33f), px_to_mm<72>(43.305f), "Fall", "Fall", SwitchSlow_Med_Fast_Fall},
		LatchingButtonMonoLight{px_to_mm<72>(92.17f), px_to_mm<72>(41.65f), "Cycle", "Cycle", SwitchCycle},

		RedBlueLight{px_to_mm<72>(45.11f), px_to_mm<72>(174.84f), "Rise CV", "Rise CV", LedRise_Led},
		RedBlueLight{px_to_mm<72>(69.34f), px_to_mm<72>(174.84f), "Fall CV", "Fall CV", LedFall_Led},
		OrangeLight{px_to_mm<72>(106.41f), px_to_mm<72>(256.6f), "EOR", "EOR", LedEor_Led},
	}};

	// static constexpr auto Rise_Slider = get<Slider25mmVert>(Knobs[0]);
	// static constexpr auto Fall_Slider = get<Slider25mmVert>(Knobs[1]);
	// static constexpr auto Level_Slider = get<Slider25mmVert>(Knobs[2]);
	// static constexpr auto Rise_Cv = get<Knob9mm>(Knobs[3]);
	// static constexpr auto Fall_Cv = get<Knob9mm>(Knobs[4]);

	// static constexpr auto Time_Cv = get<AnalogJackInput>(InJacks[0]);
	// static constexpr auto Trigger = get<GateJackInput>(InJacks[1]);
	// static constexpr auto CycleJack = get<GateJackInput>(InJacks[2]);
	// static constexpr auto Follow = get<AnalogJackInput>(InJacks[3]);
	// static constexpr auto In = get<AnalogJackInput>(InJacks[4]);

	// static constexpr auto Env = get<AnalogJackOutput>(OutJacks[0]);
	// static constexpr auto Eor = get<GateJackOutput>(OutJacks[1]);
	// static constexpr auto Out = get<AnalogJackOutput>(OutJacks[2]);

	// static constexpr auto Slow_Med_Fast_Rise = get<Toggle3pos>(Switches[0]);
	// static constexpr auto Slow_Med_Fast_Fall = get<Toggle3pos>(Switches[1]);
	// static constexpr auto CycleSwitch = get<LatchingButton>(Switches[2]);

	// static constexpr auto Rise_Led = get<RedBlueLight>(Leds[0]);
	// static constexpr auto Fall_Led = get<RedBlueLight>(Leds[1]);
	// static constexpr auto Eor_Led = get<OrangeLight>(Leds[2]);
};
} // namespace MetaModule
