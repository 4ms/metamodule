#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct SlewInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Slew"};
    static constexpr std::string_view description{"Slew Limiter"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Slew-artwork.svg"};

    static constexpr int NumKnobs = 2;
    
    enum {
        KnobRise = 0,
        KnobFall = 1,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobRise,
            .x_mm = px_to_mm<72>(28.92f),
            .y_mm = px_to_mm<72>(46.76f),
            .short_name = "Rise",
            .long_name = "Rise",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobFall,
            .x_mm = px_to_mm<72>(28.92f),
            .y_mm = px_to_mm<72>(94.44f),
            .short_name = "Fall",
            .long_name = "Fall",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 1;
    
    enum {
        InputIn = 0,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputIn,
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(263.82f),
            .short_name = "In",
            .long_name = "In",
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
            .x_mm = px_to_mm<72>(29.28f),
            .y_mm = px_to_mm<72>(312.04f),
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
