#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/module_info_base.hh"

struct AttInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Att"};
    static constexpr std::string_view description{"Attenuator"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Att-artwork.svg"};

    static constexpr int NumKnobs = 2;
    
    enum {
        KnobLevel_1 = 0,
        KnobLevel_2 = 1,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobLevel_1,
            .x_mm = px_to_mm<72>(28.92f),
            .y_mm = px_to_mm<72>(46.99f),
            .short_name = "Level 1",
            .long_name = "Level 1",
            .default_val = 1.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLevel_2,
            .x_mm = px_to_mm<72>(28.92f),
            .y_mm = px_to_mm<72>(94.2f),
            .short_name = "Level 2",
            .long_name = "Level 2",
            .default_val = 1.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 2;
    
    enum {
        InputIn_1 = 0,
        InputIn_2 = 1,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputIn_1,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(168.85f),
            .short_name = "In 1",
            .long_name = "In 1",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_2,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(216.11f),
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
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(263.68f),
            .short_name = "Out 1",
            .long_name = "Out 1",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_2,
            .x_mm = px_to_mm<72>(28.93f),
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
