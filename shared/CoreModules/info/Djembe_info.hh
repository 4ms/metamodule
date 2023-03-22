#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct DjembeInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Djembe"};
    static constexpr std::string_view description{"Djembe Drum Voice"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/Djembe-artwork.svg"};

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
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(57.97f),
            .short_name = "Pitch",
            .long_name = "Pitch",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobSharpness,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(57.97f),
            .short_name = "Sharpness",
            .long_name = "Sharpness",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobHit,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(119.21f),
            .short_name = "Hit",
            .long_name = "Hit",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobStrike_Amt,
            .x_mm = px_to_mm<72>(83.49f),
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
        InputPitch_Cv = 0,
        InputSharp_Cv = 1,
        InputHit_Cv = 2,
        InputStrike_Cv = 3,
        InputTrigger = 4,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputPitch_Cv,
            .x_mm = px_to_mm<72>(32.13f),
            .y_mm = px_to_mm<72>(214.66f),
            .short_name = "Pitch CV",
            .long_name = "Pitch CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSharp_Cv,
            .x_mm = px_to_mm<72>(83.32f),
            .y_mm = px_to_mm<72>(214.66f),
            .short_name = "Sharp CV",
            .long_name = "Sharp CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputHit_Cv,
            .x_mm = px_to_mm<72>(32.13f),
            .y_mm = px_to_mm<72>(263.38f),
            .short_name = "Hit CV",
            .long_name = "Hit CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputStrike_Cv,
            .x_mm = px_to_mm<72>(83.32f),
            .y_mm = px_to_mm<72>(263.38f),
            .short_name = "Strike CV",
            .long_name = "Strike CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputTrigger,
            .x_mm = px_to_mm<72>(32.13f),
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
            .x_mm = px_to_mm<72>(83.32f),
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
