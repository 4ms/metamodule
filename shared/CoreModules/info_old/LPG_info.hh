#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct LPGInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"LPG"};
    static constexpr std::string_view description{"Low Pass Gate"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/LPG-artwork.svg"};

    static constexpr int NumKnobs = 3;
    
    enum {
        KnobLevel = 0,
        KnobCv = 1,
        KnobDecay = 2,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobLevel,
            .x_mm = px_to_mm<72>(57.94f),
            .y_mm = px_to_mm<72>(57.97f),
            .short_name = "Level",
            .long_name = "Level",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobCv,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(119.21f),
            .short_name = "CV",
            .long_name = "CV",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobDecay,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(119.21f),
            .short_name = "Decay",
            .long_name = "Decay",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 3;
    
    enum {
        InputInput = 0,
        InputPing = 1,
        InputCv_Jack = 2,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputInput,
            .x_mm = px_to_mm<72>(32.13f),
            .y_mm = px_to_mm<72>(272.09f),
            .short_name = "Input",
            .long_name = "Input",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputPing,
            .x_mm = px_to_mm<72>(83.32f),
            .y_mm = px_to_mm<72>(272.09f),
            .short_name = "Ping",
            .long_name = "Ping",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputCv_Jack,
            .x_mm = px_to_mm<72>(32.13f),
            .y_mm = px_to_mm<72>(313.7f),
            .short_name = "CV Jack",
            .long_name = "CV Jack",
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
            .x_mm = px_to_mm<72>(83.32f),
            .y_mm = px_to_mm<72>(313.7f),
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
