#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct PanInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Pan"};
    static constexpr std::string_view description{"Panner"};
    static constexpr uint32_t width_hp = 4;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Pan-artwork.svg"};

    static constexpr std::array<Element, 5> Elements{{
		Knob9mm{to_mm<72>(28.93), to_mm<72>(47.42), "Pan", "", 0, 0, 1, 0.5f},
		AnalogJackInput4ms{to_mm<72>(29.28), to_mm<72>(166.45), "CV", ""},
		AnalogJackInput4ms{to_mm<72>(29.28), to_mm<72>(214.54), "In", ""},
		AnalogJackOutput4ms{to_mm<72>(29.28), to_mm<72>(263.64), "Out 1", ""},
		AnalogJackOutput4ms{to_mm<72>(29.28), to_mm<72>(311.23), "Out 2", ""},
}};

    enum class Elem {
        PanKnob,
        CvIn,
        In,
        Out1Out,
        Out2Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobPan = 0,
        NumKnobs,
    };
    
    
    enum {
        InputCv = 0,
        InputIn = 1,
        NumInJacks,
    };
    
    enum {
        OutputOut_1 = 0,
        OutputOut_2 = 1,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
