#pragma once
#include "CoreModules/elements/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct PEGInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"PEG"};
    static constexpr std::string_view description{"Pingable Envelope Generator"};
    static constexpr uint32_t width_hp = 20;
    static constexpr std::string_view svg_filename{"res/modules/PEG_artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 42> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(34.2), to_mm<72>(106.06), Center, "Ping Div Mult 1", ""}},
		Davies1900hBlackKnob{{to_mm<72>(34.16), to_mm<72>(170.68), Center, "Scale 1", ""}},
		Davies1900hBlackKnob{{to_mm<72>(95.87), to_mm<72>(151.47), Center, "Skew 1", ""}},
		Davies1900hBlackKnob{{to_mm<72>(106.67), to_mm<72>(215.41), Center, "Curve 1", ""}},
		Davies1900hBlackKnob{{to_mm<72>(254.32), to_mm<72>(106.02), Center, "Ping Div Mult 2", ""}},
		Davies1900hBlackKnob{{to_mm<72>(254.75), to_mm<72>(170.82), Center, "Scale 2", ""}},
		Davies1900hBlackKnob{{to_mm<72>(192.91), to_mm<72>(151.47), Center, "Skew 2", ""}},
		Davies1900hBlackKnob{{to_mm<72>(182.51), to_mm<72>(215.41), Center, "Curve 2", ""}},
		WhiteMomentary7mm{{to_mm<72>(68.06), to_mm<72>(45.56), Center, "Ping 1", ""}},
		OrangeButton{{to_mm<72>(120.9), to_mm<72>(41.96), Center, "Cycle 1", ""}},
		OrangeButton{{to_mm<72>(21.56), to_mm<72>(213.99), Center, "Bi-polar 1", ""}},
		WhiteMomentary7mm{{to_mm<72>(220.56), to_mm<72>(45.56), Center, "Ping 2", ""}},
		OrangeButton{{to_mm<72>(167.48), to_mm<72>(41.9), Center, "Cycle 2", ""}},
		OrangeButton{{to_mm<72>(267.04), to_mm<72>(213.99), Center, "Bi-polar 2", ""}},
		GateJackInput4ms{{to_mm<72>(21.57), to_mm<72>(45.55), Center, "Ping 1 Jack", ""}},
		GateJackInput4ms{{to_mm<72>(267.05), to_mm<72>(45.55), Center, "Ping 2 Jack", ""}},
		GateJackInput4ms{{to_mm<72>(97.57), to_mm<72>(74.03), Center, "Qnt 1", ""}},
		GateJackInput4ms{{to_mm<72>(144.31), to_mm<72>(74.03), Center, "Toggle", ""}},
		GateJackInput4ms{{to_mm<72>(190.86), to_mm<72>(74.03), Center, "Qnt 2", ""}},
		GateJackInput4ms{{to_mm<72>(120.8), to_mm<72>(107.7), Center, "Async 1", ""}},
		GateJackInput4ms{{to_mm<72>(167.56), to_mm<72>(107.7), Center, "Async 2", ""}},
		AnalogJackInput4ms{{to_mm<72>(27.7), to_mm<72>(317.08), Center, "Div 1 Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(69.36), to_mm<72>(317.08), Center, "Skew 1 Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(111.11), to_mm<72>(317.08), Center, "Curve 1 Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(177.5), to_mm<72>(317.08), Center, "Curve 2 Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(219.06), to_mm<72>(317.08), Center, "Skew 2 Jack", ""}},
		AnalogJackInput4ms{{to_mm<72>(260.81), to_mm<72>(317.08), Center, "Div 2 Jack", ""}},
		AnalogJackOutput4ms{{to_mm<72>(48.56), to_mm<72>(248.86), Center, "Env 1", ""}},
		AnalogJackOutput4ms{{to_mm<72>(239.76), to_mm<72>(248.86), Center, "Env 2", ""}},
		AnalogJackOutput4ms{{to_mm<72>(27.7), to_mm<72>(281.13), Center, "+5V Env 1", ""}},
		GateJackOutput4ms{{to_mm<72>(69.36), to_mm<72>(281.13), Center, "EOR", ""}},
		GateJackOutput4ms{{to_mm<72>(111.11), to_mm<72>(281.13), Center, "EOF 1", ""}},
		AnalogJackOutput4ms{{to_mm<72>(144.22), to_mm<72>(299.87), Center, "OR", ""}},
		GateJackOutput4ms{{to_mm<72>(177.5), to_mm<72>(281.13), Center, "EOF 2", ""}},
		GateJackOutput4ms{{to_mm<72>(219.06), to_mm<72>(280.99), Center, "Half R", ""}},
		AnalogJackOutput4ms{{to_mm<72>(260.81), to_mm<72>(280.99), Center, "+5V Env 2", ""}},
		WhiteLight{{to_mm<72>(47.9), to_mm<72>(213.99), Center, "Env1Light", ""}},
		WhiteLight{{to_mm<72>(239.76), to_mm<72>(213.99), Center, "Env2Light", ""}},
		RedLight{{to_mm<72>(73.01), to_mm<72>(258.36), Center, "EOR1Light", ""}},
		RedLight{{to_mm<72>(111.11), to_mm<72>(258.36), Center, "EOF1Light", ""}},
		BlueLight{{to_mm<72>(177.5), to_mm<72>(258.36), Center, "EOF2Light", ""}},
		BlueLight{{to_mm<72>(215.46), to_mm<72>(258.36), Center, "HalfRise2Light", ""}},
}};

    enum class Elem {
        PingDivMult1Knob,
        Scale1Knob,
        Skew1Knob,
        Curve1Knob,
        PingDivMult2Knob,
        Scale2Knob,
        Skew2Knob,
        Curve2Knob,
        Ping1Button,
        Cycle1Button,
        BiNPolar1Button,
        Ping2Button,
        Cycle2Button,
        BiNPolar2Button,
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
        Env1Light,
        Env2Light,
        Eor1Light,
        Eof1Light,
        Eof2Light,
        Halfrise2Light,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobPing_Div_Mult_1, 
        KnobScale_1, 
        KnobSkew_1, 
        KnobCurve_1, 
        KnobPing_Div_Mult_2, 
        KnobScale_2, 
        KnobSkew_2, 
        KnobCurve_2, 
        NumKnobs,
    };
    
    enum {
        SwitchPing_1, 
        SwitchCycle_1, 
        SwitchBiNPolar_1, 
        SwitchPing_2, 
        SwitchCycle_2, 
        SwitchBiNPolar_2, 
        NumSwitches,
    };
    
    enum {
        InputPing_1_Jack, 
        InputPing_2_Jack, 
        InputQnt_1, 
        InputToggle, 
        InputQnt_2, 
        InputAsync_1, 
        InputAsync_2, 
        InputDiv_1_Jack, 
        InputSkew_1_Jack, 
        InputCurve_1_Jack, 
        InputCurve_2_Jack, 
        InputSkew_2_Jack, 
        InputDiv_2_Jack, 
        NumInJacks,
    };
    
    enum {
        OutputEnv_1, 
        OutputEnv_2, 
        OutputP5V_Env_1, 
        OutputEor, 
        OutputEof_1, 
        OutputOr, 
        OutputEof_2, 
        OutputHalf_R, 
        OutputP5V_Env_2, 
        NumOutJacks,
    };
    
    enum {
        LedEnv1Light, 
        LedEnv2Light, 
        LedEor1Light, 
        LedEof1Light, 
        LedEof2Light, 
        LedHalfrise2Light, 
        NumDiscreteLeds,
    };
    
};
} // namespace MetaModule
