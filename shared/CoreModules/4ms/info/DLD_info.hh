#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct DLDInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"DLD"};
    static constexpr std::string_view description{"Dual Looping Delay"};
    static constexpr uint32_t width_hp = 20;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/DLD-artwork.svg"};

    static constexpr std::array<Element, 39> Elements{{
		Davies1900hBlackKnob{to_mm<72>(34.32), to_mm<72>(53.53), "Time A", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(254.17), to_mm<72>(53.39), "Time B", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(34.17), to_mm<72>(119.05), "Feedback A", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(254.59), to_mm<72>(119.05), "Feedback B", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(43.46), to_mm<72>(184.04), "Delay Feed A", "", 0, 0, 1, 1.0f},
		Davies1900hBlackKnob{to_mm<72>(111.56), to_mm<72>(178.84), "Mix A", "", 0, 0, 1, 0.875f},
		Davies1900hBlackKnob{to_mm<72>(177.02), to_mm<72>(178.91), "Mix B", "", 0, 0, 1, 0.875f},
		Davies1900hBlackKnob{to_mm<72>(245.19), to_mm<72>(183.78), "Delay Feed B", "", 0, 0, 1, 1.0f},
		AnalogJackInput4ms{to_mm<72>(167.59), to_mm<72>(42.51), "Ping Jack", ""},
		AnalogJackInput4ms{to_mm<72>(28.08), to_mm<72>(242.1), "In A", ""},
		AnalogJackInput4ms{to_mm<72>(71.16), to_mm<72>(242.1), "Return A", ""},
		GateJackInput4ms{to_mm<72>(122.51), to_mm<72>(242.1), "Reverse A Jack", ""},
		GateJackInput4ms{to_mm<72>(165.98), to_mm<72>(242.1), "Reverse B Jack", ""},
		AnalogJackInput4ms{to_mm<72>(217.15), to_mm<72>(242.1), "Return B", ""},
		AnalogJackInput4ms{to_mm<72>(260.18), to_mm<72>(242.1), "In B", ""},
		GateJackInput4ms{to_mm<72>(122.51), to_mm<72>(281.49), "Hold A Jack", ""},
		GateJackInput4ms{to_mm<72>(165.98), to_mm<72>(281.49), "Hold B Jack", ""},
		AnalogJackInput4ms{to_mm<72>(25.58), to_mm<72>(322.03), "Time A Jack", ""},
		AnalogJackInput4ms{to_mm<72>(72.88), to_mm<72>(322.03), "Feedback A Jack", ""},
		AnalogJackInput4ms{to_mm<72>(120.17), to_mm<72>(322.03), "Delay Feed A Jack", ""},
		AnalogJackInput4ms{to_mm<72>(167.84), to_mm<72>(322.03), "Delay Feed B Jack", ""},
		AnalogJackInput4ms{to_mm<72>(215.27), to_mm<72>(322.03), "Feedback B Jack", ""},
		AnalogJackInput4ms{to_mm<72>(262.73), to_mm<72>(322.03), "Time B Jack", ""},
		AnalogJackOutput4ms{to_mm<72>(108.25), to_mm<72>(81.44), "Loop A", ""},
		AnalogJackOutput4ms{to_mm<72>(144.16), to_mm<72>(93.48), "Clock Out", ""},
		AnalogJackOutput4ms{to_mm<72>(180.38), to_mm<72>(81.44), "Loop B", ""},
		AnalogJackOutput4ms{to_mm<72>(28.08), to_mm<72>(281.49), "Out A", ""},
		AnalogJackOutput4ms{to_mm<72>(71.16), to_mm<72>(281.49), "Send A", ""},
		AnalogJackOutput4ms{to_mm<72>(217.15), to_mm<72>(281.49), "Send B", ""},
		AnalogJackOutput4ms{to_mm<72>(260.18), to_mm<72>(281.49), "Out B", ""},
		RedGreenBlueLight{to_mm<72>(66.03), to_mm<72>(34.94), "Time A LED", ""},
		RedGreenBlueLight{to_mm<72>(222.2), to_mm<72>(34.94), "Time B LED", ""},
		Toggle3pos{to_mm<72>(84.11), to_mm<72>(51.455), "+16 | 1/8th A", ""},
		Toggle3pos{to_mm<72>(205.35), to_mm<72>(51.455), "+16 | 1/8th B", ""},
		MomentaryButtonWhiteLight{to_mm<72>(124.03), to_mm<72>(42.51), "Ping Button", ""},
		MomentaryButtonWhiteLight{to_mm<72>(81.85), to_mm<72>(123.11), "Reverse A", ""},
		MomentaryButtonWhiteLight{to_mm<72>(118.44), to_mm<72>(135.74), "Hold A", ""},
		MomentaryButtonWhiteLight{to_mm<72>(169.66), to_mm<72>(135.74), "Hold B", ""},
		MomentaryButtonWhiteLight{to_mm<72>(206.08), to_mm<72>(123.11), "Reverse B", ""},
}};

    enum class Elem {
        TimeAKnob,
        TimeBKnob,
        FeedbackAKnob,
        FeedbackBKnob,
        DelayFeedAKnob,
        MixAKnob,
        MixBKnob,
        DelayFeedBKnob,
        PingJackIn,
        InAIn,
        ReturnAIn,
        ReverseAJackIn,
        ReverseBJackIn,
        ReturnBIn,
        InBIn,
        HoldAJackIn,
        HoldBJackIn,
        TimeAJackIn,
        FeedbackAJackIn,
        DelayFeedAJackIn,
        DelayFeedBJackIn,
        FeedbackBJackIn,
        TimeBJackIn,
        LoopAOut,
        ClockOut,
        LoopBOut,
        OutAOut,
        SendAOut,
        SendBOut,
        OutBOut,
        TimeALedLight,
        TimeBLedLight,
        P16_OR_1_8ThASwitch,
        P16_OR_1_8ThBSwitch,
        PingButton,
        ReverseAButton,
        HoldAButton,
        HoldBButton,
        ReverseBButton,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobTime_A = 0,
        KnobTime_B = 1,
        KnobFeedback_A = 2,
        KnobFeedback_B = 3,
        KnobDelay_Feed_A = 4,
        KnobMix_A = 5,
        KnobMix_B = 6,
        KnobDelay_Feed_B = 7,
        NumKnobs,
    };
    
    enum {
        SwitchP16__OR__1_8Th_A = 0,
        SwitchP16__OR__1_8Th_B = 1,
        SwitchPing_Button = 2,
        SwitchReverse_A = 3,
        SwitchHold_A = 4,
        SwitchHold_B = 5,
        SwitchReverse_B = 6,
        NumSwitches,
    };
    
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
        NumInJacks,
    };
    
    enum {
        OutputLoop_A = 0,
        OutputClock_Out = 1,
        OutputLoop_B = 2,
        OutputOut_A = 3,
        OutputSend_A = 4,
        OutputSend_B = 5,
        OutputOut_B = 6,
        NumOutJacks,
    };
    
    enum {
        LedTime_A_Led = 0,
        LedTime_B_Led = 1,
        NumDiscreteLeds,
    };
};
} // namespace MetaModule
