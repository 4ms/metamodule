#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct Atvert2Info : ModuleInfoBase {
    static constexpr std::string_view slug{"Atvert2"};
    static constexpr std::string_view description{"Dual Attenuverter"};
    static constexpr uint32_t width_hp = 4;
    static constexpr bool uses_center_coords = true;
    static constexpr std::string_view svg_filename{"res/modules/Atvert2-artwork.svg"};

    static constexpr std::array<Element, 6> Elements{{
		Knob9mm{to_mm<72>(28.93), to_mm<72>(46.99), "1", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(28.93), to_mm<72>(94.67), "2", "", 0, 0, 1, 0.0f},
		AnalogJackInput4ms{to_mm<72>(29.28), to_mm<72>(168.85), "In 1", ""},
		AnalogJackInput4ms{to_mm<72>(29.28), to_mm<72>(214.97), "In 2", ""},
		AnalogJackOutput4ms{to_mm<72>(29.28), to_mm<72>(264.07), "Out 1", ""},
		AnalogJackOutput4ms{to_mm<72>(29.28), to_mm<72>(312.29), "Out 2", ""},
}};

    enum class Elem {
        _1Knob,
        _2Knob,
        In1In,
        In2In,
        Out1Out,
        Out2Out,
    };

    // Legacy naming (safe to remove once CoreModule is converted
    
    enum {
        Knob_1 = 0,
        Knob_2 = 1,
    };
    
    
    enum {
        InputIn_1 = 0,
        InputIn_2 = 1,
    };
    
    enum {
        OutputOut_1 = 0,
        OutputOut_2 = 1,
    };
    
};
} // namespace MetaModule
