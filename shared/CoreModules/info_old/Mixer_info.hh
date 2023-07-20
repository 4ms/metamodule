#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct MixerInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Mixer"};
    static constexpr std::string_view description{"4 Ch. Mixer"};
    static constexpr uint32_t width_hp = 10;
    static constexpr std::string_view svg_filename{"res/modules/Mixer-artwork.svg"};

    static constexpr int NumKnobs = 4;
    
    enum {
        KnobLevel_1 = 0,
        KnobLevel_2 = 1,
        KnobLevel_3 = 2,
        KnobLevel_4 = 3,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobLevel_1,
            .x_mm = px_to_mm<72>(37.85f),
            .y_mm = px_to_mm<72>(46.42f),
            .short_name = "Level 1",
            .long_name = "Level 1",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLevel_2,
            .x_mm = px_to_mm<72>(106.4f),
            .y_mm = px_to_mm<72>(46.42f),
            .short_name = "Level 2",
            .long_name = "Level 2",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLevel_3,
            .x_mm = px_to_mm<72>(37.85f),
            .y_mm = px_to_mm<72>(104.62f),
            .short_name = "Level 3",
            .long_name = "Level 3",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLevel_4,
            .x_mm = px_to_mm<72>(106.4f),
            .y_mm = px_to_mm<72>(104.62f),
            .short_name = "Level 4",
            .long_name = "Level 4",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 4;
    
    enum {
        InputIn_1 = 0,
        InputIn_2 = 1,
        InputIn_3 = 2,
        InputIn_4 = 3,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputIn_1,
            .x_mm = px_to_mm<72>(29.94f),
            .y_mm = px_to_mm<72>(272.23f),
            .short_name = "In 1",
            .long_name = "In 1",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_2,
            .x_mm = px_to_mm<72>(72.13f),
            .y_mm = px_to_mm<72>(272.23f),
            .short_name = "In 2",
            .long_name = "In 2",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_3,
            .x_mm = px_to_mm<72>(115.17f),
            .y_mm = px_to_mm<72>(272.23f),
            .short_name = "In 3",
            .long_name = "In 3",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_4,
            .x_mm = px_to_mm<72>(72.13f),
            .y_mm = px_to_mm<72>(313.84f),
            .short_name = "In 4",
            .long_name = "In 4",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 2;
    
    enum {
        OutputInv = 0,
        OutputOut = 1,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputInv,
            .x_mm = px_to_mm<72>(29.94f),
            .y_mm = px_to_mm<72>(313.84f),
            .short_name = "Inv",
            .long_name = "Inv",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut,
            .x_mm = px_to_mm<72>(115.17f),
            .y_mm = px_to_mm<72>(313.84f),
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
