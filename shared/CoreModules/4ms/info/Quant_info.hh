#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct QuantInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Quant"};
    static constexpr std::string_view description{"Quantizer"};
    static constexpr uint32_t width_hp = 10;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Quant-artwork.svg"};

    static constexpr std::array<Element, 9> Elements{{
		Davies1900hBlackKnob{to_mm<72>(37.85), to_mm<72>(151.34), "Scale", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(106.4), to_mm<72>(151.34), "Root", "", 0, 0, 1, 0.875f},
		Davies1900hBlackKnob{to_mm<72>(72.13), to_mm<72>(201.33), "Transpose", "", 0, 0, 1, 0.875f},
		AnalogJackInput4ms{to_mm<72>(29.94), to_mm<72>(272.23), "Input", ""},
		AnalogJackInput4ms{to_mm<72>(72.13), to_mm<72>(272.23), "Scale CV", ""},
		AnalogJackInput4ms{to_mm<72>(115.17), to_mm<72>(272.23), "Root CV", ""},
		AnalogJackOutput4ms{to_mm<72>(29.94), to_mm<72>(313.84), "Thru", ""},
		AnalogJackOutput4ms{to_mm<72>(72.13), to_mm<72>(313.84), "Pre", ""},
		AnalogJackOutput4ms{to_mm<72>(115.17), to_mm<72>(313.84), "Out", ""},
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

    // Legacy naming (safe to remove once CoreModule is converted
    
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
