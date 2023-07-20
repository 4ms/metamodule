#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct SCMInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"SCM"};
    static constexpr std::string_view description{"Shuffling Clock Multiplier"};
    static constexpr uint32_t width_hp = 12;
    static constexpr std::string_view svg_filename{"res/modules/SCM-artwork.svg"};

    static constexpr int NumKnobs = 5;
    
    enum {
        KnobRotate = 0,
        KnobSlip = 1,
        KnobShuffle = 2,
        KnobSkip = 3,
        KnobPw = 4,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobRotate,
            .x_mm = px_to_mm<72>(147.99f),
            .y_mm = px_to_mm<72>(54.12f),
            .short_name = "Rotate",
            .long_name = "Rotate",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobSlip,
            .x_mm = px_to_mm<72>(147.99f),
            .y_mm = px_to_mm<72>(104.09f),
            .short_name = "Slip",
            .long_name = "Slip",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobShuffle,
            .x_mm = px_to_mm<72>(147.99f),
            .y_mm = px_to_mm<72>(154.07f),
            .short_name = "Shuffle",
            .long_name = "Shuffle",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobSkip,
            .x_mm = px_to_mm<72>(147.99f),
            .y_mm = px_to_mm<72>(204.04f),
            .short_name = "Skip",
            .long_name = "Skip",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobPw,
            .x_mm = px_to_mm<72>(147.99f),
            .y_mm = px_to_mm<72>(254.01f),
            .short_name = "PW",
            .long_name = "PW",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 9;
    
    enum {
        InputClk_In = 0,
        InputResync = 1,
        InputRotate_Jack = 2,
        InputSlip_Jack = 3,
        InputShuffle_Jack = 4,
        InputSkip_Jack = 5,
        InputPw_Jack = 6,
        Input_4X_Fast_Jack = 7,
        InputMute_Jack = 8,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputClk_In,
            .x_mm = px_to_mm<72>(46.48f),
            .y_mm = px_to_mm<72>(56.3f),
            .short_name = "Clk In",
            .long_name = "Clk In",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputResync,
            .x_mm = px_to_mm<72>(81.45f),
            .y_mm = px_to_mm<72>(55.11f),
            .short_name = "Resync",
            .long_name = "Resync",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputRotate_Jack,
            .x_mm = px_to_mm<72>(81.45f),
            .y_mm = px_to_mm<72>(90.12f),
            .short_name = "Rotate Jack",
            .long_name = "Rotate Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSlip_Jack,
            .x_mm = px_to_mm<72>(81.45f),
            .y_mm = px_to_mm<72>(126.12f),
            .short_name = "Slip Jack",
            .long_name = "Slip Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputShuffle_Jack,
            .x_mm = px_to_mm<72>(81.45f),
            .y_mm = px_to_mm<72>(162.12f),
            .short_name = "Shuffle Jack",
            .long_name = "Shuffle Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSkip_Jack,
            .x_mm = px_to_mm<72>(81.45f),
            .y_mm = px_to_mm<72>(198.12f),
            .short_name = "Skip Jack",
            .long_name = "Skip Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputPw_Jack,
            .x_mm = px_to_mm<72>(81.45f),
            .y_mm = px_to_mm<72>(234.12f),
            .short_name = "PW Jack",
            .long_name = "PW Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = Input_4X_Fast_Jack,
            .x_mm = px_to_mm<72>(81.45f),
            .y_mm = px_to_mm<72>(270.12f),
            .short_name = "4x Fast Jack",
            .long_name = "4x Fast Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputMute_Jack,
            .x_mm = px_to_mm<72>(81.45f),
            .y_mm = px_to_mm<72>(306.12f),
            .short_name = "Mute Jack",
            .long_name = "Mute Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 8;
    
    enum {
        OutputX1 = 0,
        OutputX2 = 1,
        OutputS3 = 2,
        OutputS4 = 3,
        OutputS5 = 4,
        OutputS6 = 5,
        OutputS8 = 6,
        OutputX8 = 7,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputX1,
            .x_mm = px_to_mm<72>(46.48f),
            .y_mm = px_to_mm<72>(87.91f),
            .short_name = "x1",
            .long_name = "x1",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputX2,
            .x_mm = px_to_mm<72>(46.48f),
            .y_mm = px_to_mm<72>(119.52f),
            .short_name = "x2",
            .long_name = "x2",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputS3,
            .x_mm = px_to_mm<72>(46.48f),
            .y_mm = px_to_mm<72>(151.13f),
            .short_name = "S3",
            .long_name = "S3",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputS4,
            .x_mm = px_to_mm<72>(46.48f),
            .y_mm = px_to_mm<72>(182.73f),
            .short_name = "S4",
            .long_name = "S4",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputS5,
            .x_mm = px_to_mm<72>(46.48f),
            .y_mm = px_to_mm<72>(214.34f),
            .short_name = "S5",
            .long_name = "S5",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputS6,
            .x_mm = px_to_mm<72>(46.48f),
            .y_mm = px_to_mm<72>(245.95f),
            .short_name = "S6",
            .long_name = "S6",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputS8,
            .x_mm = px_to_mm<72>(46.48f),
            .y_mm = px_to_mm<72>(277.56f),
            .short_name = "S8",
            .long_name = "S8",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputX8,
            .x_mm = px_to_mm<72>(46.48f),
            .y_mm = px_to_mm<72>(309.17f),
            .short_name = "x8",
            .long_name = "x8",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 2;
    
    enum {
        Switch_4X_Fast = 0,
        SwitchMute = 1,
    };

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
        {
            .id = Switch_4X_Fast,
            .x_mm = px_to_mm<72>(148.84f),
            .y_mm = px_to_mm<72>(291.85f),
            .short_name = "4x Fast",
            .long_name = "4x Fast",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchMute,
            .x_mm = px_to_mm<72>(148.84f),
            .y_mm = px_to_mm<72>(325.47f),
            .short_name = "Mute",
            .long_name = "Mute",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
    }};

    static constexpr int NumDiscreteLeds = 9;
    
    enum {
        LedLed_In = 0,
        LedLed_X1 = 1,
        LedLed_X2 = 2,
        LedLed_S3 = 3,
        LedLed_S4 = 4,
        LedLed_S5 = 5,
        LedLed_S6 = 6,
        LedLed_S8 = 7,
        LedLed_X8 = 8,
    };

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
        {
            .id = LedLed_In,
            .x_mm = px_to_mm<72>(17.3f),
            .y_mm = px_to_mm<72>(56.3f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_X1,
            .x_mm = px_to_mm<72>(17.3f),
            .y_mm = px_to_mm<72>(87.91f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_X2,
            .x_mm = px_to_mm<72>(17.3f),
            .y_mm = px_to_mm<72>(119.52f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_S3,
            .x_mm = px_to_mm<72>(17.3f),
            .y_mm = px_to_mm<72>(151.13f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_S4,
            .x_mm = px_to_mm<72>(17.3f),
            .y_mm = px_to_mm<72>(182.73f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_S5,
            .x_mm = px_to_mm<72>(17.3f),
            .y_mm = px_to_mm<72>(214.34f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_S6,
            .x_mm = px_to_mm<72>(17.3f),
            .y_mm = px_to_mm<72>(245.95f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_S8,
            .x_mm = px_to_mm<72>(17.3f),
            .y_mm = px_to_mm<72>(277.56f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_X8,
            .x_mm = px_to_mm<72>(17.3f),
            .y_mm = px_to_mm<72>(309.17f),
            .led_color = LedDef::Red,
        },
    }};

};
