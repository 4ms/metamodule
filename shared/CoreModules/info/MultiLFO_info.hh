#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct MultiLFOInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"MultiLFO"};
    static constexpr std::string_view description{"Multi LFO"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/MultiLFO-artwork.svg"};

    static constexpr int NumKnobs = 3;
    
    enum {
        KnobRate = 0,
        KnobPhase = 1,
        KnobPw = 2,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobRate,
            .x_mm = px_to_mm<72>(57.67f),
            .y_mm = px_to_mm<72>(55.73f),
            .short_name = "Rate",
            .long_name = "Rate",
            .default_val = 0.5f,
            .knob_style = KnobDef::Large,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobPhase,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(119.41f),
            .short_name = "Phase",
            .long_name = "Phase",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobPw,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(119.75f),
            .short_name = "PW",
            .long_name = "PW",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 4;
    
    enum {
        InputReset = 0,
        InputPw_Cv = 1,
        InputRate_Cv = 2,
        InputPhase_Cv = 3,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputReset,
            .x_mm = px_to_mm<72>(32.1f),
            .y_mm = px_to_mm<72>(167.36f),
            .short_name = "Reset",
            .long_name = "Reset",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputPw_Cv,
            .x_mm = px_to_mm<72>(83.63f),
            .y_mm = px_to_mm<72>(167.36f),
            .short_name = "PW CV",
            .long_name = "PW CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputRate_Cv,
            .x_mm = px_to_mm<72>(32.1f),
            .y_mm = px_to_mm<72>(214.57f),
            .short_name = "Rate CV",
            .long_name = "Rate CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputPhase_Cv,
            .x_mm = px_to_mm<72>(83.63f),
            .y_mm = px_to_mm<72>(214.57f),
            .short_name = "Phase CV",
            .long_name = "Phase CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 4;
    
    enum {
        OutputInv_Saw = 0,
        OutputPulse = 1,
        OutputSaw = 2,
        OutputSine = 3,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputInv_Saw,
            .x_mm = px_to_mm<72>(32.1f),
            .y_mm = px_to_mm<72>(263.64f),
            .short_name = "Inv Saw",
            .long_name = "Inv Saw",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputPulse,
            .x_mm = px_to_mm<72>(83.63f),
            .y_mm = px_to_mm<72>(263.67f),
            .short_name = "Pulse",
            .long_name = "Pulse",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputSaw,
            .x_mm = px_to_mm<72>(32.1f),
            .y_mm = px_to_mm<72>(311.23f),
            .short_name = "Saw",
            .long_name = "Saw",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputSine,
            .x_mm = px_to_mm<72>(83.63f),
            .y_mm = px_to_mm<72>(311.26f),
            .short_name = "Sine",
            .long_name = "Sine",
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
