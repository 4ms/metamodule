#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct PanInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Pan"};
    static constexpr std::string_view description{"Panner"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Pan_artwork.svg"};
	static constexpr std::string_view png_filename{"4ms/fp/Pan.png"};

    using enum Coords;

    static constexpr std::array<Element, 5> Elements{{
		Knob9mm{{to_mm<72>(28.93), to_mm<72>(47.42), Center, "Pan", ""}},
		AnalogJackInput4ms{{to_mm<72>(29.28), to_mm<72>(166.45), Center, "CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(29.28), to_mm<72>(214.54), Center, "In", ""}},
		AnalogJackOutput4ms{{to_mm<72>(29.28), to_mm<72>(263.64), Center, "Out 1", ""}},
		AnalogJackOutput4ms{{to_mm<72>(29.28), to_mm<72>(311.23), Center, "Out 2", ""}},
}};

    enum class Elem {
        PanKnob,
        CvIn,
        In,
        Out1Out,
        Out2Out,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
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
