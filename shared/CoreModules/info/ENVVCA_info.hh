#pragma once
#include "CoreModules/elements.hh"
#include <array>

//TODO: Try getting rid of id field (need to manually check VCV-converted modules)
//TODO: Try one big Elements array?
// 	- But how to constexpr specify # of Knobs?
//  - Is it efficient to iterate all Elements just to do some operation on knobs?

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

	static constexpr std::array<Element, 5> Knobs{{
		Slider25mmVert{
			px_to_mm<72>(23.185f),
			px_to_mm<72>(108.81f),
			"Rise Slider",
			"Rise Slider",
			KnobRise_Slider,
			0.5f,
		},
		Slider25mmVert{
			px_to_mm<72>(57.325f),
			px_to_mm<72>(109.02f),
			"Fall Slider",
			"Fall Slider",
			KnobFall_Slider,
			0.5f,
		},
		Slider25mmVert{
			px_to_mm<72>(91.505f),
			px_to_mm<72>(108.81f),
			"Env Level Slider",
			"Env Level Slider",
			KnobEnv_Level_Slider,
			1.0f,
		},
		Knob9mm{
			px_to_mm<72>(21.69f),
			px_to_mm<72>(178.25f),
			"Rise CV",
			"Rise CV",
			KnobRise_Cv,
			1.0f,
		},
		Knob9mm{
			px_to_mm<72>(92.85f),
			px_to_mm<72>(178.25f),
			"Fall CV",
			"Fall CV",
			KnobFall_Cv,
			1.0f,
		},
	}};

	static constexpr auto Rise_Slider = get<Slider25mmVert>(Knobs[0]);
	static constexpr auto Fall_Slider = get<Slider25mmVert>(Knobs[1]);
	static constexpr auto Level_Slider = get<Slider25mmVert>(Knobs[2]);
	static constexpr auto Rise_Cv = get<Knob9mm>(Knobs[3]);
	static constexpr auto Fall_Cv = get<Knob9mm>(Knobs[4]);

	enum {
		InputTime_Cv = 0,
		InputTrigger = 1,
		InputCycle = 2,
		InputFollow = 3,
		InputIn = 4,
	};

	static constexpr std::array<InJackElement, 5> InJacks{{
		AnalogJackInput{
			px_to_mm<72>(57.25f),
			px_to_mm<72>(203.53f),
			"Time CV",
			"Time CV",
			InputTime_Cv,
			0.f,
		},
		GateJackInput{
			px_to_mm<72>(22.3f),
			px_to_mm<72>(227.06f),
			"Trigger",
			"Trigger",
			InputTrigger,
			0.f,
		},
		GateJackInput{
			px_to_mm<72>(57.25f),
			px_to_mm<72>(254.25f),
			"Cycle",
			"Cycle",
			InputCycle,
			0.f,
		},
		AnalogJackInput{
			px_to_mm<72>(22.3f),
			px_to_mm<72>(278.73f),
			"Follow",
			"Follow",
			InputFollow,
			0.f,
		},
		AnalogJackInput{
			px_to_mm<72>(35.87f),
			px_to_mm<72>(322.47f),
			"In",
			"In",
			InputIn,
			0.f,
		},
	}};

	static constexpr auto Time_Cv = get<AnalogJackInput>(InJacks[0]);
	static constexpr auto Trigger = get<GateJackInput>(InJacks[1]);
	static constexpr auto CycleJack = get<GateJackInput>(InJacks[2]);
	static constexpr auto Follow = get<AnalogJackInput>(InJacks[3]);
	static constexpr auto In = get<AnalogJackInput>(InJacks[4]);

	enum {
		OutputEnv = 0,
		OutputEor = 1,
		OutputOut = 2,
	};

	static constexpr std::array<OutJackElement, 3> OutJacks{{
		AnalogJackOutput{px_to_mm<72>(92.03f), px_to_mm<72>(227.06f), "Env", "Env", OutputEnv},
		GateJackOutput{px_to_mm<72>(92.03f), px_to_mm<72>(278.73f), "EOR", "EOR", OutputEor},
		AnalogJackOutput{px_to_mm<72>(78.57f), px_to_mm<72>(322.5f), "Out", "Out", OutputOut},
	}};

	static constexpr auto Env = get<AnalogJackOutput>(OutJacks[0]);
	static constexpr auto Eor = get<GateJackOutput>(OutJacks[1]);
	static constexpr auto Out = get<AnalogJackOutput>(OutJacks[2]);

	enum {
		SwitchSlow_Med_Fast_Rise = 0,
		SwitchSlow_Med_Fast_Fall = 1,
		SwitchCycle = 2,
	};

	static constexpr std::array<SwitchElement, 3> Switches{{
		Toggle3pos{
			px_to_mm<72>(23.19f),
			px_to_mm<72>(43.305f),
			"Slow Med Fast Rise",
			"Slow Med Fast Rise",
			SwitchSlow_Med_Fast_Rise,
		},
		Toggle3pos{
			px_to_mm<72>(57.33f),
			px_to_mm<72>(43.305f),
			"Slow Med Fast Fall",
			"Slow Med Fast Fall",
			SwitchSlow_Med_Fast_Fall,
		},
		LatchingButton{
			px_to_mm<72>(92.17f),
			px_to_mm<72>(41.65f),
			"Cycle",
			"Cycle",
			SwitchCycle,
		},
	}};

	static constexpr auto Slow_Med_Fast_Rise = get<Toggle3pos>(Switches[0]);
	static constexpr auto Slow_Med_Fast_Fall = get<Toggle3pos>(Switches[1]);
	static constexpr auto CycleSwitch = get<LatchingButton>(Switches[2]);

	enum {
		LedRise_Led = 0,
		LedFall_Led = 1,
		LedEor_Led = 2,
	};

	static constexpr std::array<LightElement, 3> Leds{{
		RedBlueLight{
			px_to_mm<72>(45.11f),
			px_to_mm<72>(174.84f),
			"Rise CV",
			"Rise CV",
			LedRise_Led,
		},
		RedBlueLight{
			px_to_mm<72>(69.34f),
			px_to_mm<72>(174.84f),
			"Fall CV",
			"Fall CV",
			LedFall_Led,
		},
		OrangeLight{
			px_to_mm<72>(106.41f),
			px_to_mm<72>(256.6f),
			"EOR",
			"EOR",
			LedEor_Led,
		},
	}};

	static constexpr auto Rise_Led = get<RedBlueLight>(Leds[0]);
	static constexpr auto Fall_Led = get<RedBlueLight>(Leds[1]);
	static constexpr auto Eor_Led = get<OrangeLight>(Leds[2]);

	static constexpr std::array<Element, 10> Elements{{
		Rise_Slider, Fall_Slider, Level_Slider, Rise_Cv, Fall_Cv, Time_Cv, Trigger, CycleJack, Follow, In,
		//		   Env,		 Eor,	  Out,	   Slow_Med_Fast_Rise,
		// Slow_Med_Fast_Fall, CycleSwitch, Rise_Led,	   Fall_Led, Eor_Led,
	}};
};
} // namespace MetaModule
