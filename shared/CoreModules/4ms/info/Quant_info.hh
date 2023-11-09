#pragma once
#include "CoreModules/elements/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct QuantInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Quant"};
    static constexpr std::string_view description{"Quantizer"};
    static constexpr uint32_t width_hp = 10;
    static constexpr std::string_view svg_filename{"res/modules/Quant_artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 9> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(37.85), to_mm<72>(151.34), Center, "Scale", ""}},
		Davies1900hBlackKnob{{to_mm<72>(106.4), to_mm<72>(151.34), Center, "Root", ""}},
		Davies1900hBlackKnob{{to_mm<72>(72.13), to_mm<72>(201.33), Center, "Transpose", ""}},
		AnalogJackInput4ms{{to_mm<72>(29.94), to_mm<72>(272.23), Center, "Input", ""}},
		AnalogJackInput4ms{{to_mm<72>(72.13), to_mm<72>(272.23), Center, "Scale CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(115.17), to_mm<72>(272.23), Center, "Root CV", ""}},
		AnalogJackOutput4ms{{to_mm<72>(29.94), to_mm<72>(313.84), Center, "Thru", ""}},
		AnalogJackOutput4ms{{to_mm<72>(72.13), to_mm<72>(313.84), Center, "Pre", ""}},
		AnalogJackOutput4ms{{to_mm<72>(115.17), to_mm<72>(313.84), Center, "Out", ""}},
}};

    enum class Elem {
        ScaleKnob,
        RootKnob,
        TransposeKnob,
        InputIn,
        ScaleCvIn,
        RootCvIn,
        ThruOut,
        PreOut,
        Out,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobScale = 0,
        KnobRoot = 1,
        KnobTranspose = 2,
        NumKnobs,
    };
    
    
    enum {
        InputInput = 0,
        InputScale_Cv = 1,
        InputRoot_Cv = 2,
        NumInJacks,
    };
    
    enum {
        OutputThru = 0,
        OutputPre = 1,
        OutputOut = 2,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
