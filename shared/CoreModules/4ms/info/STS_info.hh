#pragma once
#include "CoreModules/elements/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct STSInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"STS"};
    static constexpr std::string_view description{"Stereo Triggered Sampler"};
    static constexpr uint32_t width_hp = 20;
    static constexpr std::string_view svg_filename{"res/modules/STS_artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 41> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(37.52), to_mm<72>(54.34), Center, "Pitch L", ""}},
		Davies1900hBlackKnob{{to_mm<72>(249.91), to_mm<72>(54.27), Center, "Pitch R", ""}},
		Davies1900hBlackKnob{{to_mm<72>(95.87), to_mm<72>(90.17), Center, "Sample L", ""}},
		Davies1900hBlackKnob{{to_mm<72>(191.25), to_mm<72>(90.02), Center, "Sample R", ""}},
		Davies1900hBlackKnob{{to_mm<72>(37.24), to_mm<72>(123.0), Center, "Start Pos. L", ""}},
		Davies1900hBlackKnob{{to_mm<72>(249.6), to_mm<72>(122.95), Center, "Start Pos. R", ""}},
		Davies1900hBlackKnob{{to_mm<72>(69.36), to_mm<72>(189.23), Center, "Length L", ""}},
		Davies1900hBlackKnob{{to_mm<72>(143.45), to_mm<72>(183.69), Center, "Sample", ""}},
		Davies1900hBlackKnob{{to_mm<72>(218.16), to_mm<72>(189.23), Center, "Length R", ""}},
		WhiteMomentary7mm{{to_mm<72>(81.91), to_mm<72>(49.62), Center, "Play L", ""}},
		WhiteMomentary7mm{{to_mm<72>(122.85), to_mm<72>(41.6), Center, "Bank L", ""}},
		WhiteMomentary7mm{{to_mm<72>(164.37), to_mm<72>(41.88), Center, "Bank R", ""}},
		WhiteMomentary7mm{{to_mm<72>(205.55), to_mm<72>(49.77), Center, "Play R", ""}},
		WhiteMomentary7mm{{to_mm<72>(143.63), to_mm<72>(69.21), Center, "Edit Sample", ""}},
		WhiteMomentary7mm{{to_mm<72>(127.63), to_mm<72>(139.65), Center, "REC", ""}},
		WhiteMomentary7mm{{to_mm<72>(159.13), to_mm<72>(139.65), Center, "Bank", ""}},
		WhiteMomentary7mm{{to_mm<72>(21.08), to_mm<72>(179.74), Center, "Reverse L", ""}},
		WhiteMomentary7mm{{to_mm<72>(266.32), to_mm<72>(179.74), Center, "Reverse R", ""}},
		AnalogJackInput4ms{{to_mm<72>(66.74), to_mm<72>(248.15), Center, "Gate Out", ""}},
		AnalogJackInput4ms{{to_mm<72>(106.47), to_mm<72>(244.71), Center, "Left Rec", ""}},
		GateJackInput4ms{{to_mm<72>(143.45), to_mm<72>(263.71), Center, "Rec Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(180.84), to_mm<72>(244.71), Center, "Right Rec", ""}},
		AnalogJackInput4ms{{to_mm<72>(220.3), to_mm<72>(248.15), Center, "1V/Oct R", ""}},
		GateJackInput4ms{{to_mm<72>(27.2), to_mm<72>(283.45), Center, "Play Jack L", ""}},
		GateJackInput4ms{{to_mm<72>(110.74), to_mm<72>(283.45), Center, "Reverse Jack L", ""}},
		GateJackInput4ms{{to_mm<72>(177.15), to_mm<72>(283.45), Center, "Reverse Jack R", ""}},
		GateJackInput4ms{{to_mm<72>(260.66), to_mm<72>(283.45), Center, "Play Jack R", ""}},
		AnalogJackInput4ms{{to_mm<72>(27.2), to_mm<72>(319.51), Center, "Length CV L", ""}},
		AnalogJackInput4ms{{to_mm<72>(73.91), to_mm<72>(319.37), Center, "Start Pos CV L", ""}},
		AnalogJackInput4ms{{to_mm<72>(120.67), to_mm<72>(319.51), Center, "Sample CV L", ""}},
		AnalogJackInput4ms{{to_mm<72>(167.23), to_mm<72>(319.45), Center, "Sample CV R", ""}},
		AnalogJackInput4ms{{to_mm<72>(213.99), to_mm<72>(319.45), Center, "Start Pos CV R", ""}},
		AnalogJackInput4ms{{to_mm<72>(260.66), to_mm<72>(319.45), Center, "Length CV R", ""}},
		AnalogJackOutput4ms{{to_mm<72>(27.2), to_mm<72>(248.15), Center, "Out L", ""}},
		AnalogJackOutput4ms{{to_mm<72>(260.66), to_mm<72>(248.15), Center, "Out R", ""}},
		AnalogJackOutput4ms{{to_mm<72>(68.86), to_mm<72>(283.45), Center, "End Out L", ""}},
		AnalogJackOutput4ms{{to_mm<72>(219.17), to_mm<72>(283.45), Center, "End Out R", ""}},
		RedGreenBlueLight{{to_mm<72>(14.74), to_mm<72>(227.18), Center, "LED L", ""}},
		RedGreenBlueLight{{to_mm<72>(133.57), to_mm<72>(235.07), Center, "Monitor LED", ""}},
		RedGreenBlueLight{{to_mm<72>(153.69), to_mm<72>(235.07), Center, "Busy LED", ""}},
		RedGreenBlueLight{{to_mm<72>(273.54), to_mm<72>(227.18), Center, "LED R", ""}},
}};

    enum class Elem {
        PitchLKnob,
        PitchRKnob,
        SampleLKnob,
        SampleRKnob,
        StartPos_LKnob,
        StartPos_RKnob,
        LengthLKnob,
        SampleKnob,
        LengthRKnob,
        PlayLButton,
        BankLButton,
        BankRButton,
        PlayRButton,
        EditSampleButton,
        RecButton,
        BankButton,
        ReverseLButton,
        ReverseRButton,
        GateOutIn,
        LeftRecIn,
        RecJackIn,
        RightRecIn,
        _1V_OctRIn,
        PlayJackLIn,
        ReverseJackLIn,
        ReverseJackRIn,
        PlayJackRIn,
        LengthCvLIn,
        StartPosCvLIn,
        SampleCvLIn,
        SampleCvRIn,
        StartPosCvRIn,
        LengthCvRIn,
        OutLOut,
        OutROut,
        EndOutLOut,
        EndOutROut,
        LedLLight,
        MonitorLedLight,
        BusyLedLight,
        LedRLight,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
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
        NumKnobs,
    };
    
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
        NumSwitches,
    };
    
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
        NumInJacks,
    };
    
    enum {
        OutputOut_L = 0,
        OutputOut_R = 1,
        OutputEnd_Out_L = 2,
        OutputEnd_Out_R = 3,
        NumOutJacks,
    };
    
    enum {
        LedLed_L = 0,
        LedMonitor_Led = 1,
        LedBusy_Led = 2,
        LedLed_R = 3,
        NumDiscreteLeds,
    };
};
} // namespace MetaModule
