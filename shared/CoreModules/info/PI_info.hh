#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct PIInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"PI"};
    static constexpr std::string_view description{"Percussion Interface"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/PI-artwork.svg"};

    static constexpr int NumKnobs = 5;
    
    enum {
        KnobSensitivity = 0,
        KnobEnv__Level = 1,
        KnobSustain = 2,
        KnobInv__Level = 3,
        KnobEnv__Decay = 4,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobSensitivity,
            .x_mm = px_to_mm<72>(30.9f),
            .y_mm = px_to_mm<72>(54.04f),
            .short_name = "Sensitivity",
            .long_name = "Sensitivity",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobEnv__Level,
            .x_mm = px_to_mm<72>(86.53f),
            .y_mm = px_to_mm<72>(46.58f),
            .short_name = "Env. Level",
            .long_name = "Env. Level",
            .default_val = 1.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobSustain,
            .x_mm = px_to_mm<72>(30.8f),
            .y_mm = px_to_mm<72>(109.3f),
            .short_name = "Sustain",
            .long_name = "Sustain",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobInv__Level,
            .x_mm = px_to_mm<72>(86.53f),
            .y_mm = px_to_mm<72>(93.62f),
            .short_name = "Inv. Level",
            .long_name = "Inv. Level",
            .default_val = 1.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobEnv__Decay,
            .x_mm = px_to_mm<72>(30.8f),
            .y_mm = px_to_mm<72>(153.17f),
            .short_name = "Env. Decay",
            .long_name = "Env. Decay",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 2;
    
    enum {
        InputIn = 0,
        InputInput = 1,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputIn,
            .x_mm = px_to_mm<72>(19.83f),
            .y_mm = px_to_mm<72>(221.47f),
            .short_name = "IN",
            .long_name = "IN",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputInput,
            .x_mm = px_to_mm<72>(86.55f),
            .y_mm = px_to_mm<72>(310.71f),
            .short_name = "Input",
            .long_name = "Input",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 6;
    
    enum {
        OutputEnv__Out = 0,
        OutputInv__Out = 1,
        OutputGate_Out = 2,
        OutputAudio_Out = 3,
        OutputEnv__Out_P = 4,
        OutputEnv__Out_N = 5,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputEnv__Out,
            .x_mm = px_to_mm<72>(86.52f),
            .y_mm = px_to_mm<72>(176.9f),
            .short_name = "Env. Out",
            .long_name = "Env. Out",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputInv__Out,
            .x_mm = px_to_mm<72>(86.52f),
            .y_mm = px_to_mm<72>(217.28f),
            .short_name = "Inv. Out",
            .long_name = "Inv. Out",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputGate_Out,
            .x_mm = px_to_mm<72>(41.83f),
            .y_mm = px_to_mm<72>(253.56f),
            .short_name = "Gate Out",
            .long_name = "Gate Out",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputAudio_Out,
            .x_mm = px_to_mm<72>(86.52f),
            .y_mm = px_to_mm<72>(257.67f),
            .short_name = "Audio Out",
            .long_name = "Audio Out",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputEnv__Out_P,
            .x_mm = px_to_mm<72>(19.95f),
            .y_mm = px_to_mm<72>(286.08f),
            .short_name = "Env. Out +",
            .long_name = "Env. Out +",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputEnv__Out_N,
            .x_mm = px_to_mm<72>(41.83f),
            .y_mm = px_to_mm<72>(318.61f),
            .short_name = "Env. Out -",
            .long_name = "Env. Out -",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 2;
    
    enum {
        SwitchLow__OR__Med__OR__High = 0,
        SwitchFollow__OR__Gen = 1,
    };

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
        {
            .id = SwitchLow__OR__Med__OR__High,
            .x_mm = px_to_mm<72>(86.53f),
            .y_mm = px_to_mm<72>(138.545f),
            .short_name = "Low | Med | High",
            .long_name = "Low | Med | High",
            .switch_type = SwitchDef::Toggle3pos,
            .orientation = SwitchDef::Horizontal,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchFollow__OR__Gen,
            .x_mm = px_to_mm<72>(30.8f),
            .y_mm = px_to_mm<72>(195.475f),
            .short_name = "Follow | Gen",
            .long_name = "Follow | Gen",
            .switch_type = SwitchDef::Toggle2pos,
            .orientation = SwitchDef::Horizontal,
            .encoder_knob_style = SwitchDef::None,
        },
    }};

    static constexpr int NumDiscreteLeds = 4;
    
    enum {
        LedSens__Led = 0,
        LedGate_Led = 1,
        LedP_Led = 2,
        LedN_Led = 3,
    };

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
        {
            .id = LedSens__Led,
            .x_mm = px_to_mm<72>(11.39f),
            .y_mm = px_to_mm<72>(32.64f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedGate_Led,
            .x_mm = px_to_mm<72>(50.37f),
            .y_mm = px_to_mm<72>(230.46f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedP_Led,
            .x_mm = px_to_mm<72>(10.77f),
            .y_mm = px_to_mm<72>(261.2f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedN_Led,
            .x_mm = px_to_mm<72>(50.37f),
            .y_mm = px_to_mm<72>(292.62f),
            .led_color = LedDef::Red,
        },
    }};

};
