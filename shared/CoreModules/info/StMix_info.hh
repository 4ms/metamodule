#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct StMixInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"StMix"};
    static constexpr std::string_view description{"Stereo Mixer"};
    static constexpr uint32_t width_hp = 18;
    static constexpr std::string_view svg_filename{"res/modules/StMix-artwork.svg"};

    static constexpr int NumKnobs = 8;
    
    enum {
        KnobLevel_1 = 0,
        KnobLevel_2 = 1,
        KnobLevel_3 = 2,
        KnobLevel_4 = 3,
        KnobPan_1 = 4,
        KnobPan_2 = 5,
        KnobPan_3 = 6,
        KnobPan_4 = 7,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobLevel_1,
            .x_mm = px_to_mm<72>(35.29f),
            .y_mm = px_to_mm<72>(58.14f),
            .short_name = "Level 1",
            .long_name = "Level 1",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLevel_2,
            .x_mm = px_to_mm<72>(98.25f),
            .y_mm = px_to_mm<72>(58.14f),
            .short_name = "Level 2",
            .long_name = "Level 2",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLevel_3,
            .x_mm = px_to_mm<72>(161.2f),
            .y_mm = px_to_mm<72>(58.14f),
            .short_name = "Level 3",
            .long_name = "Level 3",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLevel_4,
            .x_mm = px_to_mm<72>(224.16f),
            .y_mm = px_to_mm<72>(58.14f),
            .short_name = "Level 4",
            .long_name = "Level 4",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobPan_1,
            .x_mm = px_to_mm<72>(35.29f),
            .y_mm = px_to_mm<72>(150.52f),
            .short_name = "Pan 1",
            .long_name = "Pan 1",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobPan_2,
            .x_mm = px_to_mm<72>(98.25f),
            .y_mm = px_to_mm<72>(150.3f),
            .short_name = "Pan 2",
            .long_name = "Pan 2",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobPan_3,
            .x_mm = px_to_mm<72>(161.1f),
            .y_mm = px_to_mm<72>(150.46f),
            .short_name = "Pan 3",
            .long_name = "Pan 3",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobPan_4,
            .x_mm = px_to_mm<72>(224.16f),
            .y_mm = px_to_mm<72>(150.3f),
            .short_name = "Pan 4",
            .long_name = "Pan 4",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 8;
    
    enum {
        InputIn_1_L = 0,
        InputIn_1_R = 1,
        InputIn_2_L = 2,
        InputIn_2_R = 3,
        InputIn_3_L = 4,
        InputIn_3_R = 5,
        InputIn_4_L = 6,
        InputIn_4_R = 7,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputIn_1_L,
            .x_mm = px_to_mm<72>(34.91f),
            .y_mm = px_to_mm<72>(222.82f),
            .short_name = "In 1 L",
            .long_name = "In 1 L",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_1_R,
            .x_mm = px_to_mm<72>(34.91f),
            .y_mm = px_to_mm<72>(271.92f),
            .short_name = "In 1 R",
            .long_name = "In 1 R",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_2_L,
            .x_mm = px_to_mm<72>(97.94f),
            .y_mm = px_to_mm<72>(222.82f),
            .short_name = "In 2 L",
            .long_name = "In 2 L",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_2_R,
            .x_mm = px_to_mm<72>(97.94f),
            .y_mm = px_to_mm<72>(271.92f),
            .short_name = "In 2 R",
            .long_name = "In 2 R",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_3_L,
            .x_mm = px_to_mm<72>(160.97f),
            .y_mm = px_to_mm<72>(222.82f),
            .short_name = "In 3 L",
            .long_name = "In 3 L",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_3_R,
            .x_mm = px_to_mm<72>(160.97f),
            .y_mm = px_to_mm<72>(271.92f),
            .short_name = "In 3 R",
            .long_name = "In 3 R",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_4_L,
            .x_mm = px_to_mm<72>(224.01f),
            .y_mm = px_to_mm<72>(222.82f),
            .short_name = "In 4 L",
            .long_name = "In 4 L",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_4_R,
            .x_mm = px_to_mm<72>(224.01f),
            .y_mm = px_to_mm<72>(271.92f),
            .short_name = "In 4 R",
            .long_name = "In 4 R",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 2;
    
    enum {
        OutputL = 0,
        OutputR = 1,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputL,
            .x_mm = px_to_mm<72>(138.46f),
            .y_mm = px_to_mm<72>(322.31f),
            .short_name = "L",
            .long_name = "L",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputR,
            .x_mm = px_to_mm<72>(206.48f),
            .y_mm = px_to_mm<72>(322.31f),
            .short_name = "R",
            .long_name = "R",
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
