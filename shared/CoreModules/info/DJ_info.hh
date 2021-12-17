#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/module_info_base.hh"

struct DJInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"DJ"};
    static constexpr std::string_view description{"Djembe"};
    static constexpr uint32_t width_hp = 577;
    static constexpr std::string_view svg_filename{"res/modules/DJ-artwork.svg"};

    static constexpr int NumKnobs = 4;
    
    enum {
        KnobPitch = 0,
        KnobSharpness = 1,
        KnobHit = 2,
        KnobStrike_Amt = 3,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobPitch,
            .x_mm = px_to_mm<72>(32.88f),
            .y_mm = px_to_mm<72>(57.97f),
            .short_name = "Pitch",
            .long_name = "Pitch",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobSharpness,
            .x_mm = px_to_mm<72>(84.41f),
            .y_mm = px_to_mm<72>(57.97f),
            .short_name = "Sharpness",
            .long_name = "Sharpness",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobHit,
            .x_mm = px_to_mm<72>(32.88f),
            .y_mm = px_to_mm<72>(119.21f),
            .short_name = "Hit",
            .long_name = "Hit",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobStrike_Amt,
            .x_mm = px_to_mm<72>(84.41f),
            .y_mm = px_to_mm<72>(119.21f),
            .short_name = "Strike Amt",
            .long_name = "Strike Amt",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 5;
    
    enum {
        InputPitch = 0,
        InputSharp = 1,
        InputHit = 2,
        InputStrike = 3,
        InputTrigger = 4,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputPitch,
            .x_mm = px_to_mm<72>(31.73f),
            .y_mm = px_to_mm<72>(214.66f),
            .short_name = "Pitch",
            .long_name = "Pitch",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSharp,
            .x_mm = px_to_mm<72>(82.92f),
            .y_mm = px_to_mm<72>(214.66f),
            .short_name = "Sharp",
            .long_name = "Sharp",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputHit,
            .x_mm = px_to_mm<72>(31.73f),
            .y_mm = px_to_mm<72>(263.38f),
            .short_name = "Hit",
            .long_name = "Hit",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputStrike,
            .x_mm = px_to_mm<72>(82.92f),
            .y_mm = px_to_mm<72>(263.38f),
            .short_name = "Strike",
            .long_name = "Strike",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputTrigger,
            .x_mm = px_to_mm<72>(31.73f),
            .y_mm = px_to_mm<72>(312.1f),
            .short_name = "Trigger",
            .long_name = "Trigger",
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
            .x_mm = px_to_mm<72>(82.92f),
            .y_mm = px_to_mm<72>(312.1f),
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
