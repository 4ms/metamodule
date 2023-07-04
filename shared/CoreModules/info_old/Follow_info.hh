#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct FollowInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Follow"};
    static constexpr std::string_view description{"Follower"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Follow-artwork.svg"};

    static constexpr int NumKnobs = 3;
    
    enum {
        KnobRise = 0,
        KnobFall = 1,
        KnobThresh = 2,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobRise,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(46.67f),
            .short_name = "Rise",
            .long_name = "Rise",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobFall,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(94.35f),
            .short_name = "Fall",
            .long_name = "Fall",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobThresh,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(142.56f),
            .short_name = "Thresh",
            .long_name = "Thresh",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 1;
    
    enum {
        InputInput = 0,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputInput,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(214.97f),
            .short_name = "Input",
            .long_name = "Input",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 2;
    
    enum {
        OutputGate = 0,
        OutputEnv = 1,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputGate,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(264.07f),
            .short_name = "Gate",
            .long_name = "Gate",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputEnv,
            .x_mm = px_to_mm<72>(28.93f),
            .y_mm = px_to_mm<72>(312.29f),
            .short_name = "Env",
            .long_name = "Env",
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
