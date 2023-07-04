#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct TapoInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Tapo"};
    static constexpr std::string_view description{"Tapographic Delay"};
    static constexpr uint32_t width_hp = 18;
    static constexpr std::string_view svg_filename{"res/modules/Tapo-artwork.svg"};

    static constexpr int NumKnobs = 6;
    
    enum {
        KnobLevel = 0,
        KnobMorph = 1,
        KnobTime = 2,
        KnobFeedback = 3,
        KnobModulation = 4,
        KnobDry_Wet = 5,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobLevel,
            .x_mm = px_to_mm<72>(34.7f),
            .y_mm = px_to_mm<72>(97.51f),
            .short_name = "Level",
            .long_name = "Level",
            .default_val = 0.875f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobMorph,
            .x_mm = px_to_mm<72>(223.88f),
            .y_mm = px_to_mm<72>(97.51f),
            .short_name = "Morph",
            .long_name = "Morph",
            .default_val = 0.0f,
            .knob_style = KnobDef::Small,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobTime,
            .x_mm = px_to_mm<72>(35.19f),
            .y_mm = px_to_mm<72>(155.83f),
            .short_name = "Time",
            .long_name = "Time",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobFeedback,
            .x_mm = px_to_mm<72>(93.97f),
            .y_mm = px_to_mm<72>(123.98f),
            .short_name = "Feedback",
            .long_name = "Feedback",
            .default_val = 0.25f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobModulation,
            .x_mm = px_to_mm<72>(164.73f),
            .y_mm = px_to_mm<72>(123.98f),
            .short_name = "Modulation",
            .long_name = "Modulation",
            .default_val = 0.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobDry_Wet,
            .x_mm = px_to_mm<72>(223.88f),
            .y_mm = px_to_mm<72>(155.83f),
            .short_name = "Dry Wet",
            .long_name = "Dry Wet",
            .default_val = 1.0f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 9;
    
    enum {
        InputTime_Jack = 0,
        InputFeedback_Jack = 1,
        InputModulation_Jack = 2,
        InputDry_Wet_Jack = 3,
        InputAudio_In = 4,
        InputRepeat_Jack = 5,
        InputTap = 6,
        InputVelocity = 7,
        InputExt_Clock = 8,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputTime_Jack,
            .x_mm = px_to_mm<72>(21.33f),
            .y_mm = px_to_mm<72>(222.74f),
            .short_name = "Time Jack",
            .long_name = "Time Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputFeedback_Jack,
            .x_mm = px_to_mm<72>(64.53f),
            .y_mm = px_to_mm<72>(214.43f),
            .short_name = "Feedback Jack",
            .long_name = "Feedback Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputModulation_Jack,
            .x_mm = px_to_mm<72>(107.66f),
            .y_mm = px_to_mm<72>(197.04f),
            .short_name = "Modulation Jack",
            .long_name = "Modulation Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputDry_Wet_Jack,
            .x_mm = px_to_mm<72>(150.84f),
            .y_mm = px_to_mm<72>(197.04f),
            .short_name = "Dry Wet Jack",
            .long_name = "Dry Wet Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputAudio_In,
            .x_mm = px_to_mm<72>(21.22f),
            .y_mm = px_to_mm<72>(264.77f),
            .short_name = "Audio In",
            .long_name = "Audio In",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputRepeat_Jack,
            .x_mm = px_to_mm<72>(64.3f),
            .y_mm = px_to_mm<72>(256.58f),
            .short_name = "Repeat Jack",
            .long_name = "Repeat Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputTap,
            .x_mm = px_to_mm<72>(107.51f),
            .y_mm = px_to_mm<72>(246.5f),
            .short_name = "Tap",
            .long_name = "Tap",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputVelocity,
            .x_mm = px_to_mm<72>(150.98f),
            .y_mm = px_to_mm<72>(246.5f),
            .short_name = "Velocity",
            .long_name = "Velocity",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputExt_Clock,
            .x_mm = px_to_mm<72>(193.9f),
            .y_mm = px_to_mm<72>(256.58f),
            .short_name = "Ext Clock",
            .long_name = "Ext Clock",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 3;
    
    enum {
        OutputGate_Out = 0,
        OutputAudio_Out_1 = 1,
        OutputAudio_Out_2 = 2,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputGate_Out,
            .x_mm = px_to_mm<72>(193.9f),
            .y_mm = px_to_mm<72>(214.43f),
            .short_name = "Gate Out",
            .long_name = "Gate Out",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputAudio_Out_1,
            .x_mm = px_to_mm<72>(237.33f),
            .y_mm = px_to_mm<72>(222.97f),
            .short_name = "Audio Out 1",
            .long_name = "Audio Out 1",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputAudio_Out_2,
            .x_mm = px_to_mm<72>(237.33f),
            .y_mm = px_to_mm<72>(264.89f),
            .short_name = "Audio Out 2",
            .long_name = "Audio Out 2",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 11;
    
    enum {
        SwitchAdd_Off_Ins = 0,
        SwitchRes_Amp_Lpf = 1,
        SwitchButton_1 = 2,
        SwitchButton_2 = 3,
        SwitchButton_3 = 4,
        SwitchButton_4 = 5,
        SwitchButton_5 = 6,
        SwitchButton_6 = 7,
        SwitchRepeat = 8,
        SwitchTap_Sensor = 9,
        SwitchDelete = 10,
    };

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
        {
            .id = SwitchAdd_Off_Ins,
            .x_mm = px_to_mm<72>(32.13f),
            .y_mm = px_to_mm<72>(317.005f),
            .short_name = "ADD OFF INS",
            .long_name = "ADD OFF INS",
            .switch_type = SwitchDef::Toggle3pos,
            .orientation = SwitchDef::Vertical,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchRes_Amp_Lpf,
            .x_mm = px_to_mm<72>(225.85f),
            .y_mm = px_to_mm<72>(317.005f),
            .short_name = "RES AMP LPF",
            .long_name = "RES AMP LPF",
            .switch_type = SwitchDef::Toggle3pos,
            .orientation = SwitchDef::Vertical,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchButton_1,
            .x_mm = px_to_mm<72>(39.25f),
            .y_mm = px_to_mm<72>(61.81f),
            .short_name = "Button 1",
            .long_name = "Button 1",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchButton_2,
            .x_mm = px_to_mm<72>(75.19f),
            .y_mm = px_to_mm<72>(61.81f),
            .short_name = "Button 2",
            .long_name = "Button 2",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchButton_3,
            .x_mm = px_to_mm<72>(111.25f),
            .y_mm = px_to_mm<72>(61.81f),
            .short_name = "Button 3",
            .long_name = "Button 3",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchButton_4,
            .x_mm = px_to_mm<72>(147.25f),
            .y_mm = px_to_mm<72>(61.81f),
            .short_name = "Button 4",
            .long_name = "Button 4",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchButton_5,
            .x_mm = px_to_mm<72>(183.25f),
            .y_mm = px_to_mm<72>(61.81f),
            .short_name = "Button 5",
            .long_name = "Button 5",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchButton_6,
            .x_mm = px_to_mm<72>(218.95f),
            .y_mm = px_to_mm<72>(61.81f),
            .short_name = "Button 6",
            .long_name = "Button 6",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchRepeat,
            .x_mm = px_to_mm<72>(64.53f),
            .y_mm = px_to_mm<72>(296.79f),
            .short_name = "Repeat",
            .long_name = "Repeat",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchTap_Sensor,
            .x_mm = px_to_mm<72>(129.13f),
            .y_mm = px_to_mm<72>(315.91f),
            .short_name = "Tap Sensor",
            .long_name = "Tap Sensor",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchDelete,
            .x_mm = px_to_mm<72>(194.13f),
            .y_mm = px_to_mm<72>(297.17f),
            .short_name = "Delete",
            .long_name = "Delete",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
    }};

    static constexpr int NumDiscreteLeds = 1;
    
    enum {
        LedTap_Led = 0,
    };

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
        {
            .id = LedTap_Led,
            .x_mm = px_to_mm<72>(129.3f),
            .y_mm = px_to_mm<72>(268.61f),
            .led_color = LedDef::Red,
        },
    }};

};
