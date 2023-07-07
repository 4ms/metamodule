#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct GateInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Gate"};
    static constexpr std::string_view description{"Gate Delay"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Gate-artwork.svg"};

    static constexpr int NumKnobs = 2;
    
    enum {
        KnobLength = 0,
        KnobDelay = 1,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobLength,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(46.52f),
            .short_name = "Length",
            .long_name = "Length",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobDelay,
            .x_mm = px_to_mm<72>(28.92f),
            .y_mm = px_to_mm<72>(94.2f),
            .short_name = "Delay",
            .long_name = "Delay",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 3;
    
    enum {
        InputLength_Cv = 0,
        InputDelay_Cv = 1,
        InputInput = 2,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputLength_Cv,
            .x_mm = px_to_mm<72>(28.92f),
            .y_mm = px_to_mm<72>(168.85f),
            .short_name = "Length CV",
            .long_name = "Length CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputDelay_Cv,
            .x_mm = px_to_mm<72>(28.92f),
            .y_mm = px_to_mm<72>(214.97f),
            .short_name = "Delay CV",
            .long_name = "Delay CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputInput,
            .x_mm = px_to_mm<72>(28.92f),
            .y_mm = px_to_mm<72>(264.07f),
            .short_name = "Input",
            .long_name = "Input",
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
            .x_mm = px_to_mm<72>(28.92f),
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
