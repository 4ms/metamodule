#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct ADEnvInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"ADEnv"};
    static constexpr std::string_view description{"Attack Decay Envelope"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/ADEnv-artwork.svg"};

    static constexpr int NumKnobs = 4;
    
    enum {
        KnobAttack = 0,
        KnobDecay = 1,
        KnobA_Shape = 2,
        KnobD_Shape = 3,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobAttack,
            .x_mm = px_to_mm<72>(31.85f),
            .y_mm = px_to_mm<72>(47.96f),
            .short_name = "Attack",
            .long_name = "Attack",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobDecay,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(47.96f),
            .short_name = "Decay",
            .long_name = "Decay",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobA_Shape,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(104.94f),
            .short_name = "A Shape",
            .long_name = "A Shape",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobD_Shape,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(104.94f),
            .short_name = "D Shape",
            .long_name = "D Shape",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 5;
    
    enum {
        InputGate = 0,
        InputDecay_Cv = 1,
        InputAttack_Cv = 2,
        InputD_Shape_Cv = 3,
        InputA_Shape_Cv = 4,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputGate,
            .x_mm = px_to_mm<72>(32.1f),
            .y_mm = px_to_mm<72>(167.36f),
            .short_name = "Gate",
            .long_name = "Gate",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputDecay_Cv,
            .x_mm = px_to_mm<72>(83.63f),
            .y_mm = px_to_mm<72>(167.36f),
            .short_name = "Decay CV",
            .long_name = "Decay CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputAttack_Cv,
            .x_mm = px_to_mm<72>(32.1f),
            .y_mm = px_to_mm<72>(214.57f),
            .short_name = "Attack CV",
            .long_name = "Attack CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputD_Shape_Cv,
            .x_mm = px_to_mm<72>(83.63f),
            .y_mm = px_to_mm<72>(214.57f),
            .short_name = "D Shape CV",
            .long_name = "D Shape CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputA_Shape_Cv,
            .x_mm = px_to_mm<72>(32.1f),
            .y_mm = px_to_mm<72>(263.64f),
            .short_name = "A Shape CV",
            .long_name = "A Shape CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 3;
    
    enum {
        OutputEod = 0,
        OutputEoa = 1,
        OutputOut = 2,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputEod,
            .x_mm = px_to_mm<72>(83.63f),
            .y_mm = px_to_mm<72>(263.67f),
            .short_name = "EOD",
            .long_name = "EOD",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputEoa,
            .x_mm = px_to_mm<72>(32.1f),
            .y_mm = px_to_mm<72>(311.23f),
            .short_name = "EOA",
            .long_name = "EOA",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut,
            .x_mm = px_to_mm<72>(83.63f),
            .y_mm = px_to_mm<72>(311.26f),
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
