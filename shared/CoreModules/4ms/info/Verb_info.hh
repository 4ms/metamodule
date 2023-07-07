#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct VerbInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Verb"};
    static constexpr std::string_view description{"Reverb Effect"};
    static constexpr uint32_t width_hp = 10;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Verb-artwork.svg"};

    static constexpr std::array<Element, 16> Elements{{
		Davies1900hBlackKnob{to_mm<72>(37.85), to_mm<72>(46.42), "Size", "", 0, 0, 1, 0.25f},
		Davies1900hBlackKnob{to_mm<72>(106.4), to_mm<72>(46.42), "Time", "", 0, 0, 1, 0.25f},
		Davies1900hBlackKnob{to_mm<72>(37.85), to_mm<72>(104.62), "Damp", "", 0, 0, 1, 0.25f},
		Davies1900hBlackKnob{to_mm<72>(106.4), to_mm<72>(104.62), "AP Ratio", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(37.85), to_mm<72>(162.82), "Comb", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(106.4), to_mm<72>(162.82), "Mix", "", 0, 0, 1, 0.875f},
		AnalogJackInput4ms{to_mm<72>(29.94), to_mm<72>(232.1), "Input", ""},
		AnalogJackInput4ms{to_mm<72>(72.13), to_mm<72>(232.1), "Size CV", ""},
		AnalogJackInput4ms{to_mm<72>(115.17), to_mm<72>(232.1), "Time CV", ""},
		AnalogJackInput4ms{to_mm<72>(29.94), to_mm<72>(272.23), "Damp CV", ""},
		AnalogJackInput4ms{to_mm<72>(72.13), to_mm<72>(272.23), "Ratio CV", ""},
		AnalogJackInput4ms{to_mm<72>(115.17), to_mm<72>(272.23), "Comb CV", ""},
		AnalogJackInput4ms{to_mm<72>(29.94), to_mm<72>(313.84), "Mix CV", ""},
		GateJackInput4ms{to_mm<72>(72.13), to_mm<72>(313.84), "Hold Gate", ""},
		AnalogJackOutput4ms{to_mm<72>(115.17), to_mm<72>(313.84), "Out", ""},
		LatchingButtonMonoLight{to_mm<72>(72.13), to_mm<72>(199.9), "Hold", ""},
}};

    enum class Elem {
        SizeKnob,
        TimeKnob,
        DampKnob,
        ApRatioKnob,
        CombKnob,
        MixKnob,
        InputIn,
        SizeCvIn,
        TimeCvIn,
        DampCvIn,
        RatioCvIn,
        CombCvIn,
        MixCvIn,
        HoldGateIn,
        Out,
        HoldButton,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
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
