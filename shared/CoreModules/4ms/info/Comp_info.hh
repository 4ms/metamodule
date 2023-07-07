#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct CompInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Comp"};
    static constexpr std::string_view description{"Comparator"};
    static constexpr uint32_t width_hp = 4;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Comp-artwork.svg"};

    static constexpr std::array<Element, 5> Elements{{
		Knob9mm{to_mm<72>(28.93), to_mm<72>(46.53), "Offset", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(28.93), to_mm<72>(94.22), "CV", "", 0, 0, 1, 0.0f},
		AnalogJackInput4ms{to_mm<72>(28.63), to_mm<72>(214.97), "CV Jack", ""},
		AnalogJackInput4ms{to_mm<72>(28.63), to_mm<72>(264.07), "Input", ""},
		AnalogJackOutput4ms{to_mm<72>(28.63), to_mm<72>(312.29), "Out", ""},
}};

    enum class Elem {
        OffsetKnob,
        CvKnob,
        CvJackIn,
        InputIn,
        Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobOffset = 0,
        KnobCv = 1,
        NumKnobs,
    };
    
    
    enum {
        InputCv_Jack = 0,
        InputInput = 1,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
