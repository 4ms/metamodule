#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct KPLSInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"KPLS"};
    static constexpr std::string_view description{"Karplus–Strong Voice"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/KPLS-artwork.svg"};

    static constexpr int NumKnobs = 3;
    
    enum {
        KnobPitch = 0,
        KnobDecay = 1,
        KnobSpread = 2,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobPitch,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(47.15f),
            .short_name = "Pitch",
            .long_name = "Pitch",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobDecay,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(94.83f),
            .short_name = "Decay",
            .long_name = "Decay",
            .default_val = 0.25f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobSpread,
            .x_mm = px_to_mm<72>(29.1f),
            .y_mm = px_to_mm<72>(143.04f),
            .short_name = "Spread",
            .long_name = "Spread",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 2;
    
    enum {
        InputV_Oct = 0,
        InputTrig = 1,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputV_Oct,
            .x_mm = px_to_mm<72>(28.63f),
            .y_mm = px_to_mm<72>(215.22f),
            .short_name = "V/Oct",
            .long_name = "V/Oct",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputTrig,
            .x_mm = px_to_mm<72>(28.63f),
            .y_mm = px_to_mm<72>(264.32f),
            .short_name = "Trig",
            .long_name = "Trig",
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
            .y_mm = px_to_mm<72>(312.54f),
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
