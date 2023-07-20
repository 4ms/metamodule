#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct MNMXInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"MNMX"};
    static constexpr std::string_view description{"Min Max Logic"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/MNMX-artwork.svg"};

    static constexpr int NumKnobs = 0;
    

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
    }};

    static constexpr int NumInJacks = 2;
    
    enum {
        InputIn_A = 0,
        InputIn_B = 1,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputIn_A,
            .x_mm = px_to_mm<72>(28.92f),
            .y_mm = px_to_mm<72>(168.85f),
            .short_name = "In A",
            .long_name = "In A",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_B,
            .x_mm = px_to_mm<72>(28.92f),
            .y_mm = px_to_mm<72>(214.97f),
            .short_name = "In B",
            .long_name = "In B",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 2;
    
    enum {
        OutputMin = 0,
        OutputMax = 1,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputMin,
            .x_mm = px_to_mm<72>(29.14f),
            .y_mm = px_to_mm<72>(264.61f),
            .short_name = "Min",
            .long_name = "Min",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputMax,
            .x_mm = px_to_mm<72>(28.92f),
            .y_mm = px_to_mm<72>(312.29f),
            .short_name = "Max",
            .long_name = "Max",
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
