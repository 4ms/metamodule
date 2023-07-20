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
		Slider25mmVertLED{to_mm<72>(23.185), to_mm<72>(108.81), "Rise Slider", "", 0, 0, 1, 0.5f},
		Slider25mmVertLED{to_mm<72>(57.325), to_mm<72>(109.02), "Fall Slider", "", 0, 0, 1, 0.5f},
		Slider25mmVertLED{to_mm<72>(91.505), to_mm<72>(108.81), "Env Level Slider", "", 0, 0, 1, 1.0f},
		Knob9mm{to_mm<72>(21.69), to_mm<72>(178.25), "Rise CV", "", 0, 0, 1, 1.0f},
		Knob9mm{to_mm<72>(92.85), to_mm<72>(178.25), "Fall CV", "", 0, 0, 1, 1.0f},

		AnalogJackInput4ms{to_mm<72>(57.25), to_mm<72>(203.53), "Time CV", ""},
		GateJackInput4ms{to_mm<72>(22.3), to_mm<72>(227.06), "Trigger", ""},
		GateJackInput4ms{to_mm<72>(57.25), to_mm<72>(254.25), "Cycle", ""},
		AnalogJackInput4ms{to_mm<72>(22.3), to_mm<72>(278.73), "Follow", ""},
		AnalogJackInput4ms{to_mm<72>(35.87), to_mm<72>(322.47), "Audio In", ""},

		AnalogJackOutput4ms{to_mm<72>(92.03), to_mm<72>(227.06), "Env", ""},
		GateJackOutput4ms{to_mm<72>(92.03), to_mm<72>(278.73), "EOR", ""},
		AnalogJackOutput4ms{to_mm<72>(78.57), to_mm<72>(322.5), "Audio Out", ""},

		Toggle3pos{to_mm<72>(23.19), to_mm<72>(43.305), "Rise Switch", ""},
		Toggle3pos{to_mm<72>(57.33), to_mm<72>(43.305), "Fall Switch", ""},
		LatchingButtonMonoLight{to_mm<72>(92.17), to_mm<72>(41.65), "Cycle", ""},

		RedBlueLight{to_mm<72>(45.11f), to_mm<72>(174.84f), "Rise CV", "Rise CV", 0},
		RedBlueLight{to_mm<72>(69.34f), to_mm<72>(174.84f), "Fall CV", "Fall CV", 0},
		OrangeLight{to_mm<72>(106.41f), to_mm<72>(256.6f), "EOR", "EOR", 0},
}};

    enum class Elem {
        RiseSlider,
        FallSlider,
        EnvLevelSlider,
        RiseCvKnob,
        FallCvKnob,

        TimeCvIn,
        TriggerIn,
        CycleIn,
        FollowIn,
        AudioIn,

        EnvOut,
        EorOut,
        AudioOut,

        RiseSwitch,
        FallSwitch,
        CycleButton,

        RiseLight,
        FallLight,
        EorLight,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobRise_Slider = 0,
        KnobFall_Slider = 1,
        KnobEnv_Level_Slider = 2,
        KnobRise_Cv = 3,
        KnobFall_Cv = 4,
        NumKnobs,
    };
    
    enum {
        SwitchRise_Switch = 0,
        SwitchFall_Switch = 1,
        SwitchCycle = 2,
        NumSwitches,
    };
    
    enum {
        InputTime_Cv = 0,
        InputTrigger = 1,
        InputCycle = 2,
        InputFollow = 3,
        InputAudio_In = 4,
        NumInJacks,
    };
    
    enum {
        OutputEnv = 0,
        OutputEor = 1,
        OutputAudio_Out = 2,
        NumOutJacks,
    };
    
    enum {
        LedRise_Light = 0,
        LedFall_Light = 1,
        LedEor_Light = 2,
        NumDiscreteLeds,
    };
};
} // namespace MetaModule
