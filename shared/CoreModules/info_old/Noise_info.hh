#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct NoiseInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Noise"};
    static constexpr std::string_view description{"Noise Source"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Noise-artwork.svg"};

    static constexpr int NumKnobs = 0;
    

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
    }};

    static constexpr int NumInJacks = 0;
    

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
    }};

    static constexpr int NumOutJacks = 2;
    
    enum {
        OutputWhite = 0,
        OutputPink = 1,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputWhite,
            .x_mm = px_to_mm<72>(29.14f),
            .y_mm = px_to_mm<72>(264.61f),
            .short_name = "White",
            .long_name = "White",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputPink,
            .x_mm = px_to_mm<72>(29.14f),
            .y_mm = px_to_mm<72>(312.2f),
            .short_name = "Pink",
            .long_name = "Pink",
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
