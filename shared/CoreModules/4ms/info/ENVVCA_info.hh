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
		AnalogJackInput4ms{to_mm<72>(35.87), to_mm<72>(322.47), "In", ""},
		AnalogJackOutput4ms{to_mm<72>(92.03), to_mm<72>(227.06), "Env", ""},
		GateJackOutput4ms{to_mm<72>(92.03), to_mm<72>(278.73), "EOR", ""},
		AnalogJackOutput4ms{to_mm<72>(78.57), to_mm<72>(322.5), "Out", ""},
		RedGreenBlueLight{to_mm<72>(45.11), to_mm<72>(174.84), "Rise LED", ""},
		RedGreenBlueLight{to_mm<72>(69.34), to_mm<72>(174.84), "Fall LED", ""},
		RedGreenBlueLight{to_mm<72>(106.41), to_mm<72>(256.6), "EOR LED", ""},
		Toggle3pos{to_mm<72>(23.19), to_mm<72>(43.305), "Slow Med Fast Rise", ""},
		Toggle3pos{to_mm<72>(57.33), to_mm<72>(43.305), "Slow Med Fast Fall", ""},
		LatchingButtonMonoLight{to_mm<72>(92.17), to_mm<72>(41.65), "Cycle", ""},
}};

    enum class Elem {
        RiseSliderSlider,
        FallSliderSlider,
        EnvLevelSliderSlider,
        RiseCvKnob,
        FallCvKnob,
        TimeCvIn,
        TriggerIn,
        CycleIn,
        FollowIn,
        InIn,
        EnvOut,
        EorOut,
        OutOut,
        RiseLedLight,
        FallLedLight,
        EorLedLight,
        SlowMedFastRiseSwitch,
        SlowMedFastFallSwitch,
        CycleButton,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobRise_Slider = 0,
        KnobFall_Slider = 1,
        KnobEnv_Level_Slider = 2,
        KnobRise_Cv = 3,
        KnobFall_Cv = 4,
    };
    
    enum {
        SwitchSlow_Med_Fast_Rise = 0,
        SwitchSlow_Med_Fast_Fall = 1,
        SwitchCycle = 2,
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
        LedRise_Led = 0,
        LedFall_Led = 1,
        LedEor_Led = 2,
    };
};
} // namespace MetaModule
