#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct FreeverbInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Freeverb"};
    static constexpr std::string_view description{"Reverb Effect"};
    static constexpr uint32_t width_hp = 10;
    static constexpr std::string_view svg_filename{"res/modules/Freeverb_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Freeverb.png"};

    using enum Coords;

    static constexpr std::array<Element, 10> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(37.85), to_mm<72>(46.42), Center, "Size", ""}, 0.25f},
		Davies1900hBlackKnob{{to_mm<72>(106.4), to_mm<72>(46.42), Center, "Time", ""}, 0.25f},
		Davies1900hBlackKnob{{to_mm<72>(37.85), to_mm<72>(104.62), Center, "Damp", ""}, 0.25f},
		Davies1900hBlackKnob{{to_mm<72>(106.4), to_mm<72>(104.62), Center, "Mix", ""}, 0.875f},
		AnalogJackInput4ms{{to_mm<72>(29.94), to_mm<72>(232.1), Center, "Input", ""}},
		AnalogJackInput4ms{{to_mm<72>(72.13), to_mm<72>(232.1), Center, "Size CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(115.17), to_mm<72>(232.1), Center, "Time CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(29.94), to_mm<72>(272.23), Center, "Damp CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(72.13), to_mm<72>(272.23), Center, "Ratio CV", ""}},
		AnalogJackOutput4ms{{to_mm<72>(115.17), to_mm<72>(313.84), Center, "Out", ""}},
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

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobSize, 
        KnobTime, 
        KnobDamp, 
        KnobMix, 
        NumKnobs,
    };
    
    
    enum {
        InputInput, 
        InputSize_Cv, 
        InputTime_Cv, 
        InputDamp_Cv, 
        InputRatio_Cv, 
        NumInJacks,
    };
    
    enum {
        OutputOut, 
        NumOutJacks,
    };
    
    
};
} // namespace MetaModule
