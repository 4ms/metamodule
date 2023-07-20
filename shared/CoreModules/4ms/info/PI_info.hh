#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct PIInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"PI"};
    static constexpr std::string_view description{"Percussion Interface"};
    static constexpr uint32_t width_hp = 8;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/PI-artwork.svg"};

    static constexpr std::array<Element, 19> Elements{{
		Davies1900hBlackKnob{to_mm<72>(30.9), to_mm<72>(54.04), "Sensitivity", "", 0, 0, 1, 0.875f},
		Knob9mm{to_mm<72>(86.53), to_mm<72>(46.58), "Env. Level", "", 0, 0, 1, 1.0f},
		Knob9mm{to_mm<72>(30.8), to_mm<72>(109.3), "Sustain", "", 0, 0, 1, 0.5f},
		Knob9mm{to_mm<72>(86.53), to_mm<72>(93.62), "Inv. Level", "", 0, 0, 1, 1.0f},
		Knob9mm{to_mm<72>(30.8), to_mm<72>(153.17), "Env. Decay", "", 0, 0, 1, 0.5f},
		AnalogJackInput4ms{to_mm<72>(19.83), to_mm<72>(221.47), "IN", ""},
		AnalogJackInput4ms{to_mm<72>(86.55), to_mm<72>(310.71), "Input", ""},
		AnalogJackOutput4ms{to_mm<72>(86.52), to_mm<72>(176.9), "Env. Out", ""},
		AnalogJackOutput4ms{to_mm<72>(86.52), to_mm<72>(217.28), "Inv. Out", ""},
		GateJackOutput4ms{to_mm<72>(41.83), to_mm<72>(253.56), "Gate Out", ""},
		AnalogJackOutput4ms{to_mm<72>(86.52), to_mm<72>(257.67), "Audio Out", ""},
		AnalogJackOutput4ms{to_mm<72>(19.95), to_mm<72>(286.08), "Env. Out +", ""},
		AnalogJackOutput4ms{to_mm<72>(41.83), to_mm<72>(318.61), "Env. Out -", ""},
		RedGreenBlueLight{to_mm<72>(11.39), to_mm<72>(32.64), "Sens. LED", ""},
		RedGreenBlueLight{to_mm<72>(50.37), to_mm<72>(230.46), "Gate LED", ""},
		RedGreenBlueLight{to_mm<72>(10.77), to_mm<72>(261.2), "+ LED", ""},
		RedGreenBlueLight{to_mm<72>(50.37), to_mm<72>(292.62), "- LED", ""},
		Toggle3posHoriz{to_mm<72>(86.53), to_mm<72>(138.545), "Low | Med | High", ""},
		Toggle2posHoriz{to_mm<72>(30.8), to_mm<72>(195.475), "Follow | Gen", ""},
}};

    enum class Elem {
        SensitivityKnob,
        Env_LevelKnob,
        SustainKnob,
        Inv_LevelKnob,
        Env_DecayKnob,
        In,
        InputIn,
        Env_Out,
        Inv_Out,
        GateOut,
        AudioOut,
        Env_OutPOut,
        Env_OutNOut,
        Sens_LedLight,
        GateLedLight,
        PLedLight,
        NLedLight,
        Low_OR_Med_OR_HighSwitch,
        Follow_OR_GenSwitch,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobSensitivity = 0,
        KnobEnv__Level = 1,
        KnobSustain = 2,
        KnobInv__Level = 3,
        KnobEnv__Decay = 4,
        NumKnobs,
    };
    
    enum {
        SwitchLow__OR__Med__OR__High = 0,
        SwitchFollow__OR__Gen = 1,
        NumSwitches,
    };
    
    enum {
        InputIn = 0,
        InputInput = 1,
        NumInJacks,
    };
    
    enum {
        OutputEnv__Out = 0,
        OutputInv__Out = 1,
        OutputGate_Out = 2,
        OutputAudio_Out = 3,
        OutputEnv__Out_P = 4,
        OutputEnv__Out_N = 5,
        NumOutJacks,
    };
    
    enum {
        LedSens__Led = 0,
        LedGate_Led = 1,
        LedP_Led = 2,
        LedN_Led = 3,
        NumDiscreteLeds,
    };
};
} // namespace MetaModule
