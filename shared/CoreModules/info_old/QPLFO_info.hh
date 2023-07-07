#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct QPLFOInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"QPLFO"};
    static constexpr std::string_view description{"Quad Pingable LFO"};
    static constexpr uint32_t width_hp = 12;
    static constexpr std::string_view svg_filename{"res/modules/QPLFO-artwork.svg"};

    static constexpr int NumKnobs = 4;
    
    enum {
        KnobSkew_1 = 0,
        KnobSkew_2 = 1,
        KnobSkew_3 = 2,
        KnobSkew_4 = 3,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobSkew_1,
            .x_mm = px_to_mm<72>(114.03f),
            .y_mm = px_to_mm<72>(59.68f),
            .short_name = "Skew 1",
            .long_name = "Skew 1",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobSkew_2,
            .x_mm = px_to_mm<72>(114.03f),
            .y_mm = px_to_mm<72>(135.28f),
            .short_name = "Skew 2",
            .long_name = "Skew 2",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobSkew_3,
            .x_mm = px_to_mm<72>(114.03f),
            .y_mm = px_to_mm<72>(210.88f),
            .short_name = "Skew 3",
            .long_name = "Skew 3",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobSkew_4,
            .x_mm = px_to_mm<72>(114.03f),
            .y_mm = px_to_mm<72>(286.48f),
            .short_name = "Skew 4",
            .long_name = "Skew 4",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 12;
    
    enum {
        InputPing_1_Jack = 0,
        InputSkew_1_Cv = 1,
        InputReset_1 = 2,
        InputPing_2_Jack = 3,
        InputSkew_2_Jack = 4,
        InputReset_2 = 5,
        InputPing_3_Jack = 6,
        InputSkew_3_Jack = 7,
        InputReset_3 = 8,
        InputPing_4_Jack = 9,
        InputSkew_4_Jack = 10,
        InputReset_4 = 11,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputPing_1_Jack,
            .x_mm = px_to_mm<72>(22.57f),
            .y_mm = px_to_mm<72>(42.18f),
            .short_name = "Ping 1 Jack",
            .long_name = "Ping 1 Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSkew_1_Cv,
            .x_mm = px_to_mm<72>(67.94f),
            .y_mm = px_to_mm<72>(59.46f),
            .short_name = "Skew 1 CV",
            .long_name = "Skew 1 CV",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputReset_1,
            .x_mm = px_to_mm<72>(67.94f),
            .y_mm = px_to_mm<72>(94.02f),
            .short_name = "Reset 1",
            .long_name = "Reset 1",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputPing_2_Jack,
            .x_mm = px_to_mm<72>(22.57f),
            .y_mm = px_to_mm<72>(117.78f),
            .short_name = "Ping 2 Jack",
            .long_name = "Ping 2 Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSkew_2_Jack,
            .x_mm = px_to_mm<72>(67.94f),
            .y_mm = px_to_mm<72>(135.06f),
            .short_name = "Skew 2 Jack",
            .long_name = "Skew 2 Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputReset_2,
            .x_mm = px_to_mm<72>(67.94f),
            .y_mm = px_to_mm<72>(169.62f),
            .short_name = "Reset 2",
            .long_name = "Reset 2",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputPing_3_Jack,
            .x_mm = px_to_mm<72>(22.57f),
            .y_mm = px_to_mm<72>(193.38f),
            .short_name = "Ping 3 Jack",
            .long_name = "Ping 3 Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSkew_3_Jack,
            .x_mm = px_to_mm<72>(67.94f),
            .y_mm = px_to_mm<72>(210.66f),
            .short_name = "Skew 3 Jack",
            .long_name = "Skew 3 Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputReset_3,
            .x_mm = px_to_mm<72>(67.94f),
            .y_mm = px_to_mm<72>(245.22f),
            .short_name = "Reset 3",
            .long_name = "Reset 3",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputPing_4_Jack,
            .x_mm = px_to_mm<72>(22.57f),
            .y_mm = px_to_mm<72>(268.98f),
            .short_name = "Ping 4 Jack",
            .long_name = "Ping 4 Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSkew_4_Jack,
            .x_mm = px_to_mm<72>(67.94f),
            .y_mm = px_to_mm<72>(286.26f),
            .short_name = "Skew 4 Jack",
            .long_name = "Skew 4 Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputReset_4,
            .x_mm = px_to_mm<72>(67.94f),
            .y_mm = px_to_mm<72>(320.82f),
            .short_name = "Reset 4",
            .long_name = "Reset 4",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 4;
    
    enum {
        OutputOut_1 = 0,
        OutputOut_2 = 1,
        OutputOut_3 = 2,
        OutputOut_4 = 3,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputOut_1,
            .x_mm = px_to_mm<72>(22.57f),
            .y_mm = px_to_mm<72>(76.74f),
            .short_name = "Out 1",
            .long_name = "Out 1",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_2,
            .x_mm = px_to_mm<72>(22.57f),
            .y_mm = px_to_mm<72>(152.34f),
            .short_name = "Out 2",
            .long_name = "Out 2",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_3,
            .x_mm = px_to_mm<72>(22.57f),
            .y_mm = px_to_mm<72>(227.94f),
            .short_name = "Out 3",
            .long_name = "Out 3",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_4,
            .x_mm = px_to_mm<72>(22.57f),
            .y_mm = px_to_mm<72>(303.54f),
            .short_name = "Out 4",
            .long_name = "Out 4",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 8;
    
    enum {
        SwitchPing_1 = 0,
        SwitchOn_1 = 1,
        SwitchPing_2 = 2,
        SwitchOn_2 = 3,
        SwitchPing_3 = 4,
        SwitchOn_3 = 5,
        SwitchPing_4 = 6,
        SwitchOn_4 = 7,
    };

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
        {
            .id = SwitchPing_1,
            .x_mm = px_to_mm<72>(154.79f),
            .y_mm = px_to_mm<72>(43.18f),
            .short_name = "Ping 1",
            .long_name = "Ping 1",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchOn_1,
            .x_mm = px_to_mm<72>(154.79f),
            .y_mm = px_to_mm<72>(81.06f),
            .short_name = "On 1",
            .long_name = "On 1",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchPing_2,
            .x_mm = px_to_mm<72>(154.79f),
            .y_mm = px_to_mm<72>(118.78f),
            .short_name = "Ping 2",
            .long_name = "Ping 2",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchOn_2,
            .x_mm = px_to_mm<72>(154.79f),
            .y_mm = px_to_mm<72>(156.66f),
            .short_name = "On 2",
            .long_name = "On 2",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchPing_3,
            .x_mm = px_to_mm<72>(154.79f),
            .y_mm = px_to_mm<72>(194.38f),
            .short_name = "Ping 3",
            .long_name = "Ping 3",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchOn_3,
            .x_mm = px_to_mm<72>(154.79f),
            .y_mm = px_to_mm<72>(232.26f),
            .short_name = "On 3",
            .long_name = "On 3",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchPing_4,
            .x_mm = px_to_mm<72>(154.79f),
            .y_mm = px_to_mm<72>(269.98f),
            .short_name = "Ping 4",
            .long_name = "Ping 4",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchOn_4,
            .x_mm = px_to_mm<72>(154.79f),
            .y_mm = px_to_mm<72>(307.86f),
            .short_name = "On 4",
            .long_name = "On 4",
            .switch_type = SwitchDef::LatchingButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
    }};

    static constexpr int NumDiscreteLeds = 4;
    
    enum {
        LedLed_1 = 0,
        LedLed_2 = 1,
        LedLed_3 = 2,
        LedLed_4 = 3,
    };

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
        {
            .id = LedLed_1,
            .x_mm = px_to_mm<72>(45.23f),
            .y_mm = px_to_mm<72>(76.95f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_2,
            .x_mm = px_to_mm<72>(45.23f),
            .y_mm = px_to_mm<72>(152.55f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_3,
            .x_mm = px_to_mm<72>(45.23f),
            .y_mm = px_to_mm<72>(228.15f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_4,
            .x_mm = px_to_mm<72>(45.23f),
            .y_mm = px_to_mm<72>(303.75f),
            .led_color = LedDef::Red,
        },
    }};

};
