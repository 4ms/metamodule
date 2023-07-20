#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct FMInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"FM"};
    static constexpr std::string_view description{"FM Oscillator"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/FM-artwork.svg"};

    static constexpr int NumKnobs = 8;
    
    enum {
        KnobPitch = 0,
        KnobMix = 1,
        KnobIndex = 2,
        KnobIndex_Cv = 3,
        KnobRatio_C = 4,
        KnobRatio_F = 5,
        KnobShape = 6,
        KnobShape_Cv = 7,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobPitch,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(40.33f),
            .short_name = "Pitch",
            .long_name = "Pitch",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobMix,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(40.33f),
            .short_name = "Mix",
            .long_name = "Mix",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobIndex,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(83.47f),
            .short_name = "Index",
            .long_name = "Index",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobIndex_Cv,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(83.47f),
            .short_name = "Index CV",
            .long_name = "Index CV",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobRatio_C,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(126.62f),
            .short_name = "Ratio C",
            .long_name = "Ratio C",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobRatio_F,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(126.62f),
            .short_name = "Ratio F",
            .long_name = "Ratio F",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobShape,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(169.76f),
            .short_name = "Shape",
            .long_name = "Shape",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobShape_Cv,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(169.76f),
            .short_name = "Shape CV",
            .long_name = "Shape CV",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 5;
    
    enum {
        InputV_Oct_P = 0,
        InputV_Oct_S = 1,
        InputMix_Cv = 2,
        InputIndex_Cv_In = 3,
        InputShape_Cv = 4,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputV_Oct_P,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(214.56f),
            .short_name = "V/Oct P",
            .long_name = "V/Oct P",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputV_Oct_S,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(214.56f),
            .short_name = "V/Oct S",
            .long_name = "V/Oct S",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputMix_Cv,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(263.28f),
            .short_name = "Mix CV",
            .long_name = "Mix CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIndex_Cv_In,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(263.28f),
            .short_name = "Index CV In",
            .long_name = "Index CV In",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputShape_Cv,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(312.0f),
            .short_name = "Shape CV",
            .long_name = "Shape CV",
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
            .x_mm = px_to_mm<72>(83.49f),
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
