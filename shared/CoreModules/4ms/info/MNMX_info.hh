#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct MNMXInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"MNMX"};
    static constexpr std::string_view description{"Min Max Logic"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/MNMX_artwork.svg"};

    using enum Coords;

    static constexpr std::array<Element, 4> Elements{{
		AnalogJackInput4ms{to_mm<72>(28.92), to_mm<72>(168.85), Center, "In A", ""},
		AnalogJackInput4ms{to_mm<72>(28.92), to_mm<72>(214.97), Center, "In B", ""},
		AnalogJackOutput4ms{to_mm<72>(29.14), to_mm<72>(264.61), Center, "Min", ""},
		AnalogJackOutput4ms{to_mm<72>(28.92), to_mm<72>(312.29), Center, "Max", ""},
}};

    enum class Elem {
        InAIn,
        InBIn,
        MinOut,
        MaxOut,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    
    
    enum {
        InputIn_A = 0,
        InputIn_B = 1,
        NumInJacks,
    };
    
    enum {
        OutputMin = 0,
        OutputMax = 1,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
