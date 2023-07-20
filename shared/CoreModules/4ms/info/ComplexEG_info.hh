#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct ComplexEGInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"ComplexEG"};
    static constexpr std::string_view description{"Complex Envelope Generator"};
    static constexpr uint32_t width_hp = 15;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/ComplexEG-artwork.svg"};

    static constexpr std::array<Element, 21> Elements{{
		Davies1900hBlackKnob{to_mm<72>(43.62), to_mm<72>(46.2), "Attack", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(43.62), to_mm<72>(163.28), "Hold", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(108.12), to_mm<72>(45.53), "Decay", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(172.52), to_mm<72>(163.23), "Sustain", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(172.62), to_mm<72>(45.53), "Release", "", 0, 0, 1, 0.25f},
		Davies1900hBlackKnob{to_mm<72>(43.62), to_mm<72>(104.51), "A Curve", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(108.12), to_mm<72>(104.51), "D Curve", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(172.62), to_mm<72>(104.51), "R Curve", "", 0, 0, 1, 0.0f},
		AnalogJackInput4ms{to_mm<72>(36.45), to_mm<72>(214.13), "Input", ""},
		AnalogJackInput4ms{to_mm<72>(83.96), to_mm<72>(214.13), "Attack CV", ""},
		AnalogJackInput4ms{to_mm<72>(83.96), to_mm<72>(265.71), "Hold CV", ""},
		AnalogJackInput4ms{to_mm<72>(131.96), to_mm<72>(214.13), "Decay CV", ""},
		AnalogJackInput4ms{to_mm<72>(131.96), to_mm<72>(265.71), "Sustain CV", ""},
		AnalogJackInput4ms{to_mm<72>(179.96), to_mm<72>(214.13), "Release CV", ""},
		AnalogJackOutput4ms{to_mm<72>(36.45), to_mm<72>(265.71), "Attack Out", ""},
		AnalogJackOutput4ms{to_mm<72>(36.45), to_mm<72>(309.84), "Hold Out", ""},
		AnalogJackOutput4ms{to_mm<72>(83.96), to_mm<72>(309.84), "Decay Out", ""},
		AnalogJackOutput4ms{to_mm<72>(131.96), to_mm<72>(309.84), "Sustain Out", ""},
		AnalogJackOutput4ms{to_mm<72>(179.96), to_mm<72>(265.71), "Release Out", ""},
		AnalogJackOutput4ms{to_mm<72>(179.96), to_mm<72>(309.84), "Out", ""},
		LatchingButtonMonoLight{to_mm<72>(108.12), to_mm<72>(159.77), "Loop", ""},
}};

    enum class Elem {
        AttackKnob,
        HoldKnob,
        DecayKnob,
        SustainKnob,
        ReleaseKnob,
        ACurveKnob,
        DCurveKnob,
        RCurveKnob,
        InputIn,
        AttackCvIn,
        HoldCvIn,
        DecayCvIn,
        SustainCvIn,
        ReleaseCvIn,
        AttackOut,
        HoldOut,
        DecayOut,
        SustainOut,
        ReleaseOut,
        Out,
        LoopButton,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobAttack = 0,
        KnobHold = 1,
        KnobDecay = 2,
        KnobSustain = 3,
        KnobRelease = 4,
        KnobA_Curve = 5,
        KnobD_Curve = 6,
        KnobR_Curve = 7,
        NumKnobs,
    };
    
    enum {
        SwitchLoop = 0,
        NumSwitches,
    };
    
    enum {
        InputInput = 0,
        InputAttack_Cv = 1,
        InputHold_Cv = 2,
        InputDecay_Cv = 3,
        InputSustain_Cv = 4,
        InputRelease_Cv = 5,
        NumInJacks,
    };
    
    enum {
        OutputAttack_Out = 0,
        OutputHold_Out = 1,
        OutputDecay_Out = 2,
        OutputSustain_Out = 3,
        OutputRelease_Out = 4,
        OutputOut = 5,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
