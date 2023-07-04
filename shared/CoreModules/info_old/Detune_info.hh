#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct DetuneInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Detune"};
    static constexpr std::string_view description{"Detuner"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/Detune-artwork.svg"};

    static constexpr int NumKnobs = 4;
    
    enum {
        KnobW_Speed = 0,
        KnobF_Speed = 1,
        KnobW_Depth = 2,
        KnobF_Depth = 3,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobW_Speed,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(57.97f),
            .short_name = "W Speed",
            .long_name = "W Speed",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobF_Speed,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(57.97f),
            .short_name = "F Speed",
            .long_name = "F Speed",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobW_Depth,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(119.21f),
            .short_name = "W Depth",
            .long_name = "W Depth",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobF_Depth,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(119.21f),
            .short_name = "F Depth",
            .long_name = "F Depth",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 3;
    
    enum {
        InputInput = 0,
        InputDetune = 1,
        InputDepth = 2,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputInput,
            .x_mm = px_to_mm<72>(32.13f),
            .y_mm = px_to_mm<72>(272.09f),
            .short_name = "Input",
            .long_name = "Input",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputDetune,
            .x_mm = px_to_mm<72>(83.32f),
            .y_mm = px_to_mm<72>(272.09f),
            .short_name = "Detune",
            .long_name = "Detune",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputDepth,
            .x_mm = px_to_mm<72>(32.13f),
            .y_mm = px_to_mm<72>(313.7f),
            .short_name = "Depth",
            .long_name = "Depth",
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
            .x_mm = px_to_mm<72>(83.32f),
            .y_mm = px_to_mm<72>(313.7f),
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
