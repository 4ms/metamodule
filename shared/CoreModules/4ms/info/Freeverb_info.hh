#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct FreeverbInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Freeverb"};
    static constexpr std::string_view description{"Reverb Effect"};
    static constexpr uint32_t width_hp = 10;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Freeverb-artwork.svg"};

    static constexpr std::array<Element, 10> Elements{{
		Davies1900hBlackKnob{to_mm<72>(37.85), to_mm<72>(46.42), "Size", "", 0, 0, 1, 0.25f},
		Davies1900hBlackKnob{to_mm<72>(106.4), to_mm<72>(46.42), "Time", "", 0, 0, 1, 0.25f},
		Davies1900hBlackKnob{to_mm<72>(37.85), to_mm<72>(104.62), "Damp", "", 0, 0, 1, 0.25f},
		Davies1900hBlackKnob{to_mm<72>(106.4), to_mm<72>(104.62), "Mix", "", 0, 0, 1, 0.875f},
		AnalogJackInput4ms{to_mm<72>(29.94), to_mm<72>(232.1), "Input", ""},
		AnalogJackInput4ms{to_mm<72>(72.13), to_mm<72>(232.1), "Size CV", ""},
		AnalogJackInput4ms{to_mm<72>(115.17), to_mm<72>(232.1), "Time CV", ""},
		AnalogJackInput4ms{to_mm<72>(29.94), to_mm<72>(272.23), "Damp CV", ""},
		AnalogJackInput4ms{to_mm<72>(72.13), to_mm<72>(272.23), "Ratio CV", ""},
		AnalogJackOutput4ms{to_mm<72>(115.17), to_mm<72>(313.84), "Out", ""},
}};

    enum class Elem {
        SizeKnob,
        TimeKnob,
        DampKnob,
        MixKnob,
        InputIn,
        SizeCvIn,
        TimeCvIn,
        DampCvIn,
        RatioCvIn,
        Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobSize = 0,
        KnobTime = 1,
        KnobDamp = 2,
        KnobMix = 3,
        NumKnobs,
    };
    
    
    enum {
        InputInput = 0,
        InputSize_Cv = 1,
        InputTime_Cv = 2,
        InputDamp_Cv = 3,
        InputRatio_Cv = 4,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
