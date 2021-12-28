#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/module_info_base.hh"

struct DetuneInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Detune"};
    static constexpr std::string_view description{"Detuner"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Detune-artwork.svg"};

    static constexpr int NumKnobs = 4;
    
    enum {
        KnobW_Speed = 0,
        KnobW_Depth = 1,
        KnobF_Speed = 2,
        KnobF_Depth = 3,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobW_Speed,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(37.05f),
            .short_name = "W Speed",
            .long_name = "W Speed",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobW_Depth,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(82.85f),
            .short_name = "W Depth",
            .long_name = "W Depth",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobF_Speed,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(128.65f),
            .short_name = "F Speed",
            .long_name = "F Speed",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobF_Depth,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(174.45f),
            .short_name = "F Depth",
            .long_name = "F Depth",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 2;
    
    enum {
        InputInput = 0,
        InputDetune = 1,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputInput,
            .x_mm = px_to_mm<72>(28.92f),
            .y_mm = px_to_mm<72>(214.44f),
            .short_name = "Input",
            .long_name = "Input",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputDetune,
            .x_mm = px_to_mm<72>(28.92f),
            .y_mm = px_to_mm<72>(263.54f),
            .short_name = "Detune",
            .long_name = "Detune",
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
            .x_mm = px_to_mm<72>(28.92f),
            .y_mm = px_to_mm<72>(311.76f),
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
