#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct TapoInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Tapo"};
    static constexpr std::string_view description{"Tapographic Delay"};
    static constexpr uint32_t width_hp = 18;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Tapo-artwork.svg"};

    static constexpr std::array<Element, 30> Elements{{
		Knob9mm{to_mm<72>(34.7), to_mm<72>(97.51), "Level", "", 0, 0, 1, 0.875f},
		Knob9mm{to_mm<72>(223.88), to_mm<72>(97.51), "Morph", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(35.19), to_mm<72>(155.83), "Time", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(93.97), to_mm<72>(123.98), "Feedback", "", 0, 0, 1, 0.25f},
		Davies1900hBlackKnob{to_mm<72>(164.73), to_mm<72>(123.98), "Modulation", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(223.88), to_mm<72>(155.83), "Dry Wet", "", 0, 0, 1, 1.0f},
		AnalogJackInput4ms{to_mm<72>(21.33), to_mm<72>(222.74), "Time Jack", ""},
		AnalogJackInput4ms{to_mm<72>(64.53), to_mm<72>(214.43), "Feedback Jack", ""},
		AnalogJackInput4ms{to_mm<72>(107.66), to_mm<72>(197.04), "Modulation Jack", ""},
		AnalogJackInput4ms{to_mm<72>(150.84), to_mm<72>(197.04), "Dry Wet Jack", ""},
		AnalogJackInput4ms{to_mm<72>(21.22), to_mm<72>(264.77), "Audio In", ""},
		GateJackInput4ms{to_mm<72>(64.3), to_mm<72>(256.58), "Repeat Jack", ""},
		GateJackInput4ms{to_mm<72>(107.51), to_mm<72>(246.5), "Tap", ""},
		AnalogJackInput4ms{to_mm<72>(150.98), to_mm<72>(246.5), "Velocity", ""},
		GateJackInput4ms{to_mm<72>(193.9), to_mm<72>(256.58), "Ext Clock", ""},
		GateJackOutput4ms{to_mm<72>(193.9), to_mm<72>(214.43), "Gate Out", ""},
		AnalogJackOutput4ms{to_mm<72>(237.33), to_mm<72>(222.97), "Audio Out 1", ""},
		AnalogJackOutput4ms{to_mm<72>(237.33), to_mm<72>(264.89), "Audio Out 2", ""},
		RedGreenBlueLight{to_mm<72>(129.3), to_mm<72>(268.61), "Tap LED", ""},
		Toggle3pos{to_mm<72>(32.13), to_mm<72>(317.005), "ADD OFF INS", ""},
		Toggle3pos{to_mm<72>(225.85), to_mm<72>(317.005), "RES AMP LPF", ""},
		MomentaryButtonWhiteLight{to_mm<72>(39.25), to_mm<72>(61.81), "Button 1", ""},
		MomentaryButtonWhiteLight{to_mm<72>(75.19), to_mm<72>(61.81), "Button 2", ""},
		MomentaryButtonWhiteLight{to_mm<72>(111.25), to_mm<72>(61.81), "Button 3", ""},
		MomentaryButtonWhiteLight{to_mm<72>(147.25), to_mm<72>(61.81), "Button 4", ""},
		MomentaryButtonWhiteLight{to_mm<72>(183.25), to_mm<72>(61.81), "Button 5", ""},
		MomentaryButtonWhiteLight{to_mm<72>(218.95), to_mm<72>(61.81), "Button 6", ""},
		MomentaryButtonWhiteLight{to_mm<72>(64.53), to_mm<72>(296.79), "Repeat", ""},
		MomentaryButtonWhiteLight{to_mm<72>(129.13), to_mm<72>(315.91), "Tap Sensor", ""},
		MomentaryButtonWhiteLight{to_mm<72>(194.13), to_mm<72>(297.17), "Delete", ""},
}};

    enum class Elem {
        LevelKnob,
        MorphKnob,
        TimeKnob,
        FeedbackKnob,
        ModulationKnob,
        DryWetKnob,
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
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
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
