#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct L4Info : ModuleInfoBase {
    static constexpr std::string_view slug{"L4"};
    static constexpr std::string_view description{"Listen Four"};
    static constexpr uint32_t width_hp = 10;
    static constexpr std::string_view svg_filename{"res/modules/L4-artwork.svg"};

    static constexpr int NumKnobs = 8;
    
    enum {
        KnobPan_1 = 0,
        KnobLevel_1 = 1,
        KnobPan_2 = 2,
        KnobLevel_2 = 3,
        KnobLevel_3 = 4,
        KnobLevel_4 = 5,
        KnobHeadphone_Level = 6,
        KnobMain_Level = 7,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobPan_1,
            .x_mm = px_to_mm<72>(62.33f),
            .y_mm = px_to_mm<72>(46.17f),
            .short_name = "Pan 1",
            .long_name = "Pan 1",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLevel_1,
            .x_mm = px_to_mm<72>(111.89f),
            .y_mm = px_to_mm<72>(59.09f),
            .short_name = "Level 1",
            .long_name = "Level 1",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobPan_2,
            .x_mm = px_to_mm<72>(62.33f),
            .y_mm = px_to_mm<72>(103.86f),
            .short_name = "Pan 2",
            .long_name = "Pan 2",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLevel_2,
            .x_mm = px_to_mm<72>(111.89f),
            .y_mm = px_to_mm<72>(116.69f),
            .short_name = "Level 2",
            .long_name = "Level 2",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLevel_3,
            .x_mm = px_to_mm<72>(111.89f),
            .y_mm = px_to_mm<72>(174.29f),
            .short_name = "Level 3",
            .long_name = "Level 3",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLevel_4,
            .x_mm = px_to_mm<72>(111.89f),
            .y_mm = px_to_mm<72>(232.15f),
            .short_name = "Level 4",
            .long_name = "Level 4",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobHeadphone_Level,
            .x_mm = px_to_mm<72>(23.27f),
            .y_mm = px_to_mm<72>(318.85f),
            .short_name = "Headphone Level",
            .long_name = "Headphone Level",
            .default_val = 0.875f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobMain_Level,
            .x_mm = px_to_mm<72>(71.7f),
            .y_mm = px_to_mm<72>(302.94f),
            .short_name = "Main Level",
            .long_name = "Main Level",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 6;
    
    enum {
        InputIn_1 = 0,
        InputIn_2 = 1,
        InputIn_3_L = 2,
        InputIn_3_R = 3,
        InputIn_4_L = 4,
        InputIn_4_R = 5,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputIn_1,
            .x_mm = px_to_mm<72>(23.31f),
            .y_mm = px_to_mm<72>(46.17f),
            .short_name = "In 1",
            .long_name = "In 1",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_2,
            .x_mm = px_to_mm<72>(23.31f),
            .y_mm = px_to_mm<72>(103.92f),
            .short_name = "In 2",
            .long_name = "In 2",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_3_L,
            .x_mm = px_to_mm<72>(23.31f),
            .y_mm = px_to_mm<72>(161.52f),
            .short_name = "In 3 L",
            .long_name = "In 3 L",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_3_R,
            .x_mm = px_to_mm<72>(62.91f),
            .y_mm = px_to_mm<72>(161.52f),
            .short_name = "In 3 R",
            .long_name = "In 3 R",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_4_L,
            .x_mm = px_to_mm<72>(23.31f),
            .y_mm = px_to_mm<72>(219.12f),
            .short_name = "In 4 L",
            .long_name = "In 4 L",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_4_R,
            .x_mm = px_to_mm<72>(62.91f),
            .y_mm = px_to_mm<72>(219.12f),
            .short_name = "In 4 R",
            .long_name = "In 4 R",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 3;
    
    enum {
        OutputHeadphone_Out = 0,
        OutputOut_Left = 1,
        OutputOut_Right = 2,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputHeadphone_Out,
            .x_mm = px_to_mm<72>(23.64f),
            .y_mm = px_to_mm<72>(266.4f),
            .short_name = "Headphone Out",
            .long_name = "Headphone Out",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_Left,
            .x_mm = px_to_mm<72>(122.02f),
            .y_mm = px_to_mm<72>(282.83f),
            .short_name = "Out Left",
            .long_name = "Out Left",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_Right,
            .x_mm = px_to_mm<72>(122.02f),
            .y_mm = px_to_mm<72>(326.07f),
            .short_name = "Out Right",
            .long_name = "Out Right",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 1;
    
    enum {
        SwitchMod___OR__Line = 0,
    };

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
        {
            .id = SwitchMod___OR__Line,
            .x_mm = px_to_mm<72>(67.265f),
            .y_mm = px_to_mm<72>(258.19f),
            .short_name = "Mod. | Line",
            .long_name = "Mod. | Line",
            .switch_type = SwitchDef::Toggle2pos,
            .orientation = SwitchDef::Horizontal,
            .encoder_knob_style = SwitchDef::None,
        },
    }};

    static constexpr int NumDiscreteLeds = 6;
    
    enum {
        LedLevel_1_Led = 0,
        LedLevel_2_Led = 1,
        LedLevel_3_Led = 2,
        LedLevel_4_Led = 3,
        LedOut_L_Led = 4,
        LedOut_R_Led = 5,
    };

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
        {
            .id = LedLevel_1_Led,
            .x_mm = px_to_mm<72>(87.38f),
            .y_mm = px_to_mm<72>(46.17f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLevel_2_Led,
            .x_mm = px_to_mm<72>(87.38f),
            .y_mm = px_to_mm<72>(105.8f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLevel_3_Led,
            .x_mm = px_to_mm<72>(87.38f),
            .y_mm = px_to_mm<72>(163.03f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLevel_4_Led,
            .x_mm = px_to_mm<72>(87.38f),
            .y_mm = px_to_mm<72>(221.73f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedOut_L_Led,
            .x_mm = px_to_mm<72>(98.07f),
            .y_mm = px_to_mm<72>(284.23f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedOut_R_Led,
            .x_mm = px_to_mm<72>(98.07f),
            .y_mm = px_to_mm<72>(316.53f),
            .led_color = LedDef::Red,
        },
    }};

};
