#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/module_info_base.hh"

struct VCAInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"VCA"};
    static constexpr std::string_view description{"Voltage Controlled Amplifier"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/VCA-artwork.svg"};

    static constexpr int NumKnobs = 4;
    
    enum {
        KnobPre = 0,
        KnobPost = 1,
        KnobOffset = 2,
        KnobCv = 3,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobPre,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(57.97f),
            .short_name = "Pre",
            .long_name = "Pre",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobPost,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(57.97f),
            .short_name = "Post",
            .long_name = "Post",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobOffset,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(119.21f),
            .short_name = "Offset",
            .long_name = "Offset",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobCv,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(119.21f),
            .short_name = "CV",
            .long_name = "CV",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 2;
    
    enum {
        InputInput = 0,
        InputCv_Jack = 1,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputInput,
            .x_mm = px_to_mm<72>(57.69f),
            .y_mm = px_to_mm<72>(271.57f),
            .short_name = "Input",
            .long_name = "Input",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputCv_Jack,
            .x_mm = px_to_mm<72>(32.16f),
            .y_mm = px_to_mm<72>(313.17f),
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
