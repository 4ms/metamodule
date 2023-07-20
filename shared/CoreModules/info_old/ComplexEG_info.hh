#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct ComplexEGInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"ComplexEG"};
    static constexpr std::string_view description{"Complex Envelope Generator"};
    static constexpr uint32_t width_hp = 15;
    static constexpr std::string_view svg_filename{"res/modules/ComplexEG-artwork.svg"};

    static constexpr int NumKnobs = 8;
    
    enum {
        KnobAttack = 0,
        KnobHold = 1,
        KnobDecay = 2,
        KnobSustain = 3,
        KnobRelease = 4,
        KnobA_Curve = 5,
        KnobD_Curve = 6,
        KnobR_Curve = 7,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
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
            .id = KnobHold,
            .x_mm = px_to_mm<72>(43.62f),
            .y_mm = px_to_mm<72>(163.28f),
            .short_name = "Hold",
            .long_name = "Hold",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
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
            .id = KnobSustain,
            .x_mm = px_to_mm<72>(172.52f),
            .y_mm = px_to_mm<72>(163.23f),
            .short_name = "Sustain",
            .long_name = "Sustain",
            .default_val = 0.0f,
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
            .id = KnobA_Curve,
            .x_mm = px_to_mm<72>(43.62f),
            .y_mm = px_to_mm<72>(104.51f),
            .short_name = "A Curve",
            .long_name = "A Curve",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobD_Curve,
            .x_mm = px_to_mm<72>(108.12f),
            .y_mm = px_to_mm<72>(104.51f),
            .short_name = "D Curve",
            .long_name = "D Curve",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobR_Curve,
            .x_mm = px_to_mm<72>(172.62f),
            .y_mm = px_to_mm<72>(104.51f),
            .short_name = "R Curve",
            .long_name = "R Curve",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 6;
    
    enum {
        InputInput = 0,
        InputAttack_Cv = 1,
        InputHold_Cv = 2,
        InputDecay_Cv = 3,
        InputSustain_Cv = 4,
        InputRelease_Cv = 5,
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
            .id = InputAttack_Cv,
            .x_mm = px_to_mm<72>(83.96f),
            .y_mm = px_to_mm<72>(214.13f),
            .short_name = "Attack CV",
            .long_name = "Attack CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputHold_Cv,
            .x_mm = px_to_mm<72>(83.96f),
            .y_mm = px_to_mm<72>(265.71f),
            .short_name = "Hold CV",
            .long_name = "Hold CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputDecay_Cv,
            .x_mm = px_to_mm<72>(131.96f),
            .y_mm = px_to_mm<72>(214.13f),
            .short_name = "Decay CV",
            .long_name = "Decay CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSustain_Cv,
            .x_mm = px_to_mm<72>(131.96f),
            .y_mm = px_to_mm<72>(265.71f),
            .short_name = "Sustain CV",
            .long_name = "Sustain CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputRelease_Cv,
            .x_mm = px_to_mm<72>(179.96f),
            .y_mm = px_to_mm<72>(214.13f),
            .short_name = "Release CV",
            .long_name = "Release CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 6;
    
    enum {
        OutputAttack_Out = 0,
        OutputHold_Out = 1,
        OutputDecay_Out = 2,
        OutputSustain_Out = 3,
        OutputRelease_Out = 4,
        OutputOut = 5,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputAttack_Out,
            .x_mm = px_to_mm<72>(36.45f),
            .y_mm = px_to_mm<72>(265.71f),
            .short_name = "Attack Out",
            .long_name = "Attack Out",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputHold_Out,
            .x_mm = px_to_mm<72>(36.45f),
            .y_mm = px_to_mm<72>(309.84f),
            .short_name = "Hold Out",
            .long_name = "Hold Out",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputDecay_Out,
            .x_mm = px_to_mm<72>(83.96f),
            .y_mm = px_to_mm<72>(309.84f),
            .short_name = "Decay Out",
            .long_name = "Decay Out",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputSustain_Out,
            .x_mm = px_to_mm<72>(131.96f),
            .y_mm = px_to_mm<72>(309.84f),
            .short_name = "Sustain Out",
            .long_name = "Sustain Out",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputRelease_Out,
            .x_mm = px_to_mm<72>(179.96f),
            .y_mm = px_to_mm<72>(265.71f),
            .short_name = "Release Out",
            .long_name = "Release Out",
            .signal_type = OutJackDef::Analog,
        },
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
