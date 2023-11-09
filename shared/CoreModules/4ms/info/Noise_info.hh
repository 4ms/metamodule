#pragma once
#include "CoreModules/elements/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct NoiseInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Noise"};
    static constexpr std::string_view description{"Noise Source"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Noise_artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 2> Elements{{
		AnalogJackOutput4ms{{to_mm<72>(29.14), to_mm<72>(264.61), Center, "White", ""}},
		AnalogJackOutput4ms{{to_mm<72>(29.14), to_mm<72>(312.2), Center, "Pink", ""}},
}};

    enum class Elem {
        WhiteOut,
        PinkOut,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    
    
    
    enum {
        OutputWhite = 0,
        OutputPink = 1,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
