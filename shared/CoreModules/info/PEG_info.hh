#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct PEGInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"PEG"};
    static constexpr std::string_view description{"Pingable Envelope Generator"};
    static constexpr uint32_t width_hp = 20;
    static constexpr std::string_view svg_filename{"res/modules/PEG-artwork.svg"};

    static constexpr int NumKnobs = 8;
    
    enum {
        KnobPing_Div_Mult_1 = 0,
        KnobPing_Div_Mult_2 = 1,
        KnobScale_1 = 2,
        KnobSkew_1 = 3,
        KnobSkew_2 = 4,
        KnobScale_2 = 5,
        KnobCurve_1 = 6,
        KnobCurve_2 = 7,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobPing_Div_Mult_1,
            .x_mm = px_to_mm<72>(34.2f),
            .y_mm = px_to_mm<72>(106.06f),
            .short_name = "Ping Div Mult 1",
            .long_name = "Ping Div Mult 1",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobPing_Div_Mult_2,
            .x_mm = px_to_mm<72>(254.32f),
            .y_mm = px_to_mm<72>(106.02f),
            .short_name = "Ping Div Mult 2",
            .long_name = "Ping Div Mult 2",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobScale_1,
            .x_mm = px_to_mm<72>(34.16f),
            .y_mm = px_to_mm<72>(170.68f),
            .short_name = "Scale 1",
            .long_name = "Scale 1",
            .default_val = 1.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobSkew_1,
            .x_mm = px_to_mm<72>(95.87f),
            .y_mm = px_to_mm<72>(151.47f),
            .short_name = "Skew 1",
            .long_name = "Skew 1",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobSkew_2,
            .x_mm = px_to_mm<72>(192.91f),
            .y_mm = px_to_mm<72>(151.47f),
            .short_name = "Skew 2",
            .long_name = "Skew 2",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobScale_2,
            .x_mm = px_to_mm<72>(254.75f),
            .y_mm = px_to_mm<72>(170.82f),
            .short_name = "Scale 2",
            .long_name = "Scale 2",
            .default_val = 1.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobCurve_1,
            .x_mm = px_to_mm<72>(106.67f),
            .y_mm = px_to_mm<72>(215.41f),
            .short_name = "Curve 1",
            .long_name = "Curve 1",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobCurve_2,
            .x_mm = px_to_mm<72>(182.51f),
            .y_mm = px_to_mm<72>(215.41f),
            .short_name = "Curve 2",
            .long_name = "Curve 2",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 13;
    
    enum {
        InputPing_1_Jack = 0,
        InputPing_2_Jack = 1,
        InputQnt_1 = 2,
        InputToggle = 3,
        InputQnt_2 = 4,
        InputAsync_1 = 5,
        InputAsync_2 = 6,
        InputDiv_1_Jack = 7,
        InputSkew_1_Jack = 8,
        InputCurve_1_Jack = 9,
        InputCurve_2_Jack = 10,
        InputSkew_2_Jack = 11,
        InputDiv_2_Jack = 12,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputPing_1_Jack,
            .x_mm = px_to_mm<72>(21.57f),
            .y_mm = px_to_mm<72>(45.55f),
            .short_name = "Ping 1 Jack",
            .long_name = "Ping 1 Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputPing_2_Jack,
            .x_mm = px_to_mm<72>(267.05f),
            .y_mm = px_to_mm<72>(45.55f),
            .short_name = "Ping 2 Jack",
            .long_name = "Ping 2 Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputQnt_1,
            .x_mm = px_to_mm<72>(97.57f),
            .y_mm = px_to_mm<72>(74.03f),
            .short_name = "Qnt 1",
            .long_name = "Qnt 1",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputToggle,
            .x_mm = px_to_mm<72>(144.31f),
            .y_mm = px_to_mm<72>(74.03f),
            .short_name = "Toggle",
            .long_name = "Toggle",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputQnt_2,
            .x_mm = px_to_mm<72>(190.86f),
            .y_mm = px_to_mm<72>(74.03f),
            .short_name = "Qnt 2",
            .long_name = "Qnt 2",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputAsync_1,
            .x_mm = px_to_mm<72>(120.8f),
            .y_mm = px_to_mm<72>(107.7f),
            .short_name = "Async 1",
            .long_name = "Async 1",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputAsync_2,
            .x_mm = px_to_mm<72>(167.56f),
            .y_mm = px_to_mm<72>(107.7f),
            .short_name = "Async 2",
            .long_name = "Async 2",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputDiv_1_Jack,
            .x_mm = px_to_mm<72>(27.7f),
            .y_mm = px_to_mm<72>(317.08f),
            .short_name = "Div 1 Jack",
            .long_name = "Div 1 Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSkew_1_Jack,
            .x_mm = px_to_mm<72>(69.36f),
            .y_mm = px_to_mm<72>(317.08f),
            .short_name = "Skew 1 Jack",
            .long_name = "Skew 1 Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputCurve_1_Jack,
            .x_mm = px_to_mm<72>(111.11f),
            .y_mm = px_to_mm<72>(317.08f),
            .short_name = "Curve 1 Jack",
            .long_name = "Curve 1 Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputCurve_2_Jack,
            .x_mm = px_to_mm<72>(177.5f),
            .y_mm = px_to_mm<72>(317.08f),
            .short_name = "Curve 2 Jack",
            .long_name = "Curve 2 Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSkew_2_Jack,
            .x_mm = px_to_mm<72>(219.06f),
            .y_mm = px_to_mm<72>(317.08f),
            .short_name = "Skew 2 Jack",
            .long_name = "Skew 2 Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputDiv_2_Jack,
            .x_mm = px_to_mm<72>(260.81f),
            .y_mm = px_to_mm<72>(317.08f),
            .short_name = "Div 2 Jack",
            .long_name = "Div 2 Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 9;
    
    enum {
        OutputEnv_1 = 0,
        OutputEnv_2 = 1,
        OutputP5V_Env_1 = 2,
        OutputEor = 3,
        OutputEof_1 = 4,
        OutputOr = 5,
        OutputEof_2 = 6,
        OutputHalf_R = 7,
        OutputP5V_Env_2 = 8,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputEnv_1,
            .x_mm = px_to_mm<72>(48.56f),
            .y_mm = px_to_mm<72>(248.86f),
            .short_name = "Env 1",
            .long_name = "Env 1",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputEnv_2,
            .x_mm = px_to_mm<72>(239.76f),
            .y_mm = px_to_mm<72>(248.86f),
            .short_name = "Env 2",
            .long_name = "Env 2",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputP5V_Env_1,
            .x_mm = px_to_mm<72>(27.7f),
            .y_mm = px_to_mm<72>(281.13f),
            .short_name = "+5V Env 1",
            .long_name = "+5V Env 1",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputEor,
            .x_mm = px_to_mm<72>(69.36f),
            .y_mm = px_to_mm<72>(281.13f),
            .short_name = "EOR",
            .long_name = "EOR",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputEof_1,
            .x_mm = px_to_mm<72>(111.11f),
            .y_mm = px_to_mm<72>(281.13f),
            .short_name = "EOF 1",
            .long_name = "EOF 1",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOr,
            .x_mm = px_to_mm<72>(144.22f),
            .y_mm = px_to_mm<72>(299.87f),
            .short_name = "OR",
            .long_name = "OR",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputEof_2,
            .x_mm = px_to_mm<72>(177.5f),
            .y_mm = px_to_mm<72>(281.13f),
            .short_name = "EOF 2",
            .long_name = "EOF 2",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputHalf_R,
            .x_mm = px_to_mm<72>(219.06f),
            .y_mm = px_to_mm<72>(280.99f),
            .short_name = "Half R",
            .long_name = "Half R",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputP5V_Env_2,
            .x_mm = px_to_mm<72>(260.81f),
            .y_mm = px_to_mm<72>(280.99f),
            .short_name = "+5V Env 2",
            .long_name = "+5V Env 2",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 6;
    
    enum {
        SwitchPing_1 = 0,
        SwitchCycle_1 = 1,
        SwitchCycle_2 = 2,
        SwitchPing_2 = 3,
        SwitchBiNPolar_1 = 4,
        SwitchBiNPolar_2 = 5,
    };

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
        {
            .id = SwitchPing_1,
            .x_mm = px_to_mm<72>(68.06f),
            .y_mm = px_to_mm<72>(45.56f),
            .short_name = "Ping 1",
            .long_name = "Ping 1",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchCycle_1,
            .x_mm = px_to_mm<72>(120.9f),
            .y_mm = px_to_mm<72>(41.96f),
            .short_name = "Cycle 1",
            .long_name = "Cycle 1",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchCycle_2,
            .x_mm = px_to_mm<72>(167.48f),
            .y_mm = px_to_mm<72>(41.9f),
            .short_name = "Cycle 2",
            .long_name = "Cycle 2",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchPing_2,
            .x_mm = px_to_mm<72>(220.56f),
            .y_mm = px_to_mm<72>(45.56f),
            .short_name = "Ping 2",
            .long_name = "Ping 2",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchBiNPolar_1,
            .x_mm = px_to_mm<72>(21.56f),
            .y_mm = px_to_mm<72>(213.99f),
            .short_name = "Bi-polar 1",
            .long_name = "Bi-polar 1",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchBiNPolar_2,
            .x_mm = px_to_mm<72>(267.04f),
            .y_mm = px_to_mm<72>(213.99f),
            .short_name = "Bi-polar 2",
            .long_name = "Bi-polar 2",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
    }};

    static constexpr int NumDiscreteLeds = 6;
    
    enum {
        LedEnv_Led_1 = 0,
        LedEnv_Led_2 = 1,
        LedEor_Led_1 = 2,
        LedEof_Led_1 = 3,
        LedEof_Led_2 = 4,
        LedHalf_R = 5,
    };

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
        {
            .id = LedEnv_Led_1,
            .x_mm = px_to_mm<72>(47.9f),
            .y_mm = px_to_mm<72>(213.99f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedEnv_Led_2,
            .x_mm = px_to_mm<72>(239.76f),
            .y_mm = px_to_mm<72>(213.99f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedEor_Led_1,
            .x_mm = px_to_mm<72>(73.01f),
            .y_mm = px_to_mm<72>(258.36f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedEof_Led_1,
            .x_mm = px_to_mm<72>(111.11f),
            .y_mm = px_to_mm<72>(258.36f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedEof_Led_2,
            .x_mm = px_to_mm<72>(177.5f),
            .y_mm = px_to_mm<72>(258.36f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedHalf_R,
            .x_mm = px_to_mm<72>(215.46f),
            .y_mm = px_to_mm<72>(258.36f),
            .led_color = LedDef::Red,
        },
    }};

};
