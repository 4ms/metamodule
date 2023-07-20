#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct SISMInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"SISM"};
    static constexpr std::string_view description{"Shifting Inverting Signal Mingler"};
    static constexpr uint32_t width_hp = 12;
    static constexpr std::string_view svg_filename{"res/modules/SISM-artwork.svg"};

    static constexpr int NumKnobs = 8;
    
    enum {
        KnobScale_1 = 0,
        KnobShift_1 = 1,
        KnobScale_2 = 2,
        KnobShift_2 = 3,
        KnobScale_3 = 4,
        KnobShift_3 = 5,
        KnobScale_4 = 6,
        KnobShift_4 = 7,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobScale_1,
            .x_mm = px_to_mm<72>(64.25f),
            .y_mm = px_to_mm<72>(46.64f),
            .short_name = "Scale 1",
            .long_name = "Scale 1",
            .default_val = 1.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobShift_1,
            .x_mm = px_to_mm<72>(107.45f),
            .y_mm = px_to_mm<72>(46.64f),
            .short_name = "Shift 1",
            .long_name = "Shift 1",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobScale_2,
            .x_mm = px_to_mm<72>(64.25f),
            .y_mm = px_to_mm<72>(111.44f),
            .short_name = "Scale 2",
            .long_name = "Scale 2",
            .default_val = 1.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobShift_2,
            .x_mm = px_to_mm<72>(107.45f),
            .y_mm = px_to_mm<72>(111.44f),
            .short_name = "Shift 2",
            .long_name = "Shift 2",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobScale_3,
            .x_mm = px_to_mm<72>(64.25f),
            .y_mm = px_to_mm<72>(176.24f),
            .short_name = "Scale 3",
            .long_name = "Scale 3",
            .default_val = 1.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobShift_3,
            .x_mm = px_to_mm<72>(107.45f),
            .y_mm = px_to_mm<72>(176.24f),
            .short_name = "Shift 3",
            .long_name = "Shift 3",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobScale_4,
            .x_mm = px_to_mm<72>(64.25f),
            .y_mm = px_to_mm<72>(241.04f),
            .short_name = "Scale 4",
            .long_name = "Scale 4",
            .default_val = 1.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobShift_4,
            .x_mm = px_to_mm<72>(107.45f),
            .y_mm = px_to_mm<72>(241.04f),
            .short_name = "Shift 4",
            .long_name = "Shift 4",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 4;
    
    enum {
        InputIn_1 = 0,
        InputIn_2 = 1,
        InputIn_3 = 2,
        InputIn_4 = 3,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputIn_1,
            .x_mm = px_to_mm<72>(21.77f),
            .y_mm = px_to_mm<72>(52.84f),
            .short_name = "In 1",
            .long_name = "In 1",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_2,
            .x_mm = px_to_mm<72>(21.77f),
            .y_mm = px_to_mm<72>(117.64f),
            .short_name = "In 2",
            .long_name = "In 2",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_3,
            .x_mm = px_to_mm<72>(21.77f),
            .y_mm = px_to_mm<72>(182.44f),
            .short_name = "In 3",
            .long_name = "In 3",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_4,
            .x_mm = px_to_mm<72>(21.77f),
            .y_mm = px_to_mm<72>(247.24f),
            .short_name = "In 4",
            .long_name = "In 4",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 8;
    
    enum {
        OutputOut_1 = 0,
        OutputOut_2 = 1,
        OutputOut_3 = 2,
        OutputOut_4 = 3,
        OutputP_Slice = 4,
        OutputN_Slice = 5,
        OutputMix__Sw_ = 6,
        OutputMix = 7,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputOut_1,
            .x_mm = px_to_mm<72>(150.52f),
            .y_mm = px_to_mm<72>(52.9f),
            .short_name = "Out 1",
            .long_name = "Out 1",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_2,
            .x_mm = px_to_mm<72>(150.52f),
            .y_mm = px_to_mm<72>(117.7f),
            .short_name = "Out 2",
            .long_name = "Out 2",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_3,
            .x_mm = px_to_mm<72>(150.52f),
            .y_mm = px_to_mm<72>(182.5f),
            .short_name = "Out 3",
            .long_name = "Out 3",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_4,
            .x_mm = px_to_mm<72>(150.52f),
            .y_mm = px_to_mm<72>(247.3f),
            .short_name = "Out 4",
            .long_name = "Out 4",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputP_Slice,
            .x_mm = px_to_mm<72>(21.1f),
            .y_mm = px_to_mm<72>(312.16f),
            .short_name = "+ Slice",
            .long_name = "+ Slice",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputN_Slice,
            .x_mm = px_to_mm<72>(64.25f),
            .y_mm = px_to_mm<72>(312.16f),
            .short_name = "- Slice",
            .long_name = "- Slice",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputMix__Sw_,
            .x_mm = px_to_mm<72>(107.45f),
            .y_mm = px_to_mm<72>(312.16f),
            .short_name = "Mix (SW)",
            .long_name = "Mix (SW)",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputMix,
            .x_mm = px_to_mm<72>(150.7f),
            .y_mm = px_to_mm<72>(312.16f),
            .short_name = "Mix",
            .long_name = "Mix",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 0;
    

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
    }};

    static constexpr int NumDiscreteLeds = 14;
    
    enum {
        LedLed_N_1 = 0,
        LedLed_P_1 = 1,
        LedLed_N_2 = 2,
        LedLed_P_2 = 3,
        LedLed_N_3 = 4,
        LedLed_P_3 = 5,
        LedLed_N_4 = 6,
        LedLed_P_4 = 7,
        LedLed_P_Slice = 8,
        LedLed_N_Slice = 9,
        LedLed_N_Mix__Sw_ = 10,
        LedLed_P_Mix__Sw_ = 11,
        LedLed_N_Mix = 12,
        LedLed_P_Mix = 13,
    };

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
        {
            .id = LedLed_N_1,
            .x_mm = px_to_mm<72>(146.69f),
            .y_mm = px_to_mm<72>(29.5f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_P_1,
            .x_mm = px_to_mm<72>(158.21f),
            .y_mm = px_to_mm<72>(29.5f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_N_2,
            .x_mm = px_to_mm<72>(144.99f),
            .y_mm = px_to_mm<72>(93.58f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_P_2,
            .x_mm = px_to_mm<72>(156.5f),
            .y_mm = px_to_mm<72>(93.58f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_N_3,
            .x_mm = px_to_mm<72>(145.02f),
            .y_mm = px_to_mm<72>(158.45f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_P_3,
            .x_mm = px_to_mm<72>(156.54f),
            .y_mm = px_to_mm<72>(158.45f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_N_4,
            .x_mm = px_to_mm<72>(145.11f),
            .y_mm = px_to_mm<72>(223.33f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_P_4,
            .x_mm = px_to_mm<72>(156.63f),
            .y_mm = px_to_mm<72>(223.33f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_P_Slice,
            .x_mm = px_to_mm<72>(20.92f),
            .y_mm = px_to_mm<72>(289.03f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_N_Slice,
            .x_mm = px_to_mm<72>(64.26f),
            .y_mm = px_to_mm<72>(288.6f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_N_Mix__Sw_,
            .x_mm = px_to_mm<72>(102.32f),
            .y_mm = px_to_mm<72>(289.18f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_P_Mix__Sw_,
            .x_mm = px_to_mm<72>(113.66f),
            .y_mm = px_to_mm<72>(289.18f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_N_Mix,
            .x_mm = px_to_mm<72>(145.66f),
            .y_mm = px_to_mm<72>(289.03f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_P_Mix,
            .x_mm = px_to_mm<72>(157.0f),
            .y_mm = px_to_mm<72>(289.03f),
            .led_color = LedDef::Red,
        },
    }};

};
