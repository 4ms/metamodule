#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct Prob8Info : ModuleInfoBase {
    static constexpr std::string_view slug{"Prob8"};
    static constexpr std::string_view description{"Probability Module"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/Prob8-artwork.svg"};

    static constexpr int NumKnobs = 8;
    
    enum {
        Knob_1 = 0,
        Knob_2 = 1,
        Knob_3 = 2,
        Knob_4 = 3,
        Knob_5 = 4,
        Knob_6 = 5,
        Knob_7 = 6,
        Knob_8 = 7,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = Knob_1,
            .x_mm = px_to_mm<72>(32.88f),
            .y_mm = px_to_mm<72>(47.23f),
            .short_name = "1",
            .long_name = "1",
            .default_val = 1.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = Knob_2,
            .x_mm = px_to_mm<72>(84.41f),
            .y_mm = px_to_mm<72>(47.23f),
            .short_name = "2",
            .long_name = "2",
            .default_val = 1.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = Knob_3,
            .x_mm = px_to_mm<72>(32.88f),
            .y_mm = px_to_mm<72>(104.31f),
            .short_name = "3",
            .long_name = "3",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = Knob_4,
            .x_mm = px_to_mm<72>(84.41f),
            .y_mm = px_to_mm<72>(104.31f),
            .short_name = "4",
            .long_name = "4",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = Knob_5,
            .x_mm = px_to_mm<72>(32.88f),
            .y_mm = px_to_mm<72>(163.62f),
            .short_name = "5",
            .long_name = "5",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = Knob_6,
            .x_mm = px_to_mm<72>(84.41f),
            .y_mm = px_to_mm<72>(163.62f),
            .short_name = "6",
            .long_name = "6",
            .default_val = 1.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = Knob_7,
            .x_mm = px_to_mm<72>(32.88f),
            .y_mm = px_to_mm<72>(222.39f),
            .short_name = "7",
            .long_name = "7",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = Knob_8,
            .x_mm = px_to_mm<72>(84.41f),
            .y_mm = px_to_mm<72>(222.39f),
            .short_name = "8",
            .long_name = "8",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 2;
    
    enum {
        InputClock = 0,
        InputReset = 1,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputClock,
            .x_mm = px_to_mm<72>(31.02f),
            .y_mm = px_to_mm<72>(272.5f),
            .short_name = "Clock",
            .long_name = "Clock",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputReset,
            .x_mm = px_to_mm<72>(84.69f),
            .y_mm = px_to_mm<72>(272.5f),
            .short_name = "Reset",
            .long_name = "Reset",
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
            .x_mm = px_to_mm<72>(31.02f),
            .y_mm = px_to_mm<72>(314.17f),
            .short_name = "Inv",
            .long_name = "Inv",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut,
            .x_mm = px_to_mm<72>(84.69f),
            .y_mm = px_to_mm<72>(314.17f),
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
