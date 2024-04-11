#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct Atvert2Info : ModuleInfoBase {
    static constexpr std::string_view slug{"Atvert2"};
    static constexpr std::string_view description{"Dual Attenuverter"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Atvert2_artwork.svg"};
	static constexpr std::string_view png_filename{"4ms/fp/Atvert2.png"};

    using enum Coords;

    static constexpr std::array<Element, 6> Elements{{
		Knob9mm{{to_mm<72>(28.93), to_mm<72>(46.99), Center, "1", ""}},
		Knob9mm{{to_mm<72>(28.93), to_mm<72>(94.67), Center, "2", ""}},
		AnalogJackInput4ms{{to_mm<72>(29.28), to_mm<72>(168.85), Center, "In 1", ""}},
		AnalogJackInput4ms{{to_mm<72>(29.28), to_mm<72>(214.97), Center, "In 2", ""}},
		AnalogJackOutput4ms{{to_mm<72>(29.28), to_mm<72>(264.07), Center, "Out 1", ""}},
		AnalogJackOutput4ms{{to_mm<72>(29.28), to_mm<72>(312.29), Center, "Out 2", ""}},
}};

    enum class Elem {
        _1Knob,
        _2Knob,
        In1In,
        In2In,
        Out1Out,
        Out2Out,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        Knob_1 = 0,
        Knob_2 = 1,
        NumKnobs,
    };
    
    
    enum {
        InputIn_1 = 0,
        InputIn_2 = 1,
        NumInJacks,
    };
    
    enum {
        OutputOut_1 = 0,
        OutputOut_2 = 1,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
