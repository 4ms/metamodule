#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct FadeInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Fade"};
    static constexpr std::string_view description{"Crossfader"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Fade-artwork.svg"};

    static constexpr int NumKnobs = 1;
    
    enum {
        KnobFade = 0,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobFade,
            .x_mm = px_to_mm<72>(28.92f),
            .y_mm = px_to_mm<72>(46.99f),
            .short_name = "Fade",
            .long_name = "Fade",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 3;
    
    enum {
        InputCv = 0,
        InputIn_1 = 1,
        InputIn_2 = 2,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputCv,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(168.85f),
            .short_name = "CV",
            .long_name = "CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_1,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(216.11f),
            .short_name = "In 1",
            .long_name = "In 1",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_2,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(263.68f),
            .short_name = "In 2",
            .long_name = "In 2",
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
            .x_mm = px_to_mm<72>(28.93f),
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
