#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct SourceInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Source"};
    static constexpr std::string_view description{"DC Source"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Source-artwork.svg"};

    static constexpr int NumKnobs = 2;
    
    enum {
        Knob_1 = 0,
        Knob_2 = 1,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = Knob_1,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(46.85f),
            .short_name = "1",
            .long_name = "1",
            .default_val = 0.25f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = Knob_2,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(94.68f),
            .short_name = "2",
            .long_name = "2",
            .default_val = 0.25f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 0;
    

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
    }};

    static constexpr int NumOutJacks = 2;
    
    enum {
        Output_1 = 0,
        Output_2 = 1,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = Output_1,
            .x_mm = px_to_mm<72>(29.14f),
            .y_mm = px_to_mm<72>(264.74f),
            .short_name = "1",
            .long_name = "1",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = Output_2,
            .x_mm = px_to_mm<72>(29.14f),
            .y_mm = px_to_mm<72>(312.33f),
            .short_name = "2",
            .long_name = "2",
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
