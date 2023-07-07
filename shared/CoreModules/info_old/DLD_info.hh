#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct DLDInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"DLD"};
    static constexpr std::string_view description{"Dual Looping Delay"};
    static constexpr uint32_t width_hp = 20;
    static constexpr std::string_view svg_filename{"res/modules/DLD-artwork.svg"};

    static constexpr int NumKnobs = 8;
    
    enum {
        KnobTime_A = 0,
        KnobTime_B = 1,
        KnobFeedback_A = 2,
        KnobFeedback_B = 3,
        KnobDelay_Feed_A = 4,
        KnobMix_A = 5,
        KnobMix_B = 6,
        KnobDelay_Feed_B = 7,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobTime_A,
            .x_mm = px_to_mm<72>(34.32f),
            .y_mm = px_to_mm<72>(53.53f),
            .short_name = "Time A",
            .long_name = "Time A",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobTime_B,
            .x_mm = px_to_mm<72>(254.17f),
            .y_mm = px_to_mm<72>(53.39f),
            .short_name = "Time B",
            .long_name = "Time B",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobFeedback_A,
            .x_mm = px_to_mm<72>(34.17f),
            .y_mm = px_to_mm<72>(119.05f),
            .short_name = "Feedback A",
            .long_name = "Feedback A",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobFeedback_B,
            .x_mm = px_to_mm<72>(254.59f),
            .y_mm = px_to_mm<72>(119.05f),
            .short_name = "Feedback B",
            .long_name = "Feedback B",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobDelay_Feed_A,
            .x_mm = px_to_mm<72>(43.46f),
            .y_mm = px_to_mm<72>(184.04f),
            .short_name = "Delay Feed A",
            .long_name = "Delay Feed A",
            .default_val = 1.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobMix_A,
            .x_mm = px_to_mm<72>(111.56f),
            .y_mm = px_to_mm<72>(178.84f),
            .short_name = "Mix A",
            .long_name = "Mix A",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobMix_B,
            .x_mm = px_to_mm<72>(177.02f),
            .y_mm = px_to_mm<72>(178.91f),
            .short_name = "Mix B",
            .long_name = "Mix B",
            .default_val = 0.875f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobDelay_Feed_B,
            .x_mm = px_to_mm<72>(245.19f),
            .y_mm = px_to_mm<72>(183.78f),
            .short_name = "Delay Feed B",
            .long_name = "Delay Feed B",
            .default_val = 1.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 15;
    
    enum {
        InputPing_Jack = 0,
        InputIn_A = 1,
        InputReturn_A = 2,
        InputReverse_A_Jack = 3,
        InputReverse_B_Jack = 4,
        InputReturn_B = 5,
        InputIn_B = 6,
        InputHold_A_Jack = 7,
        InputHold_B_Jack = 8,
        InputTime_A_Jack = 9,
        InputFeedback_A_Jack = 10,
        InputDelay_Feed_A_Jack = 11,
        InputDelay_Feed_B_Jack = 12,
        InputFeedback_B_Jack = 13,
        InputTime_B_Jack = 14,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputPing_Jack,
            .x_mm = px_to_mm<72>(167.59f),
            .y_mm = px_to_mm<72>(42.51f),
            .short_name = "Ping Jack",
            .long_name = "Ping Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_A,
            .x_mm = px_to_mm<72>(28.08f),
            .y_mm = px_to_mm<72>(242.1f),
            .short_name = "In A",
            .long_name = "In A",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputReturn_A,
            .x_mm = px_to_mm<72>(71.16f),
            .y_mm = px_to_mm<72>(242.1f),
            .short_name = "Return A",
            .long_name = "Return A",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputReverse_A_Jack,
            .x_mm = px_to_mm<72>(122.51f),
            .y_mm = px_to_mm<72>(242.1f),
            .short_name = "Reverse A Jack",
            .long_name = "Reverse A Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputReverse_B_Jack,
            .x_mm = px_to_mm<72>(165.98f),
            .y_mm = px_to_mm<72>(242.1f),
            .short_name = "Reverse B Jack",
            .long_name = "Reverse B Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputReturn_B,
            .x_mm = px_to_mm<72>(217.15f),
            .y_mm = px_to_mm<72>(242.1f),
            .short_name = "Return B",
            .long_name = "Return B",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn_B,
            .x_mm = px_to_mm<72>(260.18f),
            .y_mm = px_to_mm<72>(242.1f),
            .short_name = "In B",
            .long_name = "In B",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputHold_A_Jack,
            .x_mm = px_to_mm<72>(122.51f),
            .y_mm = px_to_mm<72>(281.49f),
            .short_name = "Hold A Jack",
            .long_name = "Hold A Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputHold_B_Jack,
            .x_mm = px_to_mm<72>(165.98f),
            .y_mm = px_to_mm<72>(281.49f),
            .short_name = "Hold B Jack",
            .long_name = "Hold B Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputTime_A_Jack,
            .x_mm = px_to_mm<72>(25.58f),
            .y_mm = px_to_mm<72>(322.03f),
            .short_name = "Time A Jack",
            .long_name = "Time A Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputFeedback_A_Jack,
            .x_mm = px_to_mm<72>(72.88f),
            .y_mm = px_to_mm<72>(322.03f),
            .short_name = "Feedback A Jack",
            .long_name = "Feedback A Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputDelay_Feed_A_Jack,
            .x_mm = px_to_mm<72>(120.17f),
            .y_mm = px_to_mm<72>(322.03f),
            .short_name = "Delay Feed A Jack",
            .long_name = "Delay Feed A Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputDelay_Feed_B_Jack,
            .x_mm = px_to_mm<72>(167.84f),
            .y_mm = px_to_mm<72>(322.03f),
            .short_name = "Delay Feed B Jack",
            .long_name = "Delay Feed B Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputFeedback_B_Jack,
            .x_mm = px_to_mm<72>(215.27f),
            .y_mm = px_to_mm<72>(322.03f),
            .short_name = "Feedback B Jack",
            .long_name = "Feedback B Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputTime_B_Jack,
            .x_mm = px_to_mm<72>(262.73f),
            .y_mm = px_to_mm<72>(322.03f),
            .short_name = "Time B Jack",
            .long_name = "Time B Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 7;
    
    enum {
        OutputLoop_A = 0,
        OutputClock_Out = 1,
        OutputLoop_B = 2,
        OutputOut_A = 3,
        OutputSend_A = 4,
        OutputSend_B = 5,
        OutputOut_B = 6,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputLoop_A,
            .x_mm = px_to_mm<72>(108.25f),
            .y_mm = px_to_mm<72>(81.44f),
            .short_name = "Loop A",
            .long_name = "Loop A",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputClock_Out,
            .x_mm = px_to_mm<72>(144.16f),
            .y_mm = px_to_mm<72>(93.48f),
            .short_name = "Clock Out",
            .long_name = "Clock Out",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputLoop_B,
            .x_mm = px_to_mm<72>(180.38f),
            .y_mm = px_to_mm<72>(81.44f),
            .short_name = "Loop B",
            .long_name = "Loop B",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_A,
            .x_mm = px_to_mm<72>(28.08f),
            .y_mm = px_to_mm<72>(281.49f),
            .short_name = "Out A",
            .long_name = "Out A",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputSend_A,
            .x_mm = px_to_mm<72>(71.16f),
            .y_mm = px_to_mm<72>(281.49f),
            .short_name = "Send A",
            .long_name = "Send A",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputSend_B,
            .x_mm = px_to_mm<72>(217.15f),
            .y_mm = px_to_mm<72>(281.49f),
            .short_name = "Send B",
            .long_name = "Send B",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_B,
            .x_mm = px_to_mm<72>(260.18f),
            .y_mm = px_to_mm<72>(281.49f),
            .short_name = "Out B",
            .long_name = "Out B",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 7;
    
    enum {
        SwitchP16__OR__1_8Th_A = 0,
        SwitchP16__OR__1_8Th_B = 1,
        SwitchPing_Button = 2,
        SwitchReverse_A = 3,
        SwitchHold_A = 4,
        SwitchHold_B = 5,
        SwitchReverse_B = 6,
    };

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
        {
            .id = SwitchP16__OR__1_8Th_A,
            .x_mm = px_to_mm<72>(84.11f),
            .y_mm = px_to_mm<72>(51.455f),
            .short_name = "+16 | 1/8th A",
            .long_name = "+16 | 1/8th A",
            .switch_type = SwitchDef::Toggle3pos,
            .orientation = SwitchDef::Vertical,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchP16__OR__1_8Th_B,
            .x_mm = px_to_mm<72>(205.35f),
            .y_mm = px_to_mm<72>(51.455f),
            .short_name = "+16 | 1/8th B",
            .long_name = "+16 | 1/8th B",
            .switch_type = SwitchDef::Toggle3pos,
            .orientation = SwitchDef::Vertical,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchPing_Button,
            .x_mm = px_to_mm<72>(124.03f),
            .y_mm = px_to_mm<72>(42.51f),
            .short_name = "Ping Button",
            .long_name = "Ping Button",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchReverse_A,
            .x_mm = px_to_mm<72>(81.85f),
            .y_mm = px_to_mm<72>(123.11f),
            .short_name = "Reverse A",
            .long_name = "Reverse A",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchHold_A,
            .x_mm = px_to_mm<72>(118.44f),
            .y_mm = px_to_mm<72>(135.74f),
            .short_name = "Hold A",
            .long_name = "Hold A",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchHold_B,
            .x_mm = px_to_mm<72>(169.66f),
            .y_mm = px_to_mm<72>(135.74f),
            .short_name = "Hold B",
            .long_name = "Hold B",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchReverse_B,
            .x_mm = px_to_mm<72>(206.08f),
            .y_mm = px_to_mm<72>(123.11f),
            .short_name = "Reverse B",
            .long_name = "Reverse B",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
    }};

    static constexpr int NumDiscreteLeds = 2;
    
    enum {
        LedTime_A_Led = 0,
        LedTime_B_Led = 1,
    };

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
        {
            .id = LedTime_A_Led,
            .x_mm = px_to_mm<72>(66.03f),
            .y_mm = px_to_mm<72>(34.94f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedTime_B_Led,
            .x_mm = px_to_mm<72>(222.2f),
            .y_mm = px_to_mm<72>(34.94f),
            .led_color = LedDef::Red,
        },
    }};

};
