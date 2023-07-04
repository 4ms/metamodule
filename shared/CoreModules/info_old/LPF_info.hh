#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct LPFInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"LPF"};
    static constexpr std::string_view description{"Low-Pass Filter"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/LPF-artwork.svg"};

    static constexpr int NumKnobs = 2;
    
    enum {
        KnobCutoff = 0,
        KnobQ = 1,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobCutoff,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(46.53f),
            .short_name = "Cutoff",
            .long_name = "Cutoff",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobQ,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(94.22f),
            .short_name = "Q",
            .long_name = "Q",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 2;
    
    enum {
        InputCv = 0,
        InputInput = 1,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputCv,
            .x_mm = px_to_mm<72>(28.63f),
            .y_mm = px_to_mm<72>(214.97f),
            .short_name = "CV",
            .long_name = "CV",
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

    static constexpr int NumSwitches = 1;
    
    enum {
        SwitchMode = 0,
    };

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
        {
            .id = SwitchMode,
            .x_mm = px_to_mm<72>(28.65f),
            .y_mm = px_to_mm<72>(166.04f),
            .short_name = "Mode",
            .long_name = "Mode",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
    }};

    static constexpr int NumDiscreteLeds = 0;
    

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
    }};

};
