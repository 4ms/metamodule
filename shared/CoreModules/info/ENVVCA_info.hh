#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct ENVVCAInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"ENVVCA"};
    static constexpr std::string_view description{"Envelope VCA"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/ENVVCA-artwork.svg"};

    static constexpr int NumKnobs = 5;
    
    enum {
        KnobRise_Slider = 0,
        KnobFall_Slider = 1,
        KnobEnv_Level_Slider = 2,
        KnobRise_Cv = 3,
        KnobFall_Cv = 4,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobRise_Slider,
            .x_mm = px_to_mm<72>(23.185f),
            .y_mm = px_to_mm<72>(108.81f),
            .short_name = "Rise Slider",
            .long_name = "Rise Slider",
            .default_val = 0.5f,
            .knob_style = KnobDef::Slider25mm,
            .orientation = KnobDef::Vertical,
        },
        {
            .id = KnobFall_Slider,
            .x_mm = px_to_mm<72>(57.325f),
            .y_mm = px_to_mm<72>(109.02f),
            .short_name = "Fall Slider",
            .long_name = "Fall Slider",
            .default_val = 0.5f,
            .knob_style = KnobDef::Slider25mm,
            .orientation = KnobDef::Vertical,
        },
        {
            .id = KnobEnv_Level_Slider,
            .x_mm = px_to_mm<72>(91.505f),
            .y_mm = px_to_mm<72>(108.81f),
            .short_name = "Env Level Slider",
            .long_name = "Env Level Slider",
            .default_val = 1.0f,
            .knob_style = KnobDef::Slider25mm,
            .orientation = KnobDef::Vertical,
        },
        {
            .id = KnobRise_Cv,
            .x_mm = px_to_mm<72>(21.69f),
            .y_mm = px_to_mm<72>(178.25f),
            .short_name = "Rise CV",
            .long_name = "Rise CV",
            .default_val = 1.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobFall_Cv,
            .x_mm = px_to_mm<72>(92.85f),
            .y_mm = px_to_mm<72>(178.25f),
            .short_name = "Fall CV",
            .long_name = "Fall CV",
            .default_val = 1.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 5;
    
    enum {
        InputTime_Cv = 0,
        InputTrigger = 1,
        InputCycle = 2,
        InputFollow = 3,
        InputIn = 4,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputTime_Cv,
            .x_mm = px_to_mm<72>(57.25f),
            .y_mm = px_to_mm<72>(203.53f),
            .short_name = "Time CV",
            .long_name = "Time CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputTrigger,
            .x_mm = px_to_mm<72>(22.3f),
            .y_mm = px_to_mm<72>(227.06f),
            .short_name = "Trigger",
            .long_name = "Trigger",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputCycle,
            .x_mm = px_to_mm<72>(57.25f),
            .y_mm = px_to_mm<72>(254.25f),
            .short_name = "Cycle",
            .long_name = "Cycle",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputFollow,
            .x_mm = px_to_mm<72>(22.3f),
            .y_mm = px_to_mm<72>(278.73f),
            .short_name = "Follow",
            .long_name = "Follow",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputIn,
            .x_mm = px_to_mm<72>(35.87f),
            .y_mm = px_to_mm<72>(322.47f),
            .short_name = "In",
            .long_name = "In",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 3;
    
    enum {
        OutputEnv = 0,
        OutputEor = 1,
        OutputOut = 2,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputEnv,
            .x_mm = px_to_mm<72>(92.03f),
            .y_mm = px_to_mm<72>(227.06f),
            .short_name = "Env",
            .long_name = "Env",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputEor,
            .x_mm = px_to_mm<72>(92.03f),
            .y_mm = px_to_mm<72>(278.73f),
            .short_name = "EOR",
            .long_name = "EOR",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut,
            .x_mm = px_to_mm<72>(78.57f),
            .y_mm = px_to_mm<72>(322.5f),
            .short_name = "Out",
            .long_name = "Out",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 3;
    
    enum {
        SwitchSlow_Med_Fast_Rise = 0,
        SwitchSlow_Med_Fast_Fall = 1,
        SwitchCycle = 2,
    };

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
        {
            .id = SwitchSlow_Med_Fast_Rise,
            .x_mm = px_to_mm<72>(23.19f),
            .y_mm = px_to_mm<72>(43.305f),
            .short_name = "Slow Med Fast Rise",
            .long_name = "Slow Med Fast Rise",
            .switch_type = SwitchDef::Toggle3pos,
            .orientation = SwitchDef::Vertical,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchSlow_Med_Fast_Fall,
            .x_mm = px_to_mm<72>(57.33f),
            .y_mm = px_to_mm<72>(43.305f),
            .short_name = "Slow Med Fast Fall",
            .long_name = "Slow Med Fast Fall",
            .switch_type = SwitchDef::Toggle3pos,
            .orientation = SwitchDef::Vertical,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchCycle,
            .x_mm = px_to_mm<72>(92.17f),
            .y_mm = px_to_mm<72>(41.65f),
            .short_name = "Cycle",
            .long_name = "Cycle",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
    }};

    static constexpr int NumDiscreteLeds = 3;
    
    enum {
        LedRise_Led = 0,
        LedFall_Led = 1,
        LedEor_Led = 2,
    };

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
        {
            .id = LedRise_Led,
            .x_mm = px_to_mm<72>(45.11f),
            .y_mm = px_to_mm<72>(174.84f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedFall_Led,
            .x_mm = px_to_mm<72>(69.34f),
            .y_mm = px_to_mm<72>(174.84f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedEor_Led,
            .x_mm = px_to_mm<72>(106.41f),
            .y_mm = px_to_mm<72>(256.6f),
            .led_color = LedDef::Red,
        },
    }};

};
