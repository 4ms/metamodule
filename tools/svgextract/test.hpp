
#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct EnOscInfo : ModuleInfoBase {
    static constexpr auto NameChars = CoreProcessor::NameChars;
    static constexpr auto LongNameChars = CoreProcessor::LongNameChars;

    static constexpr std::string_view slug{"EnOsc"};
    static inline const StaticString<LongNameChars> description{"Ensemble Oscillator"};
    static constexpr uint32_t width_hp = 16;
    static constexpr std::string_view svg_filename{"res/EnOsc-artwork.svg"};

    static constexpr int NumKnobs = 9;
    
    enum  {
        KnobSpread = 0,
        KnobScale = 1,
        KnobPitch = 2,
        KnobRoot = 3,
        KnobBalance = 4,
        KnobCross_FM = 5,
        KnobDetune = 6,
        KnobTwist = 7,
        KnobWarp = 8,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobSpread,
            .x_mm = px_to_mm<72>(114.85f),
            .y_mm = px_to_mm<72>(61.59f),
            .short_name = "Spread",
            .long_name = "Spread",
            .default_val = 0.f,
            .knob_style = KnobDef::Medium,
        },
        {
            .id = KnobScale,
            .x_mm = px_to_mm<72>(53.68f),
            .y_mm = px_to_mm<72>(78.08f),
            .short_name = "Scale",
            .long_name = "Scale",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
        },
        {
            .id = KnobPitch,
            .x_mm = px_to_mm<72>(176.54f),
            .y_mm = px_to_mm<72>(78.08f),
            .short_name = "Pitch",
            .long_name = "Pitch",
            .default_val = 0.f,
            .knob_style = KnobDef::Medium,
        },
        {
            .id = KnobRoot,
            .x_mm = px_to_mm<72>(115.14f),
            .y_mm = px_to_mm<72>(140.92f),
            .short_name = "Root",
            .long_name = "Root",
            .default_val = 0.5f,
            .knob_style = KnobDef::Large,
        },
        {
            .id = KnobBalance,
            .x_mm = px_to_mm<72>(32.3f),
            .y_mm = px_to_mm<72>(144.18f),
            .short_name = "Balance",
            .long_name = "Balance",
            .default_val = 0.f,
            .knob_style = KnobDef::Medium,
        },
        {
            .id = KnobCross_FM,
            .x_mm = px_to_mm<72>(197.81f),
            .y_mm = px_to_mm<72>(144.18f),
            .short_name = "Cross Fm",
            .long_name = "Cross Fm",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
        },
        {
            .id = KnobDetune,
            .x_mm = px_to_mm<72>(115.07f),
            .y_mm = px_to_mm<72>(207.86f),
            .short_name = "Detune",
            .long_name = "Detune",
            .default_val = 0.f,
            .knob_style = KnobDef::Small,
        },
        {
            .id = KnobTwist,
            .x_mm = px_to_mm<72>(61.35f),
            .y_mm = px_to_mm<72>(208.2f),
            .short_name = "Twist",
            .long_name = "Twist",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
        },
        {
            .id = KnobWarp,
            .x_mm = px_to_mm<72>(168.4f),
            .y_mm = px_to_mm<72>(208.2f),
            .short_name = "Warp",
            .long_name = "Warp",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
        },
    }};

    static constexpr int NumInJacks = 10;
    
    enum  {
        InputPitch = 0,
        InputSpread = 1,
        InputCross_FM = 2,
        InputScale = 3,
        InputLearn = 4,
        InputRoot = 5,
        InputTwist = 6,
        InputWarp = 7,
        InputBalance = 8,
        InputFreeze = 9,
    };

    static constexpr std::array<InJackDef, NumInJacks> Inputs{{
        {
            .id = InputPitch,
            .x_mm = px_to_mm<72>(21.45f),
            .y_mm = px_to_mm<72>(262.78f),
            .short_name = "Pitch",
            .long_name = "Pitch",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSpread,
            .x_mm = px_to_mm<72>(96.46f),
            .y_mm = px_to_mm<72>(262.78f),
            .short_name = "Spread",
            .long_name = "Spread",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputCross_FM,
            .x_mm = px_to_mm<72>(133.86f),
            .y_mm = px_to_mm<72>(262.78f),
            .short_name = "Cross Fm",
            .long_name = "Cross Fm",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputScale,
            .x_mm = px_to_mm<72>(59.0f),
            .y_mm = px_to_mm<72>(275.86f),
            .short_name = "Scale",
            .long_name = "Scale",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputLearn,
            .x_mm = px_to_mm<72>(171.32f),
            .y_mm = px_to_mm<72>(275.86f),
            .short_name = "Learn",
            .long_name = "Learn",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputRoot,
            .x_mm = px_to_mm<72>(21.45f),
            .y_mm = px_to_mm<72>(305.91f),
            .short_name = "Root",
            .long_name = "Root",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputTwist,
            .x_mm = px_to_mm<72>(96.46f),
            .y_mm = px_to_mm<72>(305.93f),
            .short_name = "Twist",
            .long_name = "Twist",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputWarp,
            .x_mm = px_to_mm<72>(133.86f),
            .y_mm = px_to_mm<72>(305.93f),
            .short_name = "Warp",
            .long_name = "Warp",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputBalance,
            .x_mm = px_to_mm<72>(59.0f),
            .y_mm = px_to_mm<72>(319.0f),
            .short_name = "Balance",
            .long_name = "Balance",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputFreeze,
            .x_mm = px_to_mm<72>(171.32f),
            .y_mm = px_to_mm<72>(319.02f),
            .short_name = "Freeze",
            .long_name = "Freeze",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 2;
    
    enum  {
        OutputOut_A = 0,
        OutputOut_B = 1,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> Outputs{{
        {
            .id = OutputOut_A,
            .x_mm = px_to_mm<72>(208.7f),
            .y_mm = px_to_mm<72>(262.78f),
            .short_name = "Out A",
            .long_name = "Out A",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_B,
            .x_mm = px_to_mm<72>(208.7f),
            .y_mm = px_to_mm<72>(305.91f),
            .short_name = "Out B",
            .long_name = "Out B",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 6;
    
    enum  {
        SwitchLearn = 0,
        SwitchFreeze = 1,
        SwitchCross_FM = 2,
        SwitchScale = 3,
        SwitchWarp = 4,
        SwitchTwist = 5,
    };

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
        {
            .id = SwitchLearn,
            .x_mm = px_to_mm<72>(21.21f),
            .y_mm = px_to_mm<72>(42.53f),
            .short_name = "Learn",
            .long_name = "Learn",
            .switch_type = SwitchDef::MomentaryButton,
        },
        {
            .id = SwitchFreeze,
            .x_mm = px_to_mm<72>(209.14f),
            .y_mm = px_to_mm<72>(42.53f),
            .short_name = "Freeze",
            .long_name = "Freeze",
            .switch_type = SwitchDef::MomentaryButton,
        },
        {
            .id = SwitchCross_FM,
            .x_mm = px_to_mm<72>(213.81f),
            .y_mm = px_to_mm<72>(102.95f),
            .short_name = "Cross Fm",
            .long_name = "Cross Fm",
            .switch_type = SwitchDef::Toggle3pos,
        },
        {
            .id = SwitchScale,
            .x_mm = px_to_mm<72>(16.51f),
            .y_mm = px_to_mm<72>(103.03f),
            .short_name = "Scale",
            .long_name = "Scale",
            .switch_type = SwitchDef::Toggle3pos,
        },
        {
            .id = SwitchWarp,
            .x_mm = px_to_mm<72>(213.81f),
            .y_mm = px_to_mm<72>(201.73f),
            .short_name = "Warp",
            .long_name = "Warp",
            .switch_type = SwitchDef::Toggle3pos,
        },
        {
            .id = SwitchTwist,
            .x_mm = px_to_mm<72>(16.51f),
            .y_mm = px_to_mm<72>(215.06f),
            .short_name = "Twist",
            .long_name = "Twist",
            .switch_type = SwitchDef::Toggle3pos,
        },
    }};

};
