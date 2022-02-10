#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/module_info_base.hh"

struct LFOInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"LFO"};
    static constexpr std::string_view description{"Simple LFO"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/LFO-artwork.svg"};

    static constexpr int NumKnobs = 3;
    
    enum {
        KnobSpeed = 0,
        KnobPhase = 1,
        KnobLevel = 2,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobSpeed,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(37.05f),
            .short_name = "Speed",
            .long_name = "Speed",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobPhase,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(82.85f),
            .short_name = "Phase",
            .long_name = "Phase",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLevel,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(128.65f),
            .short_name = "Level",
            .long_name = "Level",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 2;
    
    enum {
        InputFm = 0,
        InputReset = 1,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputFm,
            .x_mm = px_to_mm<72>(28.92f),
            .y_mm = px_to_mm<72>(214.44f),
            .short_name = "FM",
            .long_name = "FM",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputReset,
            .x_mm = px_to_mm<72>(28.92f),
            .y_mm = px_to_mm<72>(263.54f),
            .short_name = "Reset",
            .long_name = "Reset",
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
