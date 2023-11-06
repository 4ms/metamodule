#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct SourceInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Source"};
    static constexpr std::string_view description{"DC Source"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Source_artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 4> Elements{{
		Knob9mm{{to_mm<72>(28.93), to_mm<72>(46.85), Center, "1", ""}},
		Knob9mm{{to_mm<72>(28.93), to_mm<72>(94.68), Center, "2", ""}},
		AnalogJackOutput4ms{{to_mm<72>(29.14), to_mm<72>(264.74), Center, "1", ""}},
		AnalogJackOutput4ms{{to_mm<72>(29.14), to_mm<72>(312.33), Center, "2", ""}},
}};

    enum class Elem {
        _1Knob,
        _2Knob,
        _1Out,
        _2Out,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
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
