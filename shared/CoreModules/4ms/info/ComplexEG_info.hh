#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct ComplexEGInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"ComplexEG"};
    static constexpr std::string_view description{"Complex Envelope Generator"};
    static constexpr uint32_t width_hp = 15;
    static constexpr std::string_view svg_filename{"res/modules/ComplexEG_artwork.svg"};
	static constexpr std::string_view png_filename{"4ms/fp/ComplexEG.png"};

    using enum Coords;

    static constexpr std::array<Element, 21> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(43.62), to_mm<72>(46.2), Center, "Attack", ""}},
		Davies1900hBlackKnob{{to_mm<72>(43.62), to_mm<72>(163.28), Center, "Hold", ""}},
		Davies1900hBlackKnob{{to_mm<72>(108.12), to_mm<72>(45.53), Center, "Decay", ""}},
		Davies1900hBlackKnob{{to_mm<72>(172.52), to_mm<72>(163.23), Center, "Sustain", ""}},
		Davies1900hBlackKnob{{to_mm<72>(172.62), to_mm<72>(45.53), Center, "Release", ""}},
		Davies1900hBlackKnob{{to_mm<72>(43.62), to_mm<72>(104.51), Center, "A Curve", ""}},
		Davies1900hBlackKnob{{to_mm<72>(108.12), to_mm<72>(104.51), Center, "D Curve", ""}},
		Davies1900hBlackKnob{{to_mm<72>(172.62), to_mm<72>(104.51), Center, "R Curve", ""}},
		OrangeButton{{to_mm<72>(108.12), to_mm<72>(159.77), Center, "Loop", ""}},
		AnalogJackInput4ms{{to_mm<72>(36.45), to_mm<72>(214.13), Center, "Input", ""}},
		AnalogJackInput4ms{{to_mm<72>(83.96), to_mm<72>(214.13), Center, "Attack CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(83.96), to_mm<72>(265.71), Center, "Hold CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(131.96), to_mm<72>(214.13), Center, "Decay CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(131.96), to_mm<72>(265.71), Center, "Sustain CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(179.96), to_mm<72>(214.13), Center, "Release CV", ""}},
		AnalogJackOutput4ms{{to_mm<72>(36.45), to_mm<72>(265.71), Center, "Attack Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(36.45), to_mm<72>(309.84), Center, "Hold Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(83.96), to_mm<72>(309.84), Center, "Decay Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(131.96), to_mm<72>(309.84), Center, "Sustain Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(179.96), to_mm<72>(265.71), Center, "Release Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(179.96), to_mm<72>(309.84), Center, "Out", ""}},
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
        LoopButton,
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
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
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
