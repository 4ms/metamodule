#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct ENVVCAInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"ENVVCA"};
    static constexpr std::string_view description{"EnvelopeVCA"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/ENVVCA_artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 19> Elements{{
		Slider25mmVertLED{{to_mm<72>(23.185), to_mm<72>(108.81), Center, "Rise Slider", ""}},
		Slider25mmVertLED{{to_mm<72>(57.325), to_mm<72>(109.02), Center, "Fall Slider", ""}},
		Slider25mmVertLED{{to_mm<72>(91.505), to_mm<72>(108.81), Center, "Env Level Slider", ""}},
		Knob9mm{{to_mm<72>(21.69), to_mm<72>(178.25), Center, "Rise CV", ""}},
		Knob9mm{{to_mm<72>(92.85), to_mm<72>(178.25), Center, "Fall CV", ""}},
		Toggle3pos{{to_mm<72>(23.19), to_mm<72>(43.305), Center, "Rise Switch", ""}, {"Fast", "Med", "Slow"}},
		Toggle3pos{{to_mm<72>(57.33), to_mm<72>(43.305), Center, "Fall Switch", ""}, {"Fast", "Med", "Slow"}},
		OrangeButton{{to_mm<72>(92.17), to_mm<72>(41.65), Center, "Cycle", ""}},
		AnalogJackInput4ms{{to_mm<72>(57.25), to_mm<72>(203.53), Center, "Time CV", ""}},
		GateJackInput4ms{{to_mm<72>(22.3), to_mm<72>(227.06), Center, "Trigger", ""}},
		GateJackInput4ms{{to_mm<72>(57.25), to_mm<72>(254.25), Center, "Cycle", ""}},
		AnalogJackInput4ms{{to_mm<72>(22.3), to_mm<72>(278.73), Center, "Follow", ""}},
		AnalogJackInput4ms{{to_mm<72>(35.87), to_mm<72>(322.47), Center, "Audio In", ""}},
		AnalogJackOutput4ms{{to_mm<72>(92.03), to_mm<72>(227.06), Center, "Env", ""}},
		GateJackOutput4ms{{to_mm<72>(92.03), to_mm<72>(278.73), Center, "EOR", ""}},
		AnalogJackOutput4ms{{to_mm<72>(78.57), to_mm<72>(322.5), Center, "Audio Out", ""}},
		RedBlueLight{{to_mm<72>(45.11), to_mm<72>(174.84), Center, "Rise Light", ""}},
		RedBlueLight{{to_mm<72>(69.34), to_mm<72>(174.84), Center, "Fall Light", ""}},
		OrangeLight{{to_mm<72>(106.41), to_mm<72>(256.6), Center, "EOR Light", ""}},
}};

    enum class Elem {
        RiseSlider,
        FallSlider,
        EnvLevelSlider,
        RiseCvKnob,
        FallCvKnob,
        RiseSwitch,
        FallSwitch,
        CycleButton,
        TimeCvIn,
        TriggerIn,
        CycleIn,
        FollowIn,
        AudioIn,
        EnvOut,
        EorOut,
        AudioOut,
        RiseLight,
        FallLight,
        EorLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
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
