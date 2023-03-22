#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct Switch14Info : ModuleInfoBase {
    static constexpr std::string_view slug{"Switch14"};
    static constexpr std::string_view description{"1 to 4 Switch"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/Switch14-artwork.svg"};

    static constexpr int NumKnobs = 0;
    

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
    }};

    static constexpr int NumInJacks = 4;
    
    enum {
        InputIn = 0,
        InputReset = 1,
        InputClock = 2,
        InputCv = 3,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputIn,
            .x_mm = px_to_mm<72>(31.89f),
            .y_mm = px_to_mm<72>(167.17f),
            .short_name = "In",
            .long_name = "In",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputReset,
            .x_mm = px_to_mm<72>(83.42f),
            .y_mm = px_to_mm<72>(167.17f),
            .short_name = "Reset",
            .long_name = "Reset",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputClock,
            .x_mm = px_to_mm<72>(31.89f),
            .y_mm = px_to_mm<72>(214.56f),
            .short_name = "Clock",
            .long_name = "Clock",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputCv,
            .x_mm = px_to_mm<72>(83.42f),
            .y_mm = px_to_mm<72>(214.56f),
            .short_name = "CV",
            .long_name = "CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 4;
    
    enum {
        OutputOut_1 = 0,
        OutputOut_2 = 1,
        OutputOut_3 = 2,
        OutputOut_4 = 3,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputOut_1,
            .x_mm = px_to_mm<72>(31.89f),
            .y_mm = px_to_mm<72>(263.28f),
            .short_name = "Out 1",
            .long_name = "Out 1",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_2,
            .x_mm = px_to_mm<72>(83.42f),
            .y_mm = px_to_mm<72>(263.28f),
            .short_name = "Out 2",
            .long_name = "Out 2",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_3,
            .x_mm = px_to_mm<72>(31.89f),
            .y_mm = px_to_mm<72>(312.0f),
            .short_name = "Out 3",
            .long_name = "Out 3",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_4,
            .x_mm = px_to_mm<72>(83.42f),
            .y_mm = px_to_mm<72>(312.0f),
            .short_name = "Out 4",
            .long_name = "Out 4",
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
