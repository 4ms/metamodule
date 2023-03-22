#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct DrumInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Drum"};
    static constexpr std::string_view description{"Drum Voice"};
    static constexpr uint32_t width_hp = 15;
    static constexpr std::string_view svg_filename{"res/modules/Drum-artwork.svg"};

    static constexpr int NumKnobs = 9;
    
    enum {
        KnobPitch = 0,
        KnobPitch_Env = 1,
        KnobPitch_Amt = 2,
        KnobRatio = 3,
        KnobFm_Env = 4,
        KnobFm_Amt = 5,
        KnobTone_Env = 6,
        KnobNoise_Env = 7,
        KnobNoise_Blend = 8,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobPitch,
            .x_mm = px_to_mm<72>(43.62f),
            .y_mm = px_to_mm<72>(45.96f),
            .short_name = "Pitch",
            .long_name = "Pitch",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobPitch_Env,
            .x_mm = px_to_mm<72>(108.12f),
            .y_mm = px_to_mm<72>(45.96f),
            .short_name = "Pitch Env",
            .long_name = "Pitch Env",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobPitch_Amt,
            .x_mm = px_to_mm<72>(172.59f),
            .y_mm = px_to_mm<72>(45.96f),
            .short_name = "Pitch Amt",
            .long_name = "Pitch Amt",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobRatio,
            .x_mm = px_to_mm<72>(43.62f),
            .y_mm = px_to_mm<72>(104.51f),
            .short_name = "Ratio",
            .long_name = "Ratio",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobFm_Env,
            .x_mm = px_to_mm<72>(108.12f),
            .y_mm = px_to_mm<72>(104.51f),
            .short_name = "FM Env",
            .long_name = "FM Env",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobFm_Amt,
            .x_mm = px_to_mm<72>(172.59f),
            .y_mm = px_to_mm<72>(104.51f),
            .short_name = "FM Amt",
            .long_name = "FM Amt",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobTone_Env,
            .x_mm = px_to_mm<72>(43.62f),
            .y_mm = px_to_mm<72>(163.19f),
            .short_name = "Tone Env",
            .long_name = "Tone Env",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobNoise_Env,
            .x_mm = px_to_mm<72>(108.12f),
            .y_mm = px_to_mm<72>(163.19f),
            .short_name = "Noise Env",
            .long_name = "Noise Env",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobNoise_Blend,
            .x_mm = px_to_mm<72>(172.59f),
            .y_mm = px_to_mm<72>(163.19f),
            .short_name = "Noise Blend",
            .long_name = "Noise Blend",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 10;
    
    enum {
        InputTrigger = 0,
        InputV_Oct = 1,
        InputP_Env_Cv = 2,
        InputP_Amt_Cv = 3,
        InputRatio_Cv = 4,
        InputFm_Env_Cv = 5,
        InputFm_Amt_Cv = 6,
        InputT_Env_Cv = 7,
        InputN_Env_Cv = 8,
        InputN_Blend_Cv = 9,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputTrigger,
            .x_mm = px_to_mm<72>(36.54f),
            .y_mm = px_to_mm<72>(214.33f),
            .short_name = "Trigger",
            .long_name = "Trigger",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputV_Oct,
            .x_mm = px_to_mm<72>(84.82f),
            .y_mm = px_to_mm<72>(214.33f),
            .short_name = "V/Oct",
            .long_name = "V/Oct",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputP_Env_Cv,
            .x_mm = px_to_mm<72>(133.11f),
            .y_mm = px_to_mm<72>(214.33f),
            .short_name = "P Env CV",
            .long_name = "P Env CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputP_Amt_Cv,
            .x_mm = px_to_mm<72>(181.39f),
            .y_mm = px_to_mm<72>(214.33f),
            .short_name = "P Amt CV",
            .long_name = "P Amt CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputRatio_Cv,
            .x_mm = px_to_mm<72>(36.54f),
            .y_mm = px_to_mm<72>(263.05f),
            .short_name = "Ratio CV",
            .long_name = "Ratio CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputFm_Env_Cv,
            .x_mm = px_to_mm<72>(84.82f),
            .y_mm = px_to_mm<72>(263.05f),
            .short_name = "FM Env CV",
            .long_name = "FM Env CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputFm_Amt_Cv,
            .x_mm = px_to_mm<72>(133.11f),
            .y_mm = px_to_mm<72>(263.05f),
            .short_name = "FM Amt CV",
            .long_name = "FM Amt CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputT_Env_Cv,
            .x_mm = px_to_mm<72>(181.39f),
            .y_mm = px_to_mm<72>(263.05f),
            .short_name = "T Env CV",
            .long_name = "T Env CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputN_Env_Cv,
            .x_mm = px_to_mm<72>(84.82f),
            .y_mm = px_to_mm<72>(311.77f),
            .short_name = "N Env CV",
            .long_name = "N Env CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputN_Blend_Cv,
            .x_mm = px_to_mm<72>(133.11f),
            .y_mm = px_to_mm<72>(311.77f),
            .short_name = "N Blend CV",
            .long_name = "N Blend CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 2;
    
    enum {
        OutputInv_Out = 0,
        OutputOut = 1,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputInv_Out,
            .x_mm = px_to_mm<72>(36.54f),
            .y_mm = px_to_mm<72>(311.77f),
            .short_name = "Inv Out",
            .long_name = "Inv Out",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut,
            .x_mm = px_to_mm<72>(181.39f),
            .y_mm = px_to_mm<72>(311.77f),
            .short_name = "Out",
            .long_name = "Out",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 0;
    

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
    }};

    static constexpr int NumDiscreteLeds = 0;
    

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
    }};

};
