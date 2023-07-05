#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct SlewInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Slew"};
    static constexpr std::string_view description{"Slew Limiter"};
    static constexpr uint32_t width_hp = 4;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Slew-artwork.svg"};

    static constexpr std::array<Element, 4> Elements{{
		Knob9mm{to_mm<72>(28.92), to_mm<72>(46.76), "Rise", "", 0, 0, 1, 0.5f},
		Knob9mm{to_mm<72>(28.92), to_mm<72>(94.44), "Fall", "", 0, 0, 1, 0.5f},
		AnalogJackInput4ms{to_mm<72>(29.28), to_mm<72>(263.82), "In", ""},
		AnalogJackOutput4ms{to_mm<72>(29.28), to_mm<72>(312.04), "Out", ""},
}};

    enum class Elem {
        RiseKnob,
        FallKnob,
        In,
        Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        KnobRise = 0,
        KnobFall = 1,
        NumKnobs,
    };
    
    
    enum {
        InputIn = 0,
        NumInJacks,
    };
    
    enum {
        OutputOut = 0,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
