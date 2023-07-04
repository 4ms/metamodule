#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct STSInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"STS"};
    static constexpr std::string_view description{"Stereo Triggered Sampler"};
    static constexpr uint32_t width_hp = 20;
    static constexpr std::string_view svg_filename{"res/modules/STS-artwork.svg"};

    static constexpr int NumKnobs = 9;
    
    enum {
        KnobPitch_L = 0,
        KnobPitch_R = 1,
        KnobSample_L = 2,
        KnobSample_R = 3,
        KnobStart_Pos__L = 4,
        KnobStart_Pos__R = 5,
        KnobLength_L = 6,
        KnobSample = 7,
        KnobLength_R = 8,
    };

    static constexpr std::array<KnobDef, NumKnobs> Knobs{{
        {
            .id = KnobPitch_L,
            .x_mm = px_to_mm<72>(37.52f),
            .y_mm = px_to_mm<72>(54.34f),
            .short_name = "Pitch L",
            .long_name = "Pitch L",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobPitch_R,
            .x_mm = px_to_mm<72>(249.91f),
            .y_mm = px_to_mm<72>(54.27f),
            .short_name = "Pitch R",
            .long_name = "Pitch R",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobSample_L,
            .x_mm = px_to_mm<72>(95.87f),
            .y_mm = px_to_mm<72>(90.17f),
            .short_name = "Sample L",
            .long_name = "Sample L",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobSample_R,
            .x_mm = px_to_mm<72>(191.25f),
            .y_mm = px_to_mm<72>(90.02f),
            .short_name = "Sample R",
            .long_name = "Sample R",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobStart_Pos__L,
            .x_mm = px_to_mm<72>(37.24f),
            .y_mm = px_to_mm<72>(123.0f),
            .short_name = "Start Pos. L",
            .long_name = "Start Pos. L",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobStart_Pos__R,
            .x_mm = px_to_mm<72>(249.6f),
            .y_mm = px_to_mm<72>(122.95f),
            .short_name = "Start Pos. R",
            .long_name = "Start Pos. R",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLength_L,
            .x_mm = px_to_mm<72>(69.36f),
            .y_mm = px_to_mm<72>(189.23f),
            .short_name = "Length L",
            .long_name = "Length L",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobSample,
            .x_mm = px_to_mm<72>(143.45f),
            .y_mm = px_to_mm<72>(183.69f),
            .short_name = "Sample",
            .long_name = "Sample",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
        {
            .id = KnobLength_R,
            .x_mm = px_to_mm<72>(218.16f),
            .y_mm = px_to_mm<72>(189.23f),
            .short_name = "Length R",
            .long_name = "Length R",
            .default_val = 0.5f,
            .knob_style = KnobDef::Medium,
            .orientation = KnobDef::Round,
        },
    }};

    static constexpr int NumInJacks = 15;
    
    enum {
        InputGate_Out = 0,
        InputLeft_Rec = 1,
        InputRec_Jack = 2,
        InputRight_Rec = 3,
        Input_1V_Oct_R = 4,
        InputPlay_Jack_L = 5,
        InputReverse_Jack_L = 6,
        InputReverse_Jack_R = 7,
        InputPlay_Jack_R = 8,
        InputLength_Cv_L = 9,
        InputStart_Pos_Cv_L = 10,
        InputSample_Cv_L = 11,
        InputSample_Cv_R = 12,
        InputStart_Pos_Cv_R = 13,
        InputLength_Cv_R = 14,
    };

    static constexpr std::array<InJackDef, NumInJacks> InJacks{{
        {
            .id = InputGate_Out,
            .x_mm = px_to_mm<72>(66.74f),
            .y_mm = px_to_mm<72>(248.15f),
            .short_name = "Gate Out",
            .long_name = "Gate Out",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputLeft_Rec,
            .x_mm = px_to_mm<72>(106.47f),
            .y_mm = px_to_mm<72>(244.71f),
            .short_name = "Left Rec",
            .long_name = "Left Rec",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputRec_Jack,
            .x_mm = px_to_mm<72>(143.45f),
            .y_mm = px_to_mm<72>(263.71f),
            .short_name = "Rec Jack",
            .long_name = "Rec Jack",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputRight_Rec,
            .x_mm = px_to_mm<72>(180.84f),
            .y_mm = px_to_mm<72>(244.71f),
            .short_name = "Right Rec",
            .long_name = "Right Rec",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = Input_1V_Oct_R,
            .x_mm = px_to_mm<72>(220.3f),
            .y_mm = px_to_mm<72>(248.15f),
            .short_name = "1V/Oct R",
            .long_name = "1V/Oct R",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputPlay_Jack_L,
            .x_mm = px_to_mm<72>(27.2f),
            .y_mm = px_to_mm<72>(283.45f),
            .short_name = "Play Jack L",
            .long_name = "Play Jack L",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputReverse_Jack_L,
            .x_mm = px_to_mm<72>(110.74f),
            .y_mm = px_to_mm<72>(283.45f),
            .short_name = "Reverse Jack L",
            .long_name = "Reverse Jack L",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputReverse_Jack_R,
            .x_mm = px_to_mm<72>(177.15f),
            .y_mm = px_to_mm<72>(283.45f),
            .short_name = "Reverse Jack R",
            .long_name = "Reverse Jack R",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputPlay_Jack_R,
            .x_mm = px_to_mm<72>(260.66f),
            .y_mm = px_to_mm<72>(283.45f),
            .short_name = "Play Jack R",
            .long_name = "Play Jack R",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputLength_Cv_L,
            .x_mm = px_to_mm<72>(27.2f),
            .y_mm = px_to_mm<72>(319.51f),
            .short_name = "Length CV L",
            .long_name = "Length CV L",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputStart_Pos_Cv_L,
            .x_mm = px_to_mm<72>(73.91f),
            .y_mm = px_to_mm<72>(319.37f),
            .short_name = "Start Pos CV L",
            .long_name = "Start Pos CV L",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSample_Cv_L,
            .x_mm = px_to_mm<72>(120.67f),
            .y_mm = px_to_mm<72>(319.51f),
            .short_name = "Sample CV L",
            .long_name = "Sample CV L",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputSample_Cv_R,
            .x_mm = px_to_mm<72>(167.23f),
            .y_mm = px_to_mm<72>(319.45f),
            .short_name = "Sample CV R",
            .long_name = "Sample CV R",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputStart_Pos_Cv_R,
            .x_mm = px_to_mm<72>(213.99f),
            .y_mm = px_to_mm<72>(319.45f),
            .short_name = "Start Pos CV R",
            .long_name = "Start Pos CV R",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
        {
            .id = InputLength_Cv_R,
            .x_mm = px_to_mm<72>(260.66f),
            .y_mm = px_to_mm<72>(319.45f),
            .short_name = "Length CV R",
            .long_name = "Length CV R",
            .unpatched_val = 0.f,
            .signal_type = InJackDef::Analog,
        },
    }};

    static constexpr int NumOutJacks = 4;
    
    enum {
        OutputOut_L = 0,
        OutputOut_R = 1,
        OutputEnd_Out_L = 2,
        OutputEnd_Out_R = 3,
    };

    static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
        {
            .id = OutputOut_L,
            .x_mm = px_to_mm<72>(27.2f),
            .y_mm = px_to_mm<72>(248.15f),
            .short_name = "Out L",
            .long_name = "Out L",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputOut_R,
            .x_mm = px_to_mm<72>(260.66f),
            .y_mm = px_to_mm<72>(248.15f),
            .short_name = "Out R",
            .long_name = "Out R",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputEnd_Out_L,
            .x_mm = px_to_mm<72>(68.86f),
            .y_mm = px_to_mm<72>(283.45f),
            .short_name = "End Out L",
            .long_name = "End Out L",
            .signal_type = OutJackDef::Analog,
        },
        {
            .id = OutputEnd_Out_R,
            .x_mm = px_to_mm<72>(219.17f),
            .y_mm = px_to_mm<72>(283.45f),
            .short_name = "End Out R",
            .long_name = "End Out R",
            .signal_type = OutJackDef::Analog,
        },
    }};

    static constexpr int NumSwitches = 9;
    
    enum {
        SwitchPlay_L = 0,
        SwitchBank_L = 1,
        SwitchBank_R = 2,
        SwitchPlay_R = 3,
        SwitchEdit_Sample = 4,
        SwitchRec = 5,
        SwitchBank = 6,
        SwitchReverse_L = 7,
        SwitchReverse_R = 8,
    };

    static constexpr std::array<SwitchDef, NumSwitches> Switches{{
        {
            .id = SwitchPlay_L,
            .x_mm = px_to_mm<72>(81.91f),
            .y_mm = px_to_mm<72>(49.62f),
            .short_name = "Play L",
            .long_name = "Play L",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchBank_L,
            .x_mm = px_to_mm<72>(122.85f),
            .y_mm = px_to_mm<72>(41.6f),
            .short_name = "Bank L",
            .long_name = "Bank L",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchBank_R,
            .x_mm = px_to_mm<72>(164.37f),
            .y_mm = px_to_mm<72>(41.88f),
            .short_name = "Bank R",
            .long_name = "Bank R",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchPlay_R,
            .x_mm = px_to_mm<72>(205.55f),
            .y_mm = px_to_mm<72>(49.77f),
            .short_name = "Play R",
            .long_name = "Play R",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchEdit_Sample,
            .x_mm = px_to_mm<72>(143.63f),
            .y_mm = px_to_mm<72>(69.21f),
            .short_name = "Edit Sample",
            .long_name = "Edit Sample",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchRec,
            .x_mm = px_to_mm<72>(127.63f),
            .y_mm = px_to_mm<72>(139.65f),
            .short_name = "REC",
            .long_name = "REC",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchBank,
            .x_mm = px_to_mm<72>(159.13f),
            .y_mm = px_to_mm<72>(139.65f),
            .short_name = "Bank",
            .long_name = "Bank",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchReverse_L,
            .x_mm = px_to_mm<72>(21.08f),
            .y_mm = px_to_mm<72>(179.74f),
            .short_name = "Reverse L",
            .long_name = "Reverse L",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
        {
            .id = SwitchReverse_R,
            .x_mm = px_to_mm<72>(266.32f),
            .y_mm = px_to_mm<72>(179.74f),
            .short_name = "Reverse R",
            .long_name = "Reverse R",
            .switch_type = SwitchDef::MomentaryButton,
            .orientation = SwitchDef::Round,
            .encoder_knob_style = SwitchDef::None,
        },
    }};

    static constexpr int NumDiscreteLeds = 4;
    
    enum {
        LedLed_L = 0,
        LedMonitor_Led = 1,
        LedBusy_Led = 2,
        LedLed_R = 3,
    };

    static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{
        {
            .id = LedLed_L,
            .x_mm = px_to_mm<72>(14.74f),
            .y_mm = px_to_mm<72>(227.18f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedMonitor_Led,
            .x_mm = px_to_mm<72>(133.57f),
            .y_mm = px_to_mm<72>(235.07f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedBusy_Led,
            .x_mm = px_to_mm<72>(153.69f),
            .y_mm = px_to_mm<72>(235.07f),
            .led_color = LedDef::Red,
        },
        {
            .id = LedLed_R,
            .x_mm = px_to_mm<72>(273.54f),
            .y_mm = px_to_mm<72>(227.18f),
            .led_color = LedDef::Red,
        },
    }};

};
