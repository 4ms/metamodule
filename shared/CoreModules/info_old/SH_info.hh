#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct SHInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"SH"};
    static constexpr std::string_view description{"2 Ch. Sample and Hold"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/SH-artwork.svg"};

    static constexpr int NumKnobs = 0;
    

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
    }};

    static constexpr int NumInJacks = 4;
    
    enum {
        InputSamp_1 = 0,
        InputIn_1 = 1,
        InputSamp_2 = 2,
        InputIn_2 = 3,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputSamp_1,
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(78.14f),
            .short_name = "Samp 1",
            .long_name = "Samp 1",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
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
            .id = InputSamp_2,
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(168.85f),
            .short_name = "Samp 2",
            .long_name = "Samp 2",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_2,
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(214.97f),
            .short_name = "In 2",
            .long_name = "In 2",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 2;
    
    enum {
        OutputOut_1 = 0,
        OutputOut_2 = 1,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputOut_1,
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(264.07f),
            .short_name = "Out 1",
            .long_name = "Out 1",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_2,
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(312.29f),
            .short_name = "Out 2",
            .long_name = "Out 2",
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
