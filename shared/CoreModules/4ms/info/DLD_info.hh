#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct DLDInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"DLD"};
    static constexpr std::string_view description{"Dual Looping Delay"};
    static constexpr uint32_t width_hp = 20;
    static constexpr std::string_view svg_filename{"res/modules/DLD_artwork.svg"};
	static constexpr std::string_view png_filename{"4ms/fp/DLD.png"};

    using enum Coords;

    static constexpr std::array<Element, 39> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(34.32), to_mm<72>(53.53), Center, "Time A", ""}},
		Davies1900hBlackKnob{{to_mm<72>(254.17), to_mm<72>(53.39), Center, "Time B", ""}},
		Davies1900hBlackKnob{{to_mm<72>(34.17), to_mm<72>(119.05), Center, "Feedback A", ""}},
		Davies1900hBlackKnob{{to_mm<72>(254.59), to_mm<72>(119.05), Center, "Feedback B", ""}},
		Davies1900hBlackKnob{{to_mm<72>(43.46), to_mm<72>(184.04), Center, "Delay Feed A", ""}},
		Davies1900hBlackKnob{{to_mm<72>(111.56), to_mm<72>(178.84), Center, "Mix A", ""}},
		Davies1900hBlackKnob{{to_mm<72>(177.02), to_mm<72>(178.91), Center, "Mix B", ""}},
		Davies1900hBlackKnob{{to_mm<72>(245.19), to_mm<72>(183.78), Center, "Delay Feed B", ""}},
		Toggle3pos{{to_mm<72>(84.11), to_mm<72>(51.455), Center, "+16 | 1/8th A", ""}},
		Toggle3pos{{to_mm<72>(205.35), to_mm<72>(51.455), Center, "+16 | 1/8th B", ""}},
		WhiteMomentary7mm{{to_mm<72>(124.03), to_mm<72>(42.51), Center, "Ping Button", ""}},
		WhiteMomentary7mm{{to_mm<72>(81.85), to_mm<72>(123.11), Center, "Reverse A", ""}},
		WhiteMomentary7mm{{to_mm<72>(118.44), to_mm<72>(135.74), Center, "Hold A", ""}},
		WhiteMomentary7mm{{to_mm<72>(169.66), to_mm<72>(135.74), Center, "Hold B", ""}},
		WhiteMomentary7mm{{to_mm<72>(206.08), to_mm<72>(123.11), Center, "Reverse B", ""}},
		AnalogJackInput4ms{{to_mm<72>(167.59), to_mm<72>(42.51), Center, "Ping Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(28.08), to_mm<72>(242.1), Center, "In A", ""}},
		AnalogJackInput4ms{{to_mm<72>(71.16), to_mm<72>(242.1), Center, "Return A", ""}},
		GateJackInput4ms{{to_mm<72>(122.51), to_mm<72>(242.1), Center, "Reverse A Jack", ""}},
		GateJackInput4ms{{to_mm<72>(165.98), to_mm<72>(242.1), Center, "Reverse B Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(217.15), to_mm<72>(242.1), Center, "Return B", ""}},
		AnalogJackInput4ms{{to_mm<72>(260.18), to_mm<72>(242.1), Center, "In B", ""}},
		GateJackInput4ms{{to_mm<72>(122.51), to_mm<72>(281.49), Center, "Hold A Jack", ""}},
		GateJackInput4ms{{to_mm<72>(165.98), to_mm<72>(281.49), Center, "Hold B Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(25.58), to_mm<72>(322.03), Center, "Time A Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(72.88), to_mm<72>(322.03), Center, "Feedback A Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(120.17), to_mm<72>(322.03), Center, "Delay Feed A Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(167.84), to_mm<72>(322.03), Center, "Delay Feed B Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(215.27), to_mm<72>(322.03), Center, "Feedback B Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(262.73), to_mm<72>(322.03), Center, "Time B Jack", ""}},
		AnalogJackOutput4ms{{to_mm<72>(108.25), to_mm<72>(81.44), Center, "Loop A", ""}},
		AnalogJackOutput4ms{{to_mm<72>(144.16), to_mm<72>(93.48), Center, "Clock Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(180.38), to_mm<72>(81.44), Center, "Loop B", ""}},
		AnalogJackOutput4ms{{to_mm<72>(28.08), to_mm<72>(281.49), Center, "Out A", ""}},
		AnalogJackOutput4ms{{to_mm<72>(71.16), to_mm<72>(281.49), Center, "Send A", ""}},
		AnalogJackOutput4ms{{to_mm<72>(217.15), to_mm<72>(281.49), Center, "Send B", ""}},
		AnalogJackOutput4ms{{to_mm<72>(260.18), to_mm<72>(281.49), Center, "Out B", ""}},
		RedGreenBlueLight{{to_mm<72>(66.03), to_mm<72>(34.94), Center, "Time A LED", ""}},
		RedGreenBlueLight{{to_mm<72>(222.2), to_mm<72>(34.94), Center, "Time B LED", ""}},
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
        P16_OR_1_8ThASwitch,
        P16_OR_1_8ThBSwitch,
        PingButton,
        ReverseAButton,
        HoldAButton,
        HoldBButton,
        ReverseBButton,
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
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
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
