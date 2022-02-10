#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/module_info_base.hh"

struct LogicInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Logic"};
    static constexpr std::string_view description{"Logic Module"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Logic-artwork.svg"};

    static constexpr int NumKnobs = 0;
    

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
    }};

    static constexpr int NumInJacks = 2;
    
    enum {
        InputIn_1 = 0,
        InputIn_2 = 1,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputIn_1,
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(124.26f),
            .short_name = "In 1",
            .long_name = "In 1",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_2,
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(168.85f),
            .short_name = "In 2",
            .long_name = "In 2",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 3;
    
    enum {
        OutputAnd = 0,
        OutputOr = 1,
        OutputXor = 2,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputAnd,
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(214.97f),
            .short_name = "AND",
            .long_name = "AND",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOr,
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(264.07f),
            .short_name = "OR",
            .long_name = "OR",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputXor,
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(312.29f),
            .short_name = "XOR",
            .long_name = "XOR",
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
