#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct Switch41Info : ModuleInfoBase {
    static constexpr std::string_view slug{"Switch41"};
    static constexpr std::string_view description{"4 to 1 Switch"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/Switch41-artwork.svg"};

    static constexpr int NumKnobs = 0;
    

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
    }};

    static constexpr int NumInJacks = 7;
    
    enum {
        InputIn_1 = 0,
        InputIn_2 = 1,
        InputIn_3 = 2,
        InputIn_4 = 3,
        InputClock = 4,
        InputCv = 5,
        InputReset = 6,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputIn_1,
            .x_mm = px_to_mm<72>(31.89f),
            .y_mm = px_to_mm<72>(167.17f),
            .short_name = "In 1",
            .long_name = "In 1",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_2,
            .x_mm = px_to_mm<72>(83.42f),
            .y_mm = px_to_mm<72>(167.17f),
            .short_name = "In 2",
            .long_name = "In 2",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_3,
            .x_mm = px_to_mm<72>(31.89f),
            .y_mm = px_to_mm<72>(214.56f),
            .short_name = "In 3",
            .long_name = "In 3",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_4,
            .x_mm = px_to_mm<72>(83.42f),
            .y_mm = px_to_mm<72>(214.56f),
            .short_name = "In 4",
            .long_name = "In 4",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputClock,
            .x_mm = px_to_mm<72>(31.89f),
            .y_mm = px_to_mm<72>(263.28f),
            .short_name = "Clock",
            .long_name = "Clock",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputCv,
            .x_mm = px_to_mm<72>(83.42f),
            .y_mm = px_to_mm<72>(263.28f),
            .short_name = "CV",
            .long_name = "CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputReset,
            .x_mm = px_to_mm<72>(31.89f),
            .y_mm = px_to_mm<72>(312.0f),
            .short_name = "Reset",
            .long_name = "Reset",
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
            .x_mm = px_to_mm<72>(83.42f),
            .y_mm = px_to_mm<72>(312.0f),
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
