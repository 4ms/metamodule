#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct ShiftInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Shift"};
    static constexpr std::string_view description{"Frequency Shifter"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Shift-artwork.svg"};

    static constexpr int NumKnobs = 3;
    
    enum {
        KnobCoarse = 0,
        KnobFine = 1,
        KnobMix = 2,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobCoarse,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(46.53f),
            .short_name = "Coarse",
            .long_name = "Coarse",
            .default_val = 0.25f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobFine,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(94.22f),
            .short_name = "Fine",
            .long_name = "Fine",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobMix,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(142.91f),
            .short_name = "Mix",
            .long_name = "Mix",
            .default_val = 0.875f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 2;
    
    enum {
        InputCoarse_Cv = 0,
        InputInput = 1,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputCoarse_Cv,
            .x_mm = px_to_mm<72>(28.63f),
            .y_mm = px_to_mm<72>(214.97f),
            .short_name = "Coarse CV",
            .long_name = "Coarse CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputInput,
            .x_mm = px_to_mm<72>(28.63f),
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
            .x_mm = px_to_mm<72>(28.63f),
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
