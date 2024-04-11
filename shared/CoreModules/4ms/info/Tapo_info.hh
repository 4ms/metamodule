#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct TapoInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Tapo"};
    static constexpr std::string_view description{"Tapographic Delay"};
    static constexpr uint32_t width_hp = 18;
    static constexpr std::string_view svg_filename{"res/modules/Tapo_artwork.svg"};
	static constexpr std::string_view png_filename{"4ms/fp/Tapo.png"};

    using enum Coords;

    static constexpr std::array<Element, 30> Elements{{
		Knob9mm{{to_mm<72>(34.7), to_mm<72>(97.51), Center, "Level", ""}},
		Knob9mm{{to_mm<72>(223.88), to_mm<72>(97.51), Center, "Morph", ""}},
		Davies1900hBlackKnob{{to_mm<72>(35.19), to_mm<72>(155.83), Center, "Time", ""}},
		Davies1900hBlackKnob{{to_mm<72>(93.97), to_mm<72>(123.98), Center, "Feedback", ""}},
		Davies1900hBlackKnob{{to_mm<72>(164.73), to_mm<72>(123.98), Center, "Modulation", ""}},
		Davies1900hBlackKnob{{to_mm<72>(223.88), to_mm<72>(155.83), Center, "Dry Wet", ""}},
		Toggle3pos{{to_mm<72>(32.13), to_mm<72>(317.005), Center, "ADD OFF INS", ""}},
		Toggle3pos{{to_mm<72>(225.85), to_mm<72>(317.005), Center, "RES AMP LPF", ""}},
		WhiteMomentary7mm{{to_mm<72>(39.25), to_mm<72>(61.81), Center, "Button 1", ""}},
		WhiteMomentary7mm{{to_mm<72>(75.19), to_mm<72>(61.81), Center, "Button 2", ""}},
		WhiteMomentary7mm{{to_mm<72>(111.25), to_mm<72>(61.81), Center, "Button 3", ""}},
		WhiteMomentary7mm{{to_mm<72>(147.25), to_mm<72>(61.81), Center, "Button 4", ""}},
		WhiteMomentary7mm{{to_mm<72>(183.25), to_mm<72>(61.81), Center, "Button 5", ""}},
		WhiteMomentary7mm{{to_mm<72>(218.95), to_mm<72>(61.81), Center, "Button 6", ""}},
		WhiteMomentary7mm{{to_mm<72>(64.53), to_mm<72>(296.79), Center, "Repeat", ""}},
		WhiteMomentary7mm{{to_mm<72>(129.13), to_mm<72>(315.91), Center, "Tap Sensor", ""}},
		WhiteMomentary7mm{{to_mm<72>(194.13), to_mm<72>(297.17), Center, "Delete", ""}},
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
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobLevel = 0,
        KnobMorph = 1,
        KnobTime = 2,
        KnobFeedback = 3,
        KnobModulation = 4,
        KnobDry_Wet = 5,
        NumKnobs,
    };
    
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
        NumSwitches,
    };
    
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
        NumInJacks,
    };
    
    enum {
        OutputGate_Out = 0,
        OutputAudio_Out_1 = 1,
        OutputAudio_Out_2 = 2,
        NumOutJacks,
    };
    
    enum {
        LedTap_Led = 0,
        NumDiscreteLeds,
    };
};
} // namespace MetaModule
