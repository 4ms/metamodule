#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct EnOscInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"EnOsc"};
    static constexpr std::string_view description{"Ensemble Oscillator"};
    static constexpr uint32_t width_hp = 16;
    static constexpr std::string_view svg_filename{"res/modules/EnOsc-artwork.svg"};

    static constexpr int NumKnobs = 9;
    
    enum {
        KnobScale = 0,
        KnobSpread = 1,
        KnobPitch = 2,
        KnobBalance = 3,
        KnobRoot = 4,
        KnobCross_Fm = 5,
        KnobTwist = 6,
        KnobDetune = 7,
        KnobWarp = 8,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobScale,
            .x_mm = px_to_mm<72>(54.1f),
            .y_mm = px_to_mm<72>(78.08f),
            .short_name = "Scale",
            .long_name = "Scale",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobSpread,
            .x_mm = px_to_mm<72>(115.27f),
            .y_mm = px_to_mm<72>(61.62f),
            .short_name = "Spread",
            .long_name = "Spread",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobPitch,
            .x_mm = px_to_mm<72>(176.96f),
            .y_mm = px_to_mm<72>(78.07f),
            .short_name = "Pitch",
            .long_name = "Pitch",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobBalance,
            .x_mm = px_to_mm<72>(32.72f),
            .y_mm = px_to_mm<72>(144.14f),
            .short_name = "Balance",
            .long_name = "Balance",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobRoot,
            .x_mm = px_to_mm<72>(115.56f),
            .y_mm = px_to_mm<72>(140.93f),
            .short_name = "Root",
            .long_name = "Root",
            .default_val = 0.5f,
            .knob_style = KnobDef::Large,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobCross_Fm,
            .x_mm = px_to_mm<72>(198.23f),
            .y_mm = px_to_mm<72>(144.14f),
            .short_name = "Cross FM",
            .long_name = "Cross FM",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobTwist,
            .x_mm = px_to_mm<72>(61.77f),
            .y_mm = px_to_mm<72>(208.21f),
            .short_name = "Twist",
            .long_name = "Twist",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobDetune,
            .x_mm = px_to_mm<72>(115.49f),
            .y_mm = px_to_mm<72>(207.86f),
            .short_name = "Detune",
            .long_name = "Detune",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobWarp,
            .x_mm = px_to_mm<72>(168.87f),
            .y_mm = px_to_mm<72>(208.21f),
            .short_name = "Warp",
            .long_name = "Warp",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 10;
    
    enum {
        InputPitch_Jack = 0,
        InputScale_Jack = 1,
        InputSpread_Jack = 2,
        InputCross_Fm_Jack = 3,
        InputLearn_Jack = 4,
        InputRoot_Jack = 5,
        InputBalance_Jack = 6,
        InputTwist_Jack = 7,
        InputWarp_Jack = 8,
        InputFreeze_Jack = 9,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputPitch_Jack,
            .x_mm = px_to_mm<72>(21.88f),
            .y_mm = px_to_mm<72>(262.78f),
            .short_name = "Pitch Jack",
            .long_name = "Pitch Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputScale_Jack,
            .x_mm = px_to_mm<72>(59.42f),
            .y_mm = px_to_mm<72>(275.86f),
            .short_name = "Scale Jack",
            .long_name = "Scale Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSpread_Jack,
            .x_mm = px_to_mm<72>(96.88f),
            .y_mm = px_to_mm<72>(262.78f),
            .short_name = "Spread Jack",
            .long_name = "Spread Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputCross_Fm_Jack,
            .x_mm = px_to_mm<72>(134.28f),
            .y_mm = px_to_mm<72>(262.78f),
            .short_name = "Cross FM Jack",
            .long_name = "Cross FM Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputLearn_Jack,
            .x_mm = px_to_mm<72>(171.75f),
            .y_mm = px_to_mm<72>(275.86f),
            .short_name = "Learn Jack",
            .long_name = "Learn Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputRoot_Jack,
            .x_mm = px_to_mm<72>(21.88f),
            .y_mm = px_to_mm<72>(305.91f),
            .short_name = "Root Jack",
            .long_name = "Root Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputBalance_Jack,
            .x_mm = px_to_mm<72>(59.42f),
            .y_mm = px_to_mm<72>(319.0f),
            .short_name = "Balance Jack",
            .long_name = "Balance Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputTwist_Jack,
            .x_mm = px_to_mm<72>(96.88f),
            .y_mm = px_to_mm<72>(305.93f),
            .short_name = "Twist Jack",
            .long_name = "Twist Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputWarp_Jack,
            .x_mm = px_to_mm<72>(134.28f),
            .y_mm = px_to_mm<72>(305.93f),
            .short_name = "Warp Jack",
            .long_name = "Warp Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputFreeze_Jack,
            .x_mm = px_to_mm<72>(171.75f),
            .y_mm = px_to_mm<72>(319.03f),
            .short_name = "Freeze Jack",
            .long_name = "Freeze Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 2;
    
    enum {
        OutputOut_A = 0,
        OutputOut_B = 1,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputOut_A,
            .x_mm = px_to_mm<72>(209.12f),
            .y_mm = px_to_mm<72>(262.78f),
            .short_name = "Out A",
            .long_name = "Out A",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_B,
            .x_mm = px_to_mm<72>(209.12f),
            .y_mm = px_to_mm<72>(305.91f),
            .short_name = "Out B",
            .long_name = "Out B",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 6;
    
    enum {
        SwitchScale_Switch = 0,
        SwitchCross_Fm_Switch = 1,
        SwitchTwist_Switch = 2,
        SwitchWarp_Switch = 3,
        SwitchLearn = 4,
        SwitchFreeze = 5,
    };

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
        {
            .id = SwitchScale_Switch,
            .x_mm = px_to_mm<72>(16.93f),
            .y_mm = px_to_mm<72>(103.025f),
            .short_name = "Scale Switch",
            .long_name = "Scale Switch",
            .switch_type = SwitchDef::Toggle3pos,
            .orientation = SwitchDef::Vertical,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchCross_Fm_Switch,
            .x_mm = px_to_mm<72>(214.23f),
            .y_mm = px_to_mm<72>(102.945f),
            .short_name = "Cross FM Switch",
            .long_name = "Cross FM Switch",
            .switch_type = SwitchDef::Toggle3pos,
            .orientation = SwitchDef::Vertical,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchTwist_Switch,
            .x_mm = px_to_mm<72>(16.93f),
            .y_mm = px_to_mm<72>(215.065f),
            .short_name = "Twist Switch",
            .long_name = "Twist Switch",
            .switch_type = SwitchDef::Toggle3pos,
            .orientation = SwitchDef::Vertical,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchWarp_Switch,
            .x_mm = px_to_mm<72>(214.23f),
            .y_mm = px_to_mm<72>(201.725f),
            .short_name = "Warp Switch",
            .long_name = "Warp Switch",
            .switch_type = SwitchDef::Toggle3pos,
            .orientation = SwitchDef::Vertical,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchLearn,
            .x_mm = px_to_mm<72>(21.63f),
            .y_mm = px_to_mm<72>(42.53f),
            .short_name = "Learn",
            .long_name = "Learn",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchFreeze,
            .x_mm = px_to_mm<72>(209.56f),
            .y_mm = px_to_mm<72>(42.53f),
            .short_name = "Freeze",
            .long_name = "Freeze",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
    }};

    static constexpr int NumDiscreteLeds = 0;
    

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
    }};

};
