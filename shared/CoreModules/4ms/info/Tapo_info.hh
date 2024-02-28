#pragma once
#include "CoreModules/elements/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct TapoInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Tapo"};
    static constexpr std::string_view description{"Tapographic Delay"};
    static constexpr uint32_t width_hp = 18;
    static constexpr std::string_view svg_filename{"res/modules/Tapo_artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 34> Elements{{
		Knob9mm{{to_mm<72>(34.7), to_mm<72>(97.51), Center, "Level", ""}},
		Knob9mm{{to_mm<72>(223.88), to_mm<72>(97.51), Center, "Morph", ""}},
		Davies1900hBlackKnob{{to_mm<72>(35.19), to_mm<72>(155.83), Center, "Time", ""}},
		Davies1900hBlackKnob{{to_mm<72>(93.97), to_mm<72>(123.98), Center, "Feedback", ""}},
		Davies1900hBlackKnob{{to_mm<72>(164.73), to_mm<72>(123.98), Center, "Modulation", ""}},
		Davies1900hBlackKnob{{to_mm<72>(223.88), to_mm<72>(155.83), Center, "Dry Wet", ""}},
		Toggle3pos{{to_mm<72>(32.13), to_mm<72>(317.005), Center, "ADD OFF INS", ""}, {"INS", "OFF", "ADD"}},
		Toggle3pos{{to_mm<72>(225.85), to_mm<72>(317.005), Center, "RES AMP LPF", ""}, {"LPF", "AMP", "RES"}},
		MomentaryRGB5mm{{to_mm<72>(39.25), to_mm<72>(61.81), Center, "Button 1", ""}},
		MomentaryRGB5mm{{to_mm<72>(75.19), to_mm<72>(61.81), Center, "Button 2", ""}},
		MomentaryRGB5mm{{to_mm<72>(111.25), to_mm<72>(61.81), Center, "Button 3", ""}},
		MomentaryRGB5mm{{to_mm<72>(147.25), to_mm<72>(61.81), Center, "Button 4", ""}},
		MomentaryRGB5mm{{to_mm<72>(183.25), to_mm<72>(61.81), Center, "Button 5", ""}},
		MomentaryRGB5mm{{to_mm<72>(218.95), to_mm<72>(61.81), Center, "Button 6", ""}},
		MomentaryRGB5mm{{to_mm<72>(64.53), to_mm<72>(296.79), Center, "Repeat", ""}},
		WhiteMomentary7mm{{to_mm<72>(129.13), to_mm<72>(315.91), Center, "Tap Sensor", ""}},
		MomentaryRGB5mm{{to_mm<72>(194.13), to_mm<72>(297.17), Center, "Delete", ""}},
		AnalogJackInput4ms{{to_mm<72>(21.33), to_mm<72>(222.74), Center, "Time Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(64.53), to_mm<72>(214.43), Center, "Feedback Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(107.66), to_mm<72>(197.04), Center, "Modulation Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(150.84), to_mm<72>(197.04), Center, "Dry Wet Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(21.22), to_mm<72>(264.77), Center, "Audio In", ""}},
		GateJackInput4ms{{to_mm<72>(64.3), to_mm<72>(256.58), Center, "Repeat Jack", ""}},
		GateJackInput4ms{{to_mm<72>(107.51), to_mm<72>(246.5), Center, "Tap", ""}},
		AnalogJackInput4ms{{to_mm<72>(150.98), to_mm<72>(246.5), Center, "Velocity", ""}},
		GateJackInput4ms{{to_mm<72>(193.9), to_mm<72>(256.58), Center, "Ext Clock", ""}},
		GateJackOutput4ms{{to_mm<72>(193.9), to_mm<72>(214.43), Center, "Gate Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(237.33), to_mm<72>(222.97), Center, "Audio Out 1", ""}},
		AnalogJackOutput4ms{{to_mm<72>(237.33), to_mm<72>(264.89), Center, "Audio Out 2", ""}},
		RedGreenBlueLight{{to_mm<72>(129.3), to_mm<72>(268.61), Center, "Tap LED", ""}},
		AltParamChoiceLabeled{{{to_mm<72>(130.256), to_mm<72>(48.37), Center, "Velocity", ""}, 5, 1}, {"Min", "Low", "Med", "High", "Max"}},
		AltParamChoiceLabeled{{{to_mm<72>(148.011), to_mm<72>(40.89), Center, "Bank", ""}, 4, 1}, {"A", "B", "C", "D"}},
		AltParamChoiceLabeled{{{to_mm<72>(166.263), to_mm<72>(33.409), Center, "Pan", ""}, 3, 1}, {"SUM/R", "RND", "ALT"}},
		AltParamChoiceLabeled{{{to_mm<72>(184.402), to_mm<72>(25.929), Center, "Mode", ""}, 2, 1}, {"Edit", "Seq"}},
}};

    enum class Elem {
        LevelKnob,
        MorphKnob,
        TimeKnob,
        FeedbackKnob,
        ModulationKnob,
        DryWetKnob,
        AddOffInsSwitch,
        ResAmpLpfSwitch,
        Button1Button,
        Button2Button,
        Button3Button,
        Button4Button,
        Button5Button,
        Button6Button,
        RepeatButton,
        TapSensorButton,
        DeleteButton,
        TimeJackIn,
        FeedbackJackIn,
        ModulationJackIn,
        DryWetJackIn,
        AudioIn,
        RepeatJackIn,
        TapIn,
        VelocityIn,
        ExtClockIn,
        GateOut,
        AudioOut1Out,
        AudioOut2Out,
        TapLedLight,
        VelocityAltParam,
        BankAltParam,
        PanAltParam,
        ModeAltParam,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobLevel, 
        KnobMorph, 
        KnobTime, 
        KnobFeedback, 
        KnobModulation, 
        KnobDry_Wet, 
        NumKnobs,
    };
    
    enum {
        SwitchAdd_Off_Ins, 
        SwitchRes_Amp_Lpf, 
        SwitchButton_1, 
        SwitchButton_2, 
        SwitchButton_3, 
        SwitchButton_4, 
        SwitchButton_5, 
        SwitchButton_6, 
        SwitchRepeat, 
        SwitchTap_Sensor, 
        SwitchDelete, 
        NumSwitches,
    };
    
    enum {
        InputTime_Jack, 
        InputFeedback_Jack, 
        InputModulation_Jack, 
        InputDry_Wet_Jack, 
        InputAudio_In, 
        InputRepeat_Jack, 
        InputTap, 
        InputVelocity, 
        InputExt_Clock, 
        NumInJacks,
    };
    
    enum {
        OutputGate_Out, 
        OutputAudio_Out_1, 
        OutputAudio_Out_2, 
        NumOutJacks,
    };
    
    enum {
        LedTap_Led, 
        NumDiscreteLeds,
    };
    
    enum {
        AltParamVelocity, 
        AltParamBank, 
        AltParamPan, 
        AltParamMode, 
    };
};
} // namespace MetaModule
