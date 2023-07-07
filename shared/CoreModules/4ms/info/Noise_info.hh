#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct NoiseInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Noise"};
    static constexpr std::string_view description{"Noise Source"};
    static constexpr uint32_t width_hp = 4;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Noise-artwork.svg"};

    static constexpr std::array<Element, 2> Elements{{
		AnalogJackOutput4ms{to_mm<72>(29.14), to_mm<72>(264.61), "White", ""},
		AnalogJackOutput4ms{to_mm<72>(29.14), to_mm<72>(312.2), "Pink", ""},
}};

    enum class Elem {
        WhiteOut,
        PinkOut,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    
    
    
    enum {
        OutputWhite = 0,
        OutputPink = 1,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
