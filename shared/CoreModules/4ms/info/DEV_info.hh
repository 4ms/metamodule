#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct DEVInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"DEV"};
    static constexpr std::string_view description{"Dual EnvVCA"};
    static constexpr uint32_t width_hp = 16;
    static constexpr std::string_view svg_filename{"res/modules/DEV-artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 44> Elements{{
		Slider25mmVertLED{to_mm<72>(22.415), to_mm<72>(108.25), Center, "Rise A Slider", ""},
		Slider25mmVertLED{to_mm<72>(56.265), to_mm<72>(108.25), Center, "Fall A Slider", ""},
		Slider25mmVertLED{to_mm<72>(174.115), to_mm<72>(108.25), Center, "Rise B Slider", ""},
		Slider25mmVertLED{to_mm<72>(207.965), to_mm<72>(108.25), Center, "Fall B Slider", ""},
		Knob9mm{to_mm<72>(93.13), to_mm<72>(95.86), Center, "Level A", ""},
		Knob9mm{to_mm<72>(137.25), to_mm<72>(95.86), Center, "Level B", ""},
		Knob9mm{to_mm<72>(93.13), to_mm<72>(138.65), Center, "Offset A", ""},
		Knob9mm{to_mm<72>(137.25), to_mm<72>(138.65), Center, "Offset B", ""},
		Knob9mm{to_mm<72>(23.5), to_mm<72>(184.03), Center, "Rise A", ""},
		Knob9mm{to_mm<72>(94.11), to_mm<72>(183.67), Center, "Fall A", ""},
		Knob9mm{to_mm<72>(136.27), to_mm<72>(184.03), Center, "Rise B", ""},
		Knob9mm{to_mm<72>(206.87), to_mm<72>(184.03), Center, "Fall B", ""},
		GateJackInput4ms{to_mm<72>(115.19), to_mm<72>(60.85), Center, "Cycle Trig?", ""},
		AnalogJackInput4ms{to_mm<72>(58.56), to_mm<72>(208.68), Center, "Time CV A", ""},
		AnalogJackInput4ms{to_mm<72>(171.86), to_mm<72>(208.68), Center, "Time CV B", ""},
		GateJackInput4ms{to_mm<72>(23.09), to_mm<72>(232.82), Center, "Trig A", ""},
		AnalogJackInput4ms{to_mm<72>(58.52), to_mm<72>(252.75), Center, "Follow A", ""},
		AnalogJackInput4ms{to_mm<72>(171.85), to_mm<72>(252.75), Center, "Follow B", ""},
		GateJackInput4ms{to_mm<72>(207.29), to_mm<72>(232.82), Center, "Trig B", ""},
		AnalogJackInput4ms{to_mm<72>(23.06), to_mm<72>(274.73), Center, "Audio A In", ""},
		AnalogJackInput4ms{to_mm<72>(58.48), to_mm<72>(300.48), Center, "VCA CV A", ""},
		AnalogJackInput4ms{to_mm<72>(171.9), to_mm<72>(300.41), Center, "VCA CV B", ""},
		AnalogJackInput4ms{to_mm<72>(207.29), to_mm<72>(274.76), Center, "Audio B In", ""},
		GateJackOutput4ms{to_mm<72>(95.04), to_mm<72>(233.88), Center, "EOR A", ""},
		GateJackOutput4ms{to_mm<72>(135.28), to_mm<72>(233.99), Center, "EOF B", ""},
		AnalogJackOutput4ms{to_mm<72>(115.22), to_mm<72>(288.78), Center, "OR", ""},
		AnalogJackOutput4ms{to_mm<72>(23.06), to_mm<72>(324.82), Center, "Audio A Out", ""},
		AnalogJackOutput4ms{to_mm<72>(90.49), to_mm<72>(324.82), Center, "Env A Out", ""},
		AnalogJackOutput4ms{to_mm<72>(139.91), to_mm<72>(324.88), Center, "Env B Out", ""},
		AnalogJackOutput4ms{to_mm<72>(207.32), to_mm<72>(324.82), Center, "Audio B Out", ""},
		RedGreenBlueLight{to_mm<72>(45.84), to_mm<72>(176.26), Center, "Rise LED A", ""},
		RedGreenBlueLight{to_mm<72>(70.54), to_mm<72>(176.26), Center, "Fall LED A", ""},
		RedGreenBlueLight{to_mm<72>(159.84), to_mm<72>(176.26), Center, "Rise LED B", ""},
		RedGreenBlueLight{to_mm<72>(184.53), to_mm<72>(176.26), Center, "Fall LED B", ""},
		RedGreenBlueLight{to_mm<72>(99.58), to_mm<72>(260.79), Center, "EOR LED", ""},
		RedGreenBlueLight{to_mm<72>(130.68), to_mm<72>(261.07), Center, "EOF LED", ""},
		RedGreenBlueLight{to_mm<72>(65.92), to_mm<72>(327.45), Center, "Env A LED", ""},
		RedGreenBlueLight{to_mm<72>(164.39), to_mm<72>(327.52), Center, "Env B LED", ""},
		Toggle3pos{to_mm<72>(17.6), to_mm<72>(41.905), Center, "Slow Med Fast Rise A", ""},
		Toggle3pos{to_mm<72>(50.49), to_mm<72>(41.905), Center, "Slow Med Fast Fall A", ""},
		Toggle3pos{to_mm<72>(179.89), to_mm<72>(41.905), Center, "Slow Med Fast Rise B", ""},
		Toggle3pos{to_mm<72>(212.77), to_mm<72>(41.905), Center, "Slow Med Fast Fall B", ""},
		LatchingButtonMonoLight{to_mm<72>(82.8), to_mm<72>(41.64), Center, "Cycle A", ""},
		LatchingButtonMonoLight{to_mm<72>(147.61), to_mm<72>(41.68), Center, "Cycle B", ""},
}};

    enum class Elem {
        RiseASlider,
        FallASlider,
        RiseBSlider,
        FallBSlider,
        LevelAKnob,
        LevelBKnob,
        OffsetAKnob,
        OffsetBKnob,
        RiseAKnob,
        FallAKnob,
        RiseBKnob,
        FallBKnob,
        CycleTrig_In,
        TimeCvAIn,
        TimeCvBIn,
        TrigAIn,
        FollowAIn,
        FollowBIn,
        TrigBIn,
        AudioAIn,
        VcaCvAIn,
        VcaCvBIn,
        AudioBIn,
        EorAOut,
        EofBOut,
        OrOut,
        AudioAOut,
        EnvAOut,
        EnvBOut,
        AudioBOut,
        RiseLedALight,
        FallLedALight,
        RiseLedBLight,
        FallLedBLight,
        EorLedLight,
        EofLedLight,
        EnvALedLight,
        EnvBLedLight,
        SlowMedFastRiseASwitch,
        SlowMedFastFallASwitch,
        SlowMedFastRiseBSwitch,
        SlowMedFastFallBSwitch,
        CycleAButton,
        CycleBButton,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobRise_A_Slider = 0,
        KnobFall_A_Slider = 1,
        KnobRise_B_Slider = 2,
        KnobFall_B_Slider = 3,
        KnobLevel_A = 4,
        KnobLevel_B = 5,
        KnobOffset_A = 6,
        KnobOffset_B = 7,
        KnobRise_A = 8,
        KnobFall_A = 9,
        KnobRise_B = 10,
        KnobFall_B = 11,
        NumKnobs,
    };
    
    enum {
        SwitchSlow_Med_Fast_Rise_A = 0,
        SwitchSlow_Med_Fast_Fall_A = 1,
        SwitchSlow_Med_Fast_Rise_B = 2,
        SwitchSlow_Med_Fast_Fall_B = 3,
        SwitchCycle_A = 4,
        SwitchCycle_B = 5,
        NumSwitches,
    };
    
    enum {
        InputCycle_Trig_ = 0,
        InputTime_Cv_A = 1,
        InputTime_Cv_B = 2,
        InputTrig_A = 3,
        InputFollow_A = 4,
        InputFollow_B = 5,
        InputTrig_B = 6,
        InputAudio_A_In = 7,
        InputVca_Cv_A = 8,
        InputVca_Cv_B = 9,
        InputAudio_B_In = 10,
        NumInJacks,
    };
    
    enum {
        OutputEor_A = 0,
        OutputEof_B = 1,
        OutputOr = 2,
        OutputAudio_A_Out = 3,
        OutputEnv_A_Out = 4,
        OutputEnv_B_Out = 5,
        OutputAudio_B_Out = 6,
        NumOutJacks,
    };
    
    enum {
        LedRise_Led_A = 0,
        LedFall_Led_A = 1,
        LedRise_Led_B = 2,
        LedFall_Led_B = 3,
        LedEor_Led = 4,
        LedEof_Led = 5,
        LedEnv_A_Led = 6,
        LedEnv_B_Led = 7,
        NumDiscreteLeds,
    };
};
} // namespace MetaModule
