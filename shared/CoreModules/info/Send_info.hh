#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/module_info_base.hh"

struct SendInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Send"};
    static constexpr std::string_view description{"4 Ch. Send Module"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/Send-artwork.svg"};

    static constexpr int NumKnobs = 4;
    
    enum {
        KnobLevel_1 = 0,
        KnobLevel_2 = 1,
        KnobLevel_3 = 2,
        KnobLevel_4 = 3,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobLevel_1,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(57.97f),
            .short_name = "Level 1",
            .long_name = "Level 1",
            .default_val = 1.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLevel_2,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(57.97f),
            .short_name = "Level 2",
            .long_name = "Level 2",
            .default_val = 1.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLevel_3,
            .x_mm = px_to_mm<72>(31.96f),
            .y_mm = px_to_mm<72>(119.21f),
            .short_name = "Level 3",
            .long_name = "Level 3",
            .default_val = 1.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLevel_4,
            .x_mm = px_to_mm<72>(83.49f),
            .y_mm = px_to_mm<72>(119.21f),
            .short_name = "Level 4",
            .long_name = "Level 4",
            .default_val = 1.0f,
            .knob_style = KnobDef::Medium,
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
            .x_mm = px_to_mm<72>(57.93f),
            .y_mm = px_to_mm<72>(214.56f),
            .short_name = "Input",
            .long_name = "Input",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 4;
    
    enum {
        OutputOut_1 = 0,
        OutputOut_2 = 1,
        OutputOut_3 = 2,
        OutputOut_4 = 3,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputOut_1,
            .x_mm = px_to_mm<72>(32.39f),
            .y_mm = px_to_mm<72>(263.34f),
            .short_name = "Out 1",
            .long_name = "Out 1",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_2,
            .x_mm = px_to_mm<72>(83.42f),
            .y_mm = px_to_mm<72>(263.28f),
            .short_name = "Out 2",
            .long_name = "Out 2",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_3,
            .x_mm = px_to_mm<72>(31.89f),
            .y_mm = px_to_mm<72>(312.0f),
            .short_name = "Out 3",
            .long_name = "Out 3",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_4,
            .x_mm = px_to_mm<72>(83.42f),
            .y_mm = px_to_mm<72>(312.0f),
            .short_name = "Out 4",
            .long_name = "Out 4",
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
