#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct VerbInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Verb"};
    static constexpr std::string_view description{"Reverb Effect"};
    static constexpr uint32_t width_hp = 10;
    static constexpr std::string_view svg_filename{"res/modules/Verb_artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 16> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(37.85), to_mm<72>(46.42), Center, "Size", ""}},
		Davies1900hBlackKnob{{to_mm<72>(106.4), to_mm<72>(46.42), Center, "Time", ""}},
		Davies1900hBlackKnob{{to_mm<72>(37.85), to_mm<72>(104.62), Center, "Damp", ""}},
		Davies1900hBlackKnob{{to_mm<72>(106.4), to_mm<72>(104.62), Center, "AP Ratio", ""}},
		Davies1900hBlackKnob{{to_mm<72>(37.85), to_mm<72>(162.82), Center, "Comb", ""}},
		Davies1900hBlackKnob{{to_mm<72>(106.4), to_mm<72>(162.82), Center, "Mix", ""}},
		OrangeButton{{to_mm<72>(72.13), to_mm<72>(199.9), Center, "Hold", ""}},
		AnalogJackInput4ms{{to_mm<72>(29.94), to_mm<72>(232.1), Center, "Input", ""}},
		AnalogJackInput4ms{{to_mm<72>(72.13), to_mm<72>(232.1), Center, "Size CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(115.17), to_mm<72>(232.1), Center, "Time CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(29.94), to_mm<72>(272.23), Center, "Damp CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(72.13), to_mm<72>(272.23), Center, "Ratio CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(115.17), to_mm<72>(272.23), Center, "Comb CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(29.94), to_mm<72>(313.84), Center, "Mix CV", ""}},
		GateJackInput4ms{{to_mm<72>(72.13), to_mm<72>(313.84), Center, "Hold Gate", ""}},
		AnalogJackOutput4ms{{to_mm<72>(115.17), to_mm<72>(313.84), Center, "Out", ""}},
}};

    enum class Elem {
        SizeKnob,
        TimeKnob,
        DampKnob,
        ApRatioKnob,
        CombKnob,
        MixKnob,
        HoldButton,
        InputIn,
        SizeCvIn,
        TimeCvIn,
        DampCvIn,
        RatioCvIn,
        CombCvIn,
        MixCvIn,
        HoldGateIn,
        Out,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobSize = 0,
        KnobTime = 1,
        KnobDamp = 2,
        KnobAp_Ratio = 3,
        KnobComb = 4,
        KnobMix = 5,
        NumKnobs,
    };
    
    enum {
        SwitchHold = 0,
        NumSwitches,
    };
    
    enum {
        InputInput = 0,
        InputSize_Cv = 1,
        InputTime_Cv = 2,
        InputDamp_Cv = 3,
        InputRatio_Cv = 4,
        InputComb_Cv = 5,
        InputMix_Cv = 6,
        InputHold_Gate = 7,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
