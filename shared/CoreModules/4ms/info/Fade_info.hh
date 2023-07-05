#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct FadeInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Fade"};
    static constexpr std::string_view description{"Crossfader"};
    static constexpr uint32_t width_hp = 4;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Fade-artwork.svg"};

    static constexpr std::array<Element, 5> Elements{{
		Knob9mm{to_mm<72>(28.92), to_mm<72>(46.99), "Fade", "", 0, 0, 1, 0.5f},
		AnalogJackInput4ms{to_mm<72>(28.93), to_mm<72>(168.85), "CV", ""},
		AnalogJackInput4ms{to_mm<72>(28.93), to_mm<72>(216.11), "In 1", ""},
		AnalogJackInput4ms{to_mm<72>(28.93), to_mm<72>(263.68), "In 2", ""},
		AnalogJackOutput4ms{to_mm<72>(28.93), to_mm<72>(312.29), "Out", ""},
}};

    enum class Elem {
        FadeKnob,
        CvIn,
        In1In,
        In2In,
        Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobFade = 0,
        NumKnobs,
    };
    
    
    enum {
        InputCv = 0,
        InputIn_1 = 1,
        InputIn_2 = 2,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
