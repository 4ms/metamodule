#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct BuffMultInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"BuffMult"};
    static constexpr std::string_view description{"Buffered Multiple"};
    static constexpr uint32_t width_hp = 3;
    static constexpr std::string_view svg_filename{"res/modules/BuffMult-artwork.svg"};

    static constexpr int NumKnobs = 0;
    

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
    }};

    static constexpr int NumInJacks = 2;
    
    enum {
        InputInput_1 = 0,
        InputInput_2 = 1,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputInput_1,
            .x_mm = px_to_mm<72>(21.71f),
            .y_mm = px_to_mm<72>(44.75f),
            .short_name = "Input 1",
            .long_name = "Input 1",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputInput_2,
            .x_mm = px_to_mm<72>(21.71f),
            .y_mm = px_to_mm<72>(182.98f),
            .short_name = "Input 2",
            .long_name = "Input 2",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 6;
    
    enum {
        OutputOutput_A = 0,
        OutputOutput_B = 1,
        OutputOutput_C = 2,
        OutputOutput_F = 3,
        OutputOutput_E = 4,
        OutputOutput_D = 5,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputOutput_A,
            .x_mm = px_to_mm<72>(21.71f),
            .y_mm = px_to_mm<72>(79.31f),
            .short_name = "Output A",
            .long_name = "Output A",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOutput_B,
            .x_mm = px_to_mm<72>(21.71f),
            .y_mm = px_to_mm<72>(113.89f),
            .short_name = "Output B",
            .long_name = "Output B",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOutput_C,
            .x_mm = px_to_mm<72>(21.71f),
            .y_mm = px_to_mm<72>(148.42f),
            .short_name = "Output C",
            .long_name = "Output C",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOutput_F,
            .x_mm = px_to_mm<72>(21.71f),
            .y_mm = px_to_mm<72>(217.54f),
            .short_name = "Output F",
            .long_name = "Output F",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOutput_E,
            .x_mm = px_to_mm<72>(21.71f),
            .y_mm = px_to_mm<72>(252.1f),
            .short_name = "Output E",
            .long_name = "Output E",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOutput_D,
            .x_mm = px_to_mm<72>(21.71f),
            .y_mm = px_to_mm<72>(286.66f),
            .short_name = "Output D",
            .long_name = "Output D",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 0;
    

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
    }};

    static constexpr int NumDiscreteLeds = 2;
    
    enum {
        LedInput_1_Led = 0,
        LedInput_2_Led = 1,
    };

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
        {
            .id = LedInput_1_Led,
            .x_mm = px_to_mm<72>(36.49f),
            .y_mm = px_to_mm<72>(62.81f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedInput_2_Led,
            .x_mm = px_to_mm<72>(36.49f),
            .y_mm = px_to_mm<72>(201.01f),
            .led_color = LedDef::Red,
        },
    }};

};
