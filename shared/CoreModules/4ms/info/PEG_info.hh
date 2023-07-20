#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct PEGInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"PEG"};
    static constexpr std::string_view description{"Pingable Envelope Generator"};
    static constexpr uint32_t width_hp = 20;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/PEG-artwork.svg"};

    static constexpr std::array<Element, 42> Elements{{
		Davies1900hBlackKnob{to_mm<72>(34.2), to_mm<72>(106.06), "Ping Div Mult 1", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(254.32), to_mm<72>(106.02), "Ping Div Mult 2", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(34.16), to_mm<72>(170.68), "Scale 1", "", 0, 0, 1, 1.0f},
		Davies1900hBlackKnob{to_mm<72>(95.87), to_mm<72>(151.47), "Skew 1", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(192.91), to_mm<72>(151.47), "Skew 2", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(254.75), to_mm<72>(170.82), "Scale 2", "", 0, 0, 1, 1.0f},
		Davies1900hBlackKnob{to_mm<72>(106.67), to_mm<72>(215.41), "Curve 1", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(182.51), to_mm<72>(215.41), "Curve 2", "", 0, 0, 1, 0.5f},
		GateJackInput4ms{to_mm<72>(21.57), to_mm<72>(45.55), "Ping 1 Jack", ""},
		GateJackInput4ms{to_mm<72>(267.05), to_mm<72>(45.55), "Ping 2 Jack", ""},
		GateJackInput4ms{to_mm<72>(97.57), to_mm<72>(74.03), "Qnt 1", ""},
		GateJackInput4ms{to_mm<72>(144.31), to_mm<72>(74.03), "Toggle", ""},
		GateJackInput4ms{to_mm<72>(190.86), to_mm<72>(74.03), "Qnt 2", ""},
		GateJackInput4ms{to_mm<72>(120.8), to_mm<72>(107.7), "Async 1", ""},
		GateJackInput4ms{to_mm<72>(167.56), to_mm<72>(107.7), "Async 2", ""},
		AnalogJackInput4ms{to_mm<72>(27.7), to_mm<72>(317.08), "Div 1 Jack", ""},
		AnalogJackInput4ms{to_mm<72>(69.36), to_mm<72>(317.08), "Skew 1 Jack", ""},
		AnalogJackInput4ms{to_mm<72>(111.11), to_mm<72>(317.08), "Curve 1 Jack", ""},
		AnalogJackInput4ms{to_mm<72>(177.5), to_mm<72>(317.08), "Curve 2 Jack", ""},
		AnalogJackInput4ms{to_mm<72>(219.06), to_mm<72>(317.08), "Skew 2 Jack", ""},
		AnalogJackInput4ms{to_mm<72>(260.81), to_mm<72>(317.08), "Div 2 Jack", ""},
		AnalogJackOutput4ms{to_mm<72>(48.56), to_mm<72>(248.86), "Env 1", ""},
		AnalogJackOutput4ms{to_mm<72>(239.76), to_mm<72>(248.86), "Env 2", ""},
		AnalogJackOutput4ms{to_mm<72>(27.7), to_mm<72>(281.13), "+5V Env 1", ""},
		GateJackOutput4ms{to_mm<72>(69.36), to_mm<72>(281.13), "EOR", ""},
		GateJackOutput4ms{to_mm<72>(111.11), to_mm<72>(281.13), "EOF 1", ""},
		AnalogJackOutput4ms{to_mm<72>(144.22), to_mm<72>(299.87), "OR", ""},
		GateJackOutput4ms{to_mm<72>(177.5), to_mm<72>(281.13), "EOF 2", ""},
		GateJackOutput4ms{to_mm<72>(219.06), to_mm<72>(280.99), "Half R", ""},
		AnalogJackOutput4ms{to_mm<72>(260.81), to_mm<72>(280.99), "+5V Env 2", ""},
		RedGreenBlueLight{to_mm<72>(47.9), to_mm<72>(213.99), "Env LED 1", ""},
		RedGreenBlueLight{to_mm<72>(239.76), to_mm<72>(213.99), "Env LED 2", ""},
		RedGreenBlueLight{to_mm<72>(73.01), to_mm<72>(258.36), "EOR LED 1", ""},
		RedGreenBlueLight{to_mm<72>(111.11), to_mm<72>(258.36), "EOF LED 1", ""},
		RedGreenBlueLight{to_mm<72>(177.5), to_mm<72>(258.36), "EOF LED 2", ""},
		RedGreenBlueLight{to_mm<72>(215.46), to_mm<72>(258.36), "Half R", ""},
		MomentaryButtonWhiteLight{to_mm<72>(68.06), to_mm<72>(45.56), "Ping 1", ""},
		MomentaryButtonWhiteLight{to_mm<72>(120.9), to_mm<72>(41.96), "Cycle 1", ""},
		MomentaryButtonWhiteLight{to_mm<72>(167.48), to_mm<72>(41.9), "Cycle 2", ""},
		MomentaryButtonWhiteLight{to_mm<72>(220.56), to_mm<72>(45.56), "Ping 2", ""},
		MomentaryButtonWhiteLight{to_mm<72>(21.56), to_mm<72>(213.99), "Bi-polar 1", ""},
		MomentaryButtonWhiteLight{to_mm<72>(267.04), to_mm<72>(213.99), "Bi-polar 2", ""},
}};

    enum class Elem {
        PingDivMult1Knob,
        PingDivMult2Knob,
        Scale1Knob,
        Skew1Knob,
        Skew2Knob,
        Scale2Knob,
        Curve1Knob,
        Curve2Knob,
        Ping1JackIn,
        Ping2JackIn,
        Qnt1In,
        ToggleIn,
        Qnt2In,
        Async1In,
        Async2In,
        Div1JackIn,
        Skew1JackIn,
        Curve1JackIn,
        Curve2JackIn,
        Skew2JackIn,
        Div2JackIn,
        Env1Out,
        Env2Out,
        P5VEnv1Out,
        EorOut,
        Eof1Out,
        OrOut,
        Eof2Out,
        HalfROut,
        P5VEnv2Out,
        EnvLed1Light,
        EnvLed2Light,
        EorLed1Light,
        EofLed1Light,
        EofLed2Light,
        HalfRLight,
        Ping1Button,
        Cycle1Button,
        Cycle2Button,
        Ping2Button,
        BiNPolar1Button,
        BiNPolar2Button,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobPing_Div_Mult_1 = 0,
        KnobPing_Div_Mult_2 = 1,
        KnobScale_1 = 2,
        KnobSkew_1 = 3,
        KnobSkew_2 = 4,
        KnobScale_2 = 5,
        KnobCurve_1 = 6,
        KnobCurve_2 = 7,
        NumKnobs,
    };
    
    enum {
        SwitchPing_1 = 0,
        SwitchCycle_1 = 1,
        SwitchCycle_2 = 2,
        SwitchPing_2 = 3,
        SwitchBiNPolar_1 = 4,
        SwitchBiNPolar_2 = 5,
        NumSwitches,
    };
    
    enum {
        InputPing_1_Jack = 0,
        InputPing_2_Jack = 1,
        InputQnt_1 = 2,
        InputToggle = 3,
        InputQnt_2 = 4,
        InputAsync_1 = 5,
        InputAsync_2 = 6,
        InputDiv_1_Jack = 7,
        InputSkew_1_Jack = 8,
        InputCurve_1_Jack = 9,
        InputCurve_2_Jack = 10,
        InputSkew_2_Jack = 11,
        InputDiv_2_Jack = 12,
        NumInJacks,
    };
    
    enum {
        OutputEnv_1 = 0,
        OutputEnv_2 = 1,
        OutputP5V_Env_1 = 2,
        OutputEor = 3,
        OutputEof_1 = 4,
        OutputOr = 5,
        OutputEof_2 = 6,
        OutputHalf_R = 7,
        OutputP5V_Env_2 = 8,
        NumOutJacks,
    };
    
    enum {
        LedEnv_Led_1 = 0,
        LedEnv_Led_2 = 1,
        LedEor_Led_1 = 2,
        LedEof_Led_1 = 3,
        LedEof_Led_2 = 4,
        LedHalf_R = 5,
        NumDiscreteLeds,
    };
};
} // namespace MetaModule
