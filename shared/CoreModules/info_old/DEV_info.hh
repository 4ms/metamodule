#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct DEVInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"DEV"};
    static constexpr std::string_view description{"Dual EnvVCA"};
    static constexpr uint32_t width_hp = 16;
    static constexpr std::string_view svg_filename{"res/modules/DEV-artwork.svg"};

    static constexpr int NumKnobs = 12;
    
    enum {
        KnobRise_A_Slider = 0,
        KnobFall_A_Slider = 1,
        KnobRise_B_Slider = 2,
        KnobFall_B_Slider = 3,
        KnobLevel_A = 4,
        KnobLevel_B = 5,
        KnobOffset_A = 6,
        KnobOffset_B = 7,
        KnobRise_A = 8,
        KnobFall_A = 9,
        KnobRise_B = 10,
        KnobFall_B = 11,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobRise_A_Slider,
            .x_mm = px_to_mm<72>(22.415f),
            .y_mm = px_to_mm<72>(108.25f),
            .short_name = "Rise A Slider",
            .long_name = "Rise A Slider",
            .default_val = 0.5f,
            .knob_style = KnobDef::Slider25mm,
            .orientation = KnobDef::Vertical,
        },
        {
            .id = KnobFall_A_Slider,
            .x_mm = px_to_mm<72>(56.265f),
            .y_mm = px_to_mm<72>(108.25f),
            .short_name = "Fall A Slider",
            .long_name = "Fall A Slider",
            .default_val = 0.5f,
            .knob_style = KnobDef::Slider25mm,
            .orientation = KnobDef::Vertical,
        },
        {
            .id = KnobRise_B_Slider,
            .x_mm = px_to_mm<72>(174.115f),
            .y_mm = px_to_mm<72>(108.25f),
            .short_name = "Rise B Slider",
            .long_name = "Rise B Slider",
            .default_val = 0.5f,
            .knob_style = KnobDef::Slider25mm,
            .orientation = KnobDef::Vertical,
        },
        {
            .id = KnobFall_B_Slider,
            .x_mm = px_to_mm<72>(207.965f),
            .y_mm = px_to_mm<72>(108.25f),
            .short_name = "Fall B Slider",
            .long_name = "Fall B Slider",
            .default_val = 0.5f,
            .knob_style = KnobDef::Slider25mm,
            .orientation = KnobDef::Vertical,
        },
        {
            .id = KnobLevel_A,
            .x_mm = px_to_mm<72>(93.13f),
            .y_mm = px_to_mm<72>(95.86f),
            .short_name = "Level A",
            .long_name = "Level A",
            .default_val = 1.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLevel_B,
            .x_mm = px_to_mm<72>(137.25f),
            .y_mm = px_to_mm<72>(95.86f),
            .short_name = "Level B",
            .long_name = "Level B",
            .default_val = 1.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobOffset_A,
            .x_mm = px_to_mm<72>(93.13f),
            .y_mm = px_to_mm<72>(138.65f),
            .short_name = "Offset A",
            .long_name = "Offset A",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobOffset_B,
            .x_mm = px_to_mm<72>(137.25f),
            .y_mm = px_to_mm<72>(138.65f),
            .short_name = "Offset B",
            .long_name = "Offset B",
            .default_val = 0.5f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobRise_A,
            .x_mm = px_to_mm<72>(23.5f),
            .y_mm = px_to_mm<72>(184.03f),
            .short_name = "Rise A",
            .long_name = "Rise A",
            .default_val = 1.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobFall_A,
            .x_mm = px_to_mm<72>(94.11f),
            .y_mm = px_to_mm<72>(183.67f),
            .short_name = "Fall A",
            .long_name = "Fall A",
            .default_val = 1.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobRise_B,
            .x_mm = px_to_mm<72>(136.27f),
            .y_mm = px_to_mm<72>(184.03f),
            .short_name = "Rise B",
            .long_name = "Rise B",
            .default_val = 1.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobFall_B,
            .x_mm = px_to_mm<72>(206.87f),
            .y_mm = px_to_mm<72>(184.03f),
            .short_name = "Fall B",
            .long_name = "Fall B",
            .default_val = 1.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 11;
    
    enum {
        InputCycle_Trig_ = 0,
        InputTime_Cv_A = 1,
        InputTime_Cv_B = 2,
        InputTrig_A = 3,
        InputFollow_A = 4,
        InputFollow_B = 5,
        InputTrig_B = 6,
        InputAudio_A_In = 7,
        InputVca_Cv_A = 8,
        InputVca_Cv_B = 9,
        InputAudio_B_In = 10,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputCycle_Trig_,
            .x_mm = px_to_mm<72>(115.19f),
            .y_mm = px_to_mm<72>(60.85f),
            .short_name = "Cycle Trig?",
            .long_name = "Cycle Trig?",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputTime_Cv_A,
            .x_mm = px_to_mm<72>(58.56f),
            .y_mm = px_to_mm<72>(208.68f),
            .short_name = "Time CV A",
            .long_name = "Time CV A",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputTime_Cv_B,
            .x_mm = px_to_mm<72>(171.86f),
            .y_mm = px_to_mm<72>(208.68f),
            .short_name = "Time CV B",
            .long_name = "Time CV B",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputTrig_A,
            .x_mm = px_to_mm<72>(23.09f),
            .y_mm = px_to_mm<72>(232.82f),
            .short_name = "Trig A",
            .long_name = "Trig A",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputFollow_A,
            .x_mm = px_to_mm<72>(58.52f),
            .y_mm = px_to_mm<72>(252.75f),
            .short_name = "Follow A",
            .long_name = "Follow A",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputFollow_B,
            .x_mm = px_to_mm<72>(171.85f),
            .y_mm = px_to_mm<72>(252.75f),
            .short_name = "Follow B",
            .long_name = "Follow B",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputTrig_B,
            .x_mm = px_to_mm<72>(207.29f),
            .y_mm = px_to_mm<72>(232.82f),
            .short_name = "Trig B",
            .long_name = "Trig B",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputAudio_A_In,
            .x_mm = px_to_mm<72>(23.06f),
            .y_mm = px_to_mm<72>(274.73f),
            .short_name = "Audio A In",
            .long_name = "Audio A In",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputVca_Cv_A,
            .x_mm = px_to_mm<72>(58.48f),
            .y_mm = px_to_mm<72>(300.48f),
            .short_name = "VCA CV A",
            .long_name = "VCA CV A",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputVca_Cv_B,
            .x_mm = px_to_mm<72>(171.9f),
            .y_mm = px_to_mm<72>(300.41f),
            .short_name = "VCA CV B",
            .long_name = "VCA CV B",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputAudio_B_In,
            .x_mm = px_to_mm<72>(207.29f),
            .y_mm = px_to_mm<72>(274.76f),
            .short_name = "Audio B In",
            .long_name = "Audio B In",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 7;
    
    enum {
        OutputEor_A = 0,
        OutputEof_B = 1,
        OutputOr = 2,
        OutputAudio_A_Out = 3,
        OutputEnv_A_Out = 4,
        OutputEnv_B_Out = 5,
        OutputAudio_B_Out = 6,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputEor_A,
            .x_mm = px_to_mm<72>(95.04f),
            .y_mm = px_to_mm<72>(233.88f),
            .short_name = "EOR A",
            .long_name = "EOR A",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputEof_B,
            .x_mm = px_to_mm<72>(135.28f),
            .y_mm = px_to_mm<72>(233.99f),
            .short_name = "EOF B",
            .long_name = "EOF B",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOr,
            .x_mm = px_to_mm<72>(115.22f),
            .y_mm = px_to_mm<72>(288.78f),
            .short_name = "OR",
            .long_name = "OR",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputAudio_A_Out,
            .x_mm = px_to_mm<72>(23.06f),
            .y_mm = px_to_mm<72>(324.82f),
            .short_name = "Audio A Out",
            .long_name = "Audio A Out",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputEnv_A_Out,
            .x_mm = px_to_mm<72>(90.49f),
            .y_mm = px_to_mm<72>(324.82f),
            .short_name = "Env A Out",
            .long_name = "Env A Out",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputEnv_B_Out,
            .x_mm = px_to_mm<72>(139.91f),
            .y_mm = px_to_mm<72>(324.88f),
            .short_name = "Env B Out",
            .long_name = "Env B Out",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputAudio_B_Out,
            .x_mm = px_to_mm<72>(207.32f),
            .y_mm = px_to_mm<72>(324.82f),
            .short_name = "Audio B Out",
            .long_name = "Audio B Out",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 6;
    
    enum {
        SwitchSlow_Med_Fast_Rise_A = 0,
        SwitchSlow_Med_Fast_Fall_A = 1,
        SwitchSlow_Med_Fast_Rise_B = 2,
        SwitchSlow_Med_Fast_Fall_B = 3,
        SwitchCycle_A = 4,
        SwitchCycle_B = 5,
    };

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
        {
            .id = SwitchSlow_Med_Fast_Rise_A,
            .x_mm = px_to_mm<72>(17.6f),
            .y_mm = px_to_mm<72>(41.905f),
            .short_name = "Slow Med Fast Rise A",
            .long_name = "Slow Med Fast Rise A",
            .switch_type = SwitchDef::Toggle3pos,
            .orientation = SwitchDef::Vertical,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchSlow_Med_Fast_Fall_A,
            .x_mm = px_to_mm<72>(50.49f),
            .y_mm = px_to_mm<72>(41.905f),
            .short_name = "Slow Med Fast Fall A",
            .long_name = "Slow Med Fast Fall A",
            .switch_type = SwitchDef::Toggle3pos,
            .orientation = SwitchDef::Vertical,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchSlow_Med_Fast_Rise_B,
            .x_mm = px_to_mm<72>(179.89f),
            .y_mm = px_to_mm<72>(41.905f),
            .short_name = "Slow Med Fast Rise B",
            .long_name = "Slow Med Fast Rise B",
            .switch_type = SwitchDef::Toggle3pos,
            .orientation = SwitchDef::Vertical,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchSlow_Med_Fast_Fall_B,
            .x_mm = px_to_mm<72>(212.77f),
            .y_mm = px_to_mm<72>(41.905f),
            .short_name = "Slow Med Fast Fall B",
            .long_name = "Slow Med Fast Fall B",
            .switch_type = SwitchDef::Toggle3pos,
            .orientation = SwitchDef::Vertical,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchCycle_A,
            .x_mm = px_to_mm<72>(82.8f),
            .y_mm = px_to_mm<72>(41.64f),
            .short_name = "Cycle A",
            .long_name = "Cycle A",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchCycle_B,
            .x_mm = px_to_mm<72>(147.61f),
            .y_mm = px_to_mm<72>(41.68f),
            .short_name = "Cycle B",
            .long_name = "Cycle B",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
    }};

    static constexpr int NumDiscreteLeds = 8;
    
    enum {
        LedRise_Led_A = 0,
        LedFall_Led_A = 1,
        LedRise_Led_B = 2,
        LedFall_Led_B = 3,
        LedEor_Led = 4,
        LedEof_Led = 5,
        LedEnv_A_Led = 6,
        LedEnv_B_Led = 7,
    };

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
        {
            .id = LedRise_Led_A,
            .x_mm = px_to_mm<72>(45.84f),
            .y_mm = px_to_mm<72>(176.26f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedFall_Led_A,
            .x_mm = px_to_mm<72>(70.54f),
            .y_mm = px_to_mm<72>(176.26f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedRise_Led_B,
            .x_mm = px_to_mm<72>(159.84f),
            .y_mm = px_to_mm<72>(176.26f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedFall_Led_B,
            .x_mm = px_to_mm<72>(184.53f),
            .y_mm = px_to_mm<72>(176.26f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedEor_Led,
            .x_mm = px_to_mm<72>(99.58f),
            .y_mm = px_to_mm<72>(260.79f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedEof_Led,
            .x_mm = px_to_mm<72>(130.68f),
            .y_mm = px_to_mm<72>(261.07f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedEnv_A_Led,
            .x_mm = px_to_mm<72>(65.92f),
            .y_mm = px_to_mm<72>(327.45f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedEnv_B_Led,
            .x_mm = px_to_mm<72>(164.39f),
            .y_mm = px_to_mm<72>(327.52f),
            .led_color = LedDef::Red,
        },
    }};

};
