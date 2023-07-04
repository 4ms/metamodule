#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct QuantInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Quant"};
    static constexpr std::string_view description{"Quantizer"};
    static constexpr uint32_t width_hp = 10;
    static constexpr std::string_view svg_filename{"res/modules/Quant-artwork.svg"};

    static constexpr int NumKnobs = 3;
    
    enum {
        KnobScale = 0,
        KnobRoot = 1,
        KnobTranspose = 2,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobScale,
            .x_mm = px_to_mm<72>(37.85f),
            .y_mm = px_to_mm<72>(151.34f),
            .short_name = "Scale",
            .long_name = "Scale",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobRoot,
            .x_mm = px_to_mm<72>(106.4f),
            .y_mm = px_to_mm<72>(151.34f),
            .short_name = "Root",
            .long_name = "Root",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobTranspose,
            .x_mm = px_to_mm<72>(72.13f),
            .y_mm = px_to_mm<72>(201.33f),
            .short_name = "Transpose",
            .long_name = "Transpose",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 3;
    
    enum {
        InputInput = 0,
        InputScale_Cv = 1,
        InputRoot_Cv = 2,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputInput,
            .x_mm = px_to_mm<72>(29.94f),
            .y_mm = px_to_mm<72>(272.23f),
            .short_name = "Input",
            .long_name = "Input",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputScale_Cv,
            .x_mm = px_to_mm<72>(72.13f),
            .y_mm = px_to_mm<72>(272.23f),
            .short_name = "Scale CV",
            .long_name = "Scale CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputRoot_Cv,
            .x_mm = px_to_mm<72>(115.17f),
            .y_mm = px_to_mm<72>(272.23f),
            .short_name = "Root CV",
            .long_name = "Root CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 3;
    
    enum {
        OutputThru = 0,
        OutputPre = 1,
        OutputOut = 2,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputThru,
            .x_mm = px_to_mm<72>(29.94f),
            .y_mm = px_to_mm<72>(313.84f),
            .short_name = "Thru",
            .long_name = "Thru",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputPre,
            .x_mm = px_to_mm<72>(72.13f),
            .y_mm = px_to_mm<72>(313.84f),
            .short_name = "Pre",
            .long_name = "Pre",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut,
            .x_mm = px_to_mm<72>(115.17f),
            .y_mm = px_to_mm<72>(313.84f),
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
