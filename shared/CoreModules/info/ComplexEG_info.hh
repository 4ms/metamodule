#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/module_info_base.hh"

struct ComplexEGInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"ComplexEG"};
    static constexpr std::string_view description{"Complex Envelope Generator"};
    static constexpr uint32_t width_hp = 15;
    static constexpr std::string_view svg_filename{"res/modules/ComplexEG-artwork.svg"};

    static constexpr int NumKnobs = 8;
    
    enum {
        KnobDecay = 0,
        KnobRelease = 1,
        KnobAttack = 2,
        KnobCurve = 3,
        KnobCurve = 4,
        KnobCurve = 5,
        KnobHold = 6,
        KnobSustain = 7,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobDecay,
            .x_mm = px_to_mm<72>(108.12f),
            .y_mm = px_to_mm<72>(45.53f),
            .short_name = "Decay",
            .long_name = "Decay",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobRelease,
            .x_mm = px_to_mm<72>(172.62f),
            .y_mm = px_to_mm<72>(45.53f),
            .short_name = "Release",
            .long_name = "Release",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobAttack,
            .x_mm = px_to_mm<72>(43.62f),
            .y_mm = px_to_mm<72>(46.2f),
            .short_name = "Attack",
            .long_name = "Attack",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobCurve,
            .x_mm = px_to_mm<72>(43.62f),
            .y_mm = px_to_mm<72>(104.51f),
            .short_name = "Curve",
            .long_name = "Curve",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobCurve,
            .x_mm = px_to_mm<72>(108.12f),
            .y_mm = px_to_mm<72>(104.51f),
            .short_name = "Curve",
            .long_name = "Curve",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobCurve,
            .x_mm = px_to_mm<72>(172.62f),
            .y_mm = px_to_mm<72>(104.51f),
            .short_name = "Curve",
            .long_name = "Curve",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobHold,
            .x_mm = px_to_mm<72>(172.52f),
            .y_mm = px_to_mm<72>(163.23f),
            .short_name = "Hold",
            .long_name = "Hold",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobSustain,
            .x_mm = px_to_mm<72>(43.62f),
            .y_mm = px_to_mm<72>(163.28f),
            .short_name = "Sustain",
            .long_name = "Sustain",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 11;
    
    enum {
        InputInput = 0,
        InputAttack = 1,
        InputDecay = 2,
        InputRelease = 3,
        InputAttack = 4,
        InputSustain = 5,
        InputHold = 6,
        InputDecay = 7,
        InputRelease = 8,
        InputSustain = 9,
        InputHold = 10,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputInput,
            .x_mm = px_to_mm<72>(36.45f),
            .y_mm = px_to_mm<72>(214.13f),
            .short_name = "Input",
            .long_name = "Input",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputAttack,
            .x_mm = px_to_mm<72>(83.96f),
            .y_mm = px_to_mm<72>(214.13f),
            .short_name = "Attack",
            .long_name = "Attack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputDecay,
            .x_mm = px_to_mm<72>(131.96f),
            .y_mm = px_to_mm<72>(214.13f),
            .short_name = "Decay",
            .long_name = "Decay",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputRelease,
            .x_mm = px_to_mm<72>(179.96f),
            .y_mm = px_to_mm<72>(214.13f),
            .short_name = "Release",
            .long_name = "Release",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputAttack,
            .x_mm = px_to_mm<72>(36.45f),
            .y_mm = px_to_mm<72>(265.71f),
            .short_name = "Attack",
            .long_name = "Attack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSustain,
            .x_mm = px_to_mm<72>(83.96f),
            .y_mm = px_to_mm<72>(265.71f),
            .short_name = "Sustain",
            .long_name = "Sustain",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputHold,
            .x_mm = px_to_mm<72>(131.96f),
            .y_mm = px_to_mm<72>(265.71f),
            .short_name = "Hold",
            .long_name = "Hold",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputDecay,
            .x_mm = px_to_mm<72>(179.96f),
            .y_mm = px_to_mm<72>(265.71f),
            .short_name = "Decay",
            .long_name = "Decay",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputRelease,
            .x_mm = px_to_mm<72>(36.45f),
            .y_mm = px_to_mm<72>(309.84f),
            .short_name = "Release",
            .long_name = "Release",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSustain,
            .x_mm = px_to_mm<72>(83.96f),
            .y_mm = px_to_mm<72>(309.84f),
            .short_name = "Sustain",
            .long_name = "Sustain",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputHold,
            .x_mm = px_to_mm<72>(131.96f),
            .y_mm = px_to_mm<72>(309.84f),
            .short_name = "Hold",
            .long_name = "Hold",
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
            .x_mm = px_to_mm<72>(179.96f),
            .y_mm = px_to_mm<72>(309.84f),
            .short_name = "Out",
            .long_name = "Out",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 1;
    
    enum {
        SwitchLoop = 0,
    };

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
        {
            .id = SwitchLoop,
            .x_mm = px_to_mm<72>(108.12f),
            .y_mm = px_to_mm<72>(159.77f),
            .short_name = "Loop",
            .long_name = "Loop",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
    }};

    static constexpr int NumDiscreteLeds = 0;
    

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
    }};

};
