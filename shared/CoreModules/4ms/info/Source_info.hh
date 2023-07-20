#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct SourceInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Source"};
    static constexpr std::string_view description{"DC Source"};
    static constexpr uint32_t width_hp = 4;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Source-artwork.svg"};

    static constexpr std::array<Element, 4> Elements{{
		Knob9mm{to_mm<72>(28.93), to_mm<72>(46.85), "1", "", 0, 0, 1, 0.25f},
		Knob9mm{to_mm<72>(28.93), to_mm<72>(94.68), "2", "", 0, 0, 1, 0.25f},
		AnalogJackOutput4ms{to_mm<72>(29.14), to_mm<72>(264.74), "1", ""},
		AnalogJackOutput4ms{to_mm<72>(29.14), to_mm<72>(312.33), "2", ""},
}};

    enum class Elem {
        _1Knob,
        _2Knob,
        _1Out,
        _2Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        Knob_1 = 0,
        Knob_2 = 1,
        NumKnobs,
    };
    
    
    
    enum {
        Output_1 = 0,
        Output_2 = 1,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
