#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct FreeverbInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Freeverb"};
    static constexpr std::string_view description{"Reverb Effect"};
    static constexpr uint32_t width_hp = 10;
    static constexpr std::string_view svg_filename{"res/modules/Freeverb-artwork.svg"};

    static constexpr int NumKnobs = 4;
    
    enum {
        KnobSize = 0,
        KnobTime = 1,
        KnobDamp = 2,
        KnobMix = 3,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobSize,
            .x_mm = px_to_mm<72>(37.85f),
            .y_mm = px_to_mm<72>(46.42f),
            .short_name = "Size",
            .long_name = "Size",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobTime,
            .x_mm = px_to_mm<72>(106.4f),
            .y_mm = px_to_mm<72>(46.42f),
            .short_name = "Time",
            .long_name = "Time",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobDamp,
            .x_mm = px_to_mm<72>(37.85f),
            .y_mm = px_to_mm<72>(104.62f),
            .short_name = "Damp",
            .long_name = "Damp",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobMix,
            .x_mm = px_to_mm<72>(106.4f),
            .y_mm = px_to_mm<72>(104.62f),
            .short_name = "Mix",
            .long_name = "Mix",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 5;
    
    enum {
        InputInput = 0,
        InputSize_Cv = 1,
        InputTime_Cv = 2,
        InputDamp_Cv = 3,
        InputRatio_Cv = 4,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputInput,
            .x_mm = px_to_mm<72>(29.94f),
            .y_mm = px_to_mm<72>(232.1f),
            .short_name = "Input",
            .long_name = "Input",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSize_Cv,
            .x_mm = px_to_mm<72>(72.13f),
            .y_mm = px_to_mm<72>(232.1f),
            .short_name = "Size CV",
            .long_name = "Size CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputTime_Cv,
            .x_mm = px_to_mm<72>(115.17f),
            .y_mm = px_to_mm<72>(232.1f),
            .short_name = "Time CV",
            .long_name = "Time CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputDamp_Cv,
            .x_mm = px_to_mm<72>(29.94f),
            .y_mm = px_to_mm<72>(272.23f),
            .short_name = "Damp CV",
            .long_name = "Damp CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputRatio_Cv,
            .x_mm = px_to_mm<72>(72.13f),
            .y_mm = px_to_mm<72>(272.23f),
            .short_name = "Ratio CV",
            .long_name = "Ratio CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 1;
    
    enum {
        OutputOut = 0,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputOut,
            .x_mm = px_to_mm<72>(115.17f),
            .y_mm = px_to_mm<72>(313.84f),
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
