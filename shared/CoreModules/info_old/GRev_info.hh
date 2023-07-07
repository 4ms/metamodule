#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct GRevInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"GRev"};
    static constexpr std::string_view description{"Gated Reverse"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/GRev-artwork.svg"};

    static constexpr int NumKnobs = 1;
    
    enum {
        KnobBuffer = 0,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobBuffer,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(46.53f),
            .short_name = "Buffer",
            .long_name = "Buffer",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 2;
    
    enum {
        InputRev = 0,
        InputInput = 1,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputRev,
            .x_mm = px_to_mm<72>(28.63f),
            .y_mm = px_to_mm<72>(214.97f),
            .short_name = "Rev",
            .long_name = "Rev",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputInput,
            .x_mm = px_to_mm<72>(28.63f),
            .y_mm = px_to_mm<72>(264.07f),
            .short_name = "Input",
            .long_name = "Input",
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
            .x_mm = px_to_mm<72>(28.63f),
            .y_mm = px_to_mm<72>(312.29f),
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
