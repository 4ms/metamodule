#pragma once
#include "CoreModules/elements/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct SHInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"SH"};
    static constexpr std::string_view description{"2 Ch. Sample and Hold"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/SH_artwork.svg"};
	static constexpr std::string_view png_filename{"4ms/fp/SH.png"};

    using enum Coords;

    static constexpr std::array<Element, 6> Elements{{
		AnalogJackInput4ms{{to_mm<72>(29.28), to_mm<72>(78.14), Center, "Samp 1", ""}},
		AnalogJackInput4ms{{to_mm<72>(29.28), to_mm<72>(124.26), Center, "In 1", ""}},
		AnalogJackInput4ms{{to_mm<72>(29.28), to_mm<72>(168.85), Center, "Samp 2", ""}},
		AnalogJackInput4ms{{to_mm<72>(29.28), to_mm<72>(214.97), Center, "In 2", ""}},
		AnalogJackOutput4ms{{to_mm<72>(29.28), to_mm<72>(264.07), Center, "Out 1", ""}},
		AnalogJackOutput4ms{{to_mm<72>(29.28), to_mm<72>(312.29), Center, "Out 2", ""}},
}};

    enum class Elem {
        Samp1In,
        In1In,
        Samp2In,
        In2In,
        Out1Out,
        Out2Out,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    
    
    enum {
        InputSamp_1 = 0,
        InputIn_1 = 1,
        InputSamp_2 = 2,
        InputIn_2 = 3,
        NumInJacks,
    };
    
    enum {
        OutputOut_1 = 0,
        OutputOut_2 = 1,
        NumOutJacks,
    };
    
};
} // namespace MetaModule
