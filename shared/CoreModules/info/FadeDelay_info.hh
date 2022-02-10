#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/module_info_base.hh"

struct FadeDelayInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"FadeDelay"};
    static constexpr std::string_view description{"Fade Delay"};
    static constexpr uint32_t width_hp = 10;
    static constexpr std::string_view svg_filename{"res/modules/FadeDelay-artwork.svg"};

    static constexpr int NumKnobs = 5;
    
    enum {
        KnobDelay = 0,
        KnobFeed = 1,
        KnobFade = 2,
        KnobMix = 3,
        KnobDelay_Cv = 4,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobDelay,
            .x_mm = px_to_mm<72>(37.85f),
            .y_mm = px_to_mm<72>(46.42f),
            .short_name = "Delay",
            .long_name = "Delay",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobFeed,
            .x_mm = px_to_mm<72>(106.4f),
            .y_mm = px_to_mm<72>(46.42f),
            .short_name = "Feed",
            .long_name = "Feed",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobFade,
            .x_mm = px_to_mm<72>(37.85f),
            .y_mm = px_to_mm<72>(104.62f),
            .short_name = "Fade",
            .long_name = "Fade",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobMix,
            .x_mm = px_to_mm<72>(106.4f),
            .y_mm = px_to_mm<72>(104.62f),
            .short_name = "Mix",
            .long_name = "Mix",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobDelay_Cv,
            .x_mm = px_to_mm<72>(72.12f),
            .y_mm = px_to_mm<72>(162.82f),
            .short_name = "Delay CV",
            .long_name = "Delay CV",
            .default_val = 1.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 5;
    
    enum {
        InputInput = 0,
        InputDelay_Cv_Jack = 1,
        InputFeed_Cv = 2,
        InputClock = 3,
        InputFade_Cv = 4,
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
            .id = InputDelay_Cv_Jack,
            .x_mm = px_to_mm<72>(72.13f),
            .y_mm = px_to_mm<72>(272.23f),
            .short_name = "Delay CV Jack",
            .long_name = "Delay CV Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputFeed_Cv,
            .x_mm = px_to_mm<72>(115.17f),
            .y_mm = px_to_mm<72>(272.23f),
            .short_name = "Feed CV",
            .long_name = "Feed CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputClock,
            .x_mm = px_to_mm<72>(29.94f),
            .y_mm = px_to_mm<72>(313.84f),
            .short_name = "Clock",
            .long_name = "Clock",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputFade_Cv,
            .x_mm = px_to_mm<72>(72.13f),
            .y_mm = px_to_mm<72>(313.84f),
            .short_name = "Fade CV",
            .long_name = "Fade CV",
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
